#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <SoftwareSerial.h>
#include "UART.h"

  
SoftwareSerial mySerial(10, 11); // RX, TX

volatile uint16_t pulse_count = 0;
volatile uint16_t capture = 1000;
volatile uint16_t position = 1;
volatile uint16_t valueA = 1500;
volatile uint16_t valueB = 5;

volatile uint8_t flag_random = 0;
volatile uint8_t enableCount = 0;
volatile uint8_t rxIndex = 0;  
volatile uint8_t rxDone = 0;

volatile char firstChar = 0;
volatile char rxBuffer[16];
String Buffer = "";

// put function declarations here:
void ContarPulso(void);
void ResetReception(void);

void ContarPulso() {
  pulse_count++;
}

void ResetReception(void){
    rxIndex = 0;
    firstChar = 0;
    memset((void *)rxBuffer, 0, sizeof(rxBuffer));
}

void setup(void) {
  Serial.begin(9600); // Serial.begin já inclui a configuração dos pinos RX e TX para a Serial
  mySerial.begin(9600);
  pinMode(2, INPUT); // Pino de interrupção para contagem de pulsos
  pinMode(10, INPUT); // Segundo RX do SoftwareSerial
  pinMode(11, OUTPUT); // Segundo TX do SoftwareSerial
  pinMode(7, OUTPUT); // Led verde
  pinMode(8, OUTPUT); // Led vermelho
  attachInterrupt(digitalPinToInterrupt(2), ContarPulso, RISING);
}

void loop() {

  // Verificação de dados recebidos pela Serial e SoftwareSerial
  while (Serial.available()){
    char c = Serial.read();
    if (c == '#'){
      Serial.print("Received: ");
      Serial.println(Buffer);
      Buffer = "";
      } else {
        Buffer += c;
    }
    
  }
  static String bufferSoftware = "";
  while (mySerial.available()){
    char c = mySerial.read();
    if (c == '#'){
      mySerial.print("Received: ");
      mySerial.println(bufferSoftware);
      bufferSoftware = "";
      } else {
        bufferSoftware += c;
    }
  } 
}

 /** 
  * Serve para iniciar o módulo UART com a taxa de baud e modo de velocidade especificados
 * @param baud_rate
 * @param BRGH speed mode (high speed or low speed)
 */

 void UART1_Init(void) {
  // Configura os pinos RX e TX
  UART1_TRIS_RX;
  UART1_TRIS_TX;
  Serial.begin(9600);
}

/**
 * Envia um caractere
 * @param c caractere a ser enviado
 */

 void UART1_Write(char data) {
  Serial.print(data);
}

void UART1_Write_String(const char *str) {
  while (*str)
  {
    UART1_Write(*str);
    str++;
  }
}

/**
 * Lê um caractere
 * @return  byte lido
 */

char UART1_Read_Char() {
  while (!Serial.available());
  return Serial.read();
}

/**
 * @param buf   buffer pré-alocado
 * @param max_length
 * @return número de bytes lidos
 */

uint8_t UART1ReadString(char *buf, uint8_t max_length) {
  for (uint8_t i = 0; i < max_length; i++) {
    buf[i] = UART1_Read_Char();;
  }
  return 1;
}

/**
 * Serve para iniciar o módulo UART com a taxa de baud e modo de velocidade especificados
 * @param baud_rate
 * @param BRGH speed mode (high speed or low speed)
 */

 void UART2_Init(void) {
  // Configura os pinos RX e TX
  UART2_TRIS_RX;
  UART2_TRIS_TX;
  mySerial.begin(9600);
}

/**
 * Envia um caractere
 * @param c caractere a ser enviado
 */

void UART2_Write(char data) {
  mySerial.print(data);
}

void UART2_Write_String(const char *str) {
  if (str == NULL) return;

  while (*str != '\0') {
    UART2_Write(*str);
    str++;
  }
}

/**
 * Lê um caractere
 * @return  byte lido
 */
char UART2_Read_Char() {
  while (!mySerial.available());
  return mySerial.read();
}

/**
 * Lê uma string, até ler '\0', com no máximo max_length caracteres.
 * @param buf   buffer pré-alocado
 * @param max_length
 * @return número de bytes lidos
 */

uint8_t UART2_Read_String(char *buf, uint8_t max_length) {
  for (uint8_t i = 0; i < max_length; i++) {
    buf[i] = UART2_Read_Char();
  }
  return 1; 
}
