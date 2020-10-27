/*                LIGAÇÕES ARDUINO ==> NRF24L01
 *                         3.3V ==> VCC
 *                          GND ==> GND
 *                           8  ==> CSN
 *                           7  ==> CE
 *                           13 ==> SCK
 *                           11 ==> MOSI
 *                           12 ==> MISO
 *                 LIGAÇÕES ARDUINO ==> SERVO
 *                          GND ==> GND
 *                          VCC ==> VCC
 *                            5 ==> SINAL 
 *                 LIGAÇÕES ARDUINO ==> L298N
 *                            4 ==> INPUT 4
 *                            2 ==> INPUT 3
 *                        "12V E GND DO L298N
 *                            NA FONTE EXTERNA"
 *                 LIGAÇÕES ARDUINO ==> BOTÕES
 *                       BOTÃO1 ==> 1
 *                       BOTÃO2 ==> 6
 *                (botão2 ou botaob como está no sketch)
 *                SKETCH FEITA POR: THIAGO LOPES BATISTA
 *                27/10/2020 10:08 
 *                CARCAÇA PARA SER IMPRESSA EM 3D ESTÁ EM:
 * https://www.tinkercad.com/things/2rk4Yh9rpME-bodacious-tumelo-kasi
 *                MATERIAIS NESCESSÁRIOS PARA CARRINHO:
 *                ARDUINO NANO,  L298N,  NRF24L01,
 *                MOTOR DC 12V OU 24V, BATERIA RECARREGÁVEL 12V,
 *                TP4056. SE QUISER INCREMENTE OUTROS BOTÕES NO
 *                CONTROLE E ACRESCENTE O QUE QUISER NO CARRINHO.
 *                   BOA DIVERSÃO COM SEU CARRINHO!!!
 */
// includes
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// defines
Servo servo;
#define pinmotor1 4
#define pinmotor2 2
#define velmotor1 3
#define botao 1
#define botaob 6
boolean buttonState = 0;
boolean buttonState1 = 0;

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  // put your setup code here, to run once:
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  
  pinMode(pinmotor1, OUTPUT);
  pinMode(pinmotor2, OUTPUT);
  pinMode(velmotor1, OUTPUT);
  pinMode(botao, INPUT);
  pinMode(botaob, INPUT);
  servo.attach(5);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (radio.available()) {
    while (radio.available()) {
      int anguloV = 0;
      radio.read(&anguloV, sizeof(anguloV));
      servo.write(anguloV);
    }
    }
  if (radio.available()) {
    while (radio.available()) {
  int potenciometrovalor = analogRead(A3);
  int angulovalor = map( potenciometrovalor, 0, 1023, 0, 255);
  radio.read(&angulovalor, sizeof(angulovalor));
  analogWrite(velmotor1, angulovalor);
  }
  }
  buttonState = digitalRead(botao);
  radio.read(&buttonState, sizeof(buttonState));

 buttonState1 = digitalRead(botaob);
  radio.read(&buttonState1, sizeof(buttonState1));

  
  if(digitalRead(botao) == HIGH){
    analogWrite(pinmotor1, 255);
    analogWrite(pinmotor2, 255);
    }if(digitalRead(botaob) == HIGH){
      analogWrite(pinmotor1, 255);
      analogWrite(pinmotor2, 255);
    }
  }
  
