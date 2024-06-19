#ifndef SETUPWIFI_H
#define SETUPWIFI_H

/*=== Inclusão de bibliotecas ================================*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <time.h>

/*=== Inclusão de funções próprias ===========================*/
#include <serialdebug.h>

/*=== Preprocessor directives ================================*/

/*--- Informações para conexão à internet --------------------*/
#ifndef STASSID
  #define STASSID "ifgoiano priv" // "You_shall_not_pass 2.4"
  #define STAPSK  "usu@153*@" // "G1nd1lf4Br1nc4!"
#endif

/* #define is often misunderstood because it isn’t a programming statement.  Instead, it sets up a macro which causes a text replace to occur before code is compiled. This is a very powerful and useful feature.  No RAM is consumed by a variable called “STASSID” or "STAPSK".  In fact, no variables called “STASSID” or "STAPSK" exists at all! */

/*=== Definição de constantes externas =======================*/

/*=== Definição de variáveis externas ========================*/

/*=== Definição das funções ==================================*/
void beginWiFi();

#endif