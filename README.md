<a href="./LICENSE">![GitHub](https://img.shields.io/badge/license-MIT-green)</a>

# PROJETO - NodeMCU e sensor RFID [EM DESENVOLVIMENTO]

## :rocket: Tecnologias utilizadas

<li>C</li>
<li>PHP</li>
<li>NodeMCU</li>
<li>Sensor RFID</li>

## :loudspeaker: Apresentação

Este é um projeto onde a o NodeMCU fica escutando a informações obtidas pelo sensor RFID, e assim que ocorre a leitura de algum chip, o NodeMCU envia pelo protocolo HTTP uma requisição via GET para um endpoint definido na API <a href="https://github.com/lucaslgr/api-restful-ponto-eletronico">api</a> enviando as informações do cartão lido do respectivo funcionário, para alimentar um banco de dados de um sistema de ponto eletrônico da empresa Encautech Jr.

## :clipboard: Instruções para rodar o projeto

### Pré-requisitos 

- Antes de começar, você vai precisar ter instalado em sua máquina as seguintes ferramentas:

<li>![Git](https://git-scm.com)</li>
<li>Caso não tenha, instale um editor, eu indico o <b>[VSCode](https://code.visualstudio.com/)</li>
<li>Indico também a extensão PlatformIO para o VSCode <b>[PlatformIO](https://platformio.org/)</li>

- Hardware:
<li>NodeMCU</li>
<li>Sensor RFID</li>
<li>Jumpers</li>

### Instalando e rodando:

- 1º: Clone o repositório:
  
  ```bash
  # Clone este repositório
  $ git clone https://github.com/lucaslgr/nodemcu-rfid
  ```

- 2º: Monte o hardware conforme a imagem abaixo:

  [EM DESENVOLVIMENTO]..

## :man_technologist: Autoria

Lucas Guimarães

https://lucaslgr.github.io/

https://www.linkedin.com/in/lucas-guimar%C3%A3es-rocha-a30282132/