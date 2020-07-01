#include <Arduino.h>
//Biblioteca do NODEMCU
#include <ESP8266WiFi.h>

//Bibliotecas do RFID
#include <SPI.h>
#include <MFRC522.h>

#define BASE_URL "/projectPontoEletronico/api-batponto/"
String base_url = BASE_URL;

//====================================================<RFID (START) CONFIG>====================================================
//Pinos do RFID
#define SS_PIN D4
#define RST_PIN D2

String IDTag = ""; //Variavel que armazenará o ID da Tag

//Definindo os pinos do módulo e passando para um objeto MFRC522 da lib
MFRC522 mfrc522(SS_PIN, RST_PIN);
//====================================================<RFID (END) CONFIG>====================================================

//==================================================<NODEMCU (START) CONFIG>====================================================
#ifndef STASSID //Verifica se esta definido
#define STASSID "wolf" //nick da rede
#define STAPSK  "wheyebatatadoce" //senha da rede
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "192.168.1.104"; //Ipv4 da rede
const uint16_t port = 80; //Porta onde esta rodando o Apache
//==================================================<NODEMCU (END) CONFIG>====================================================


//Configurações de Setup
void setup() {
  //Inicializando a serial e setando a velocidade/frequencia
  Serial.begin(9600);

  //==========================================Inicialização o [RFID]========================================================
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("RFID reading UID");

  //==========================================Inicialização o [NODEMCU]======================================================
  //Mensagem de inicio de conexão na rede
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  /**
   * Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
   * would try to act as both a client and an access-point and could cause
   *  network-issues with your other WiFi-devices on your WiFi-network. 
   */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//Função para fazer a requisiçao GET via HTTP e enviar o valor lido pelo RFID
void connectAndRequestHTTP(String uid){
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

  //We now create a URI for the request
  // String url = "/nodemcu/index.php?";
  String url = base_url+"access/"+IDTag+"/new";
    // url += "uidTag="; //key
    // url += IDTag; //value

  // This will send a string to the server
  Serial.println("sending data to server");
  Serial.println(url);

  //This will send the request to the server
  client.print(String("GET ") + url + "\r\nHTTP\1.1\r\n"+
              "Host: " + host + "\r\n" + 
              "Connection: close\r\n\r\n");

  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }

  // Lê todas as linhas da resposta do servidor e printa na serial
  Serial.println("Recebendo do servidor remoto");
  // not testing 'client.connected()' since we do not need to send data here
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
  }

  // Fechand a conexão
  Serial.println();
  Serial.println("Fechando a conexão");
  client.stop();

  delay(1000); // execute once every 10 segundos, don't flood remote service
}

//Função para verificar se tem algum RFID presente e fazer a leitura do UID
void readRFID(){
  //Esvaziando a String
  IDTag = "";

  //Verificando se existe algum novo cartão presente
  if(mfrc522.PICC_IsNewCardPresent())
  {
    //Lendo a informação do serial
    if(mfrc522.PICC_ReadCardSerial())
    {
      //Printando a UID da Tag
      Serial.println("Tag UID:");

      //Pegando a informação lida e salva no mfrc522.uid referente ao UID do chip lido
      for(byte i=0; i < mfrc522.uid.size; i++){
        //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        //Serial.print(mfrc522.uid.uidByte[i], HEX);
        IDTag.concat(String(mfrc522.uid.uidByte[i], HEX));
      }

      //Printa o IDTag na Serial
      Serial.println(IDTag);
      //Instrui o PICC quando está no estado de ACTIVE a ir para um estado de PARADA
      mfrc522.PICC_HaltA();

      //Chama a função para enviar o valor da TAG para iniciar uma requisição GET via HTTP
      connectAndRequestHTTP(IDTag);
    }
  }
}

//Fica executando a função readRFID
void loop() {
  readRFID();
}