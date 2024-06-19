#ifndef SERIALDEBUG_H
#define SERIALDEBUG_H

/*=== Inclusão de bibliotecas ================================*/
#include <Arduino.h>

/*=== Inclusão de funções próprias ===========================*/

/*=== Preprocessor directives ================================*/
#define DEBUG 1 /* Use DEBUG 1 to print in serial port. Use DEBUG 0 to skip printing. */

#if DEBUG == 1
#define debug(x) Serial.print(x) /* Read debug as Serial.print */
#define debugln(x) Serial.println(x) /* Read debugln as Serial.println */
#define debugf(x,y) Serial.printf(x,y) /* Read debugf as Serial.printf */
#else
#define debug(x) /* Read debug as nothing */
#define debugln(x) /* Read debugln as nothing */
#define debugf(x,y) /* Read debugf as nothing */
#endif

/*=== Definição de constantes externas =======================*/

/*=== Definição de variáveis externas ========================*/

/*=== Definição das funções ==================================*/

#endif