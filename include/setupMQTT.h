#ifndef SETUPMQTT_H
#define SETUPMQTT_H

/*=== Inclusão de bibliotecas ================================*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <time.h>

/*=== Inclusão de funções próprias ===========================*/
#include <serialdebug.h>

/*=== Preprocessor directives ================================*/

/*=== Definição de constantes externas =======================*/

/*=== Definição de variáveis externas ========================*/

/*=== Definição das funções ==================================*/
void MQTTbegin(PubSubClient & client, const char* & mqtt_server); // Ler sobre Pass by reference vs Pass by value
void connectMQTT(PubSubClient & client); // Ler sobre Pass by reference vs Pass by value

#endif