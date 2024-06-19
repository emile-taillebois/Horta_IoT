#ifndef PCF8574ET_H
#define PCF8574ET_H

/*=== Inclusão de bibliotecas ================================*/
#include <Arduino.h>
#include <Wire.h> /* Biblioteca para uso da comunicação I2C*/

/*=== Inclusão de funções próprias ===========================*/

/*=== Preprocessor directives ================================*/

/*=== Definição de constantes externas =======================*/

/*--- Constantes de OUTPUT para as pinagens do PCF8574 -------*/
extern const unsigned char P0;
extern const unsigned char P1;
extern const unsigned char P2;
extern const unsigned char P3;
extern const unsigned char P4;
extern const unsigned char P5;
extern const unsigned char P6;
extern const unsigned char P7;
extern const unsigned char ALLLOW;
extern const unsigned char ALLHIGH;

/* Nunca definir valores para variáveis nos cabeçalhos! Isso pode dar um erro de definições duplicadas. */

/*=== Definição de variáveis externas ========================*/

/*=== Definição das funções ==================================*/
void WriteToPCF8574(unsigned char data);

#endif