#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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
// put function declarations here:

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), ContarPulso, RISING);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
}

void ResetReception(void){
    rxIndex = 0;
    firstChar = 0;
    memset((void *)rxBuffer, 0, sizeof(rxBuffer));
}

void ContarPulso() {
  pulse_count++;
}



// put function definitions here:
