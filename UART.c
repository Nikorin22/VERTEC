#include <Arduino.h>
#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include "UART.h"
#include "main.cpp"

 /** 
  * Serve para iniciar o módulo UART com a taxa de baud e modo de velocidade especificados
 * @param baud_rate
 * @param BRGH speed mode (high speed or low speed)
 */
void UART1_Init(void){
    
    pinMode (0,INPUT);    // RX
    pinMode (1,OUTPUT);    // TX

}

/**
 * Envia um caractere
 * @param c caractere a ser enviado
 */

void UART1_Write(char data) {
   Serial.print(data);
}

void UART1_Write_String(const char *str)
{
    while(*str)
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
    while (!Serial.available());   // Espera por dados disponíveis
    return Serial.read();
}

/**
 * @param buf   buffer pré-alocado
 * @param max_length    tamanho máximo do buffer
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
void UART2_Init(void){
    
    pinMode (10,INPUT);    // RX
    pinMode (11,OUTPUT);    // TX

}

/**
 * Send a character
 * @param c character to send
 */
void UART2_Write(char data) {
    mySerial.print(data);
}

void UART2_Write_String(const char *str)
{
    if (str == NULL) return;

    while (*str != '\0') {
        UART2_Write(*str++);
    }
}

/**
 * Read one character
 * @return  byte read
 */
char UART2_Read_Char() {
    while (!mySerial.available());   // Espera por dados disponíveis
    return mySerial.read();
}

/**
 * @param buf   pre-allocated buffer
 * @param max_length    tamanho máximo do buffer
 * @return número de bytes lidos            
 */

uint8_t UART2_Read_String(char *buf, uint8_t max_length) {
    for (uint8_t i = 0; i < max_length; i++) {
        buf[i] = UART2_Read_Char();;
    }
    return 1;
}