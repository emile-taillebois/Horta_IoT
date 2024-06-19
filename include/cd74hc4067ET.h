#ifndef CD74HC4067ET_H
#define CD74HC4067ET_H

/*=== Inclusão de bibliotecas ================================*/
#include <Arduino.h>

/*=== Inclusão de funções próprias ===========================*/

/*=== Preprocessor directives ================================*/

/*=== Definição de constantes externas =======================*/

/*--- Códigos de seleção da pinagem do multiplexador ---------*/
extern const int C0[4];
extern const int C1[4];
extern const int C2[4];
extern const int C3[4];
extern const int C4[4];
extern const int C5[4];
extern const int C6[4];
extern const int C7[4];
extern const int C8[4];
extern const int C9[4];
extern const int C10[4];
extern const int C11[4];
extern const int C12[4];
extern const int C13[4];
extern const int C14[4];
extern const int C15[4];

/*=== Definição de variáveis externas ========================*/

/*--- Definição das variáveis de saída analógica -------------*/
extern int analogInBin;
extern float analogInVolt;

/*=== Definição das funções ==================================*/
void setupMP();
void AnalogReadMP(const int channel[4]);

#endif