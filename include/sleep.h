#ifndef SLEEP_H
#define SLEEP_H

/*=== Inclusão de bibliotecas ================================*/
#include <Arduino.h>
#include <user_interface.h> /* required for light-sleep mode */
#include <ESP8266WiFi.h>

/*=== Inclusão de funções próprias ===========================*/
#include <serialdebug.h>

/*=== Preprocessor directives ================================*/

/*=== Definição de constantes externas =======================*/

/*=== Definição de variáveis externas ========================*/
extern os_timer_t* timer_list; /* List of active os_timers of the system */

/*=== Definição das funções ==================================*/
void fpm_wakup_cb_func();
void lightsleep(float sleepTimeMinutes);
void deepsleep(float sleepTimeHours);

#endif