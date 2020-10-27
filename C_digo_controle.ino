/*                LIGAÇÕES ARDUINO ==> NRF24L01
 *                         3.3V ==> VCC
 *                          GND ==> GND
 *                           8  ==> CSN
 *                           7  ==> CE
 *                           13 ==> SCK
 *                           11 ==> MOSI
 *                           12 ==> MISO
 *                LIGAÇÕES ARDUINO ==> BOTÕES
 *                           1  ==> BOTÃO 1
 *                           3  ==> BOTÃO 2
 *                LIGAÇÕES ARDUINO ==> POTENCIÔMETRO1
 *                          GND ==> GND
 *                          VCC ==> VCC
 *                           A0 ==> SINAL
 *                LIGAÇÕES ARDUINO ==> POTENCIÔMETRO2
 *                          GND ==> GND
 *                          VCC ==> VCC
 *                           A3 ==> SINAL                          
 *                SKETCH FEITA POR: THIAGO LOPES BATISTA
 *                27/10/2020 10:08 
 *                CARCAÇA PARA SER IMPRESSA EM 3D ESTÁ EM:
 * https://www.tinkercad.com/things/2rk4Yh9rpME-bodacious-tumelo-kasi
 *                MATERIAIS NESCESSÁRIOS PARA CONTROLE:
 *                ARDUINO NANO,  NRF24L01,
 *                BATERIA RECARREGÁVEL 18650,
 *                TP4056. SE QUISER INCREMENTE OUTROS BOTÕES NO
 *                CONTROLE E ACRESCENTE O QUE QUISER.
 *                   BOA DIVERSÃO COM SEU CARRINHO!!!
 */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define botao 1
boolean buttonState = 0;
#define botaob 3
boolean buttonState1 = 0;

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  pinMode(botao, INPUT);
  pinMode(botaob, INPUT);
}
void loop() {
  radio.stopListening();
  int potvalor = analogRead(A0);
  int angvalor = map(potvalor, 0, 1023, 0, 180);
  radio.write(&angvalor, sizeof(angvalor));
  
  int potenciometrovalor = analogRead(A3);
  int angulovalor = map(potenciometrovalor, 0, 1023, 0, 255);
  radio.write(&angulovalor, sizeof(angulovalor));
  
  buttonState = digitalRead(botao);
  radio.write(&buttonState, sizeof(buttonState));

  buttonState1 = digitalRead(botaob);
  radio.write(&buttonState1, sizeof(buttonState1));
}
