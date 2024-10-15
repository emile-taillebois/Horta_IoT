/*==============================================================
Controle e automação de uma Horta Inteligente
Instituto Federal Goiano - Campus Avançado Ipameri
Desenvolvedores:  Márcia Danielle (07/2022 - 12/2022)
                  Tiago Santos Dias (01/2023 - 31/07/2023)
                  Felipe da Costa Dias (10/2024 - presente -)
                  Emile Taillebois (07/2022 - presente)
Orientador do projeto: Emile Taillebois
==============================================================*/

/*=== Comentários ============================================*/

/*O programa está sendo desenvolvido para ter suporte aos seguintes sensores e componentes:
    - Sensor de umidade do solo com uso de saída digital para deep sleep e saída analógica para acionamento de irrigação;
    - Sensor hall para medição do fluxo de água;
    - ... */

/*=== Inclusão de bibliotecas ================================*/
#include <Arduino.h>
#include <user_interface.h> /* Required to write and read RTC memory. Required to retrieve reset info. */
#include <iostream>

/*=== Inclusão de funções próprias ===========================*/
#include <serialdebug.h> /* Código para uso do Serial.print apenas no modo de debug */
#include <setupWiFi.h> /* Conexão da placa ESP8266 na rede */
#include <setupMQTT.h> // Comunicação da placa com o Broker MQTT
#include <OTA.h> /* Atualização do código no modo "Over the Air"*/
#include <sleep.h> /* Controle dos modos de economia de energia */
#include <pcf8574ET.h> /* Multiplexador PCF8574 - comunicação I2C*/
#include <cd74hc4067ET.h> /* Multiplexador CD74HC4067 */
#include <rainsensor.h> /* Sensor de chuva */

/*=== Preprocessor directives ================================*/
#define RTCMEMORYSTART 64
#define RTCMEMORYLEN 128 /* https://www.youtube.com/watch?v=r-hEOL007nw */

/*=== Struct definitions =====================================*/

/*--- RTC memory data storage struct -------------------------*/
typedef struct  { // information over structs https://stackoverflow.com/questions/612328/difference-between-struct-and-typedef-struct-in-c/612350#612350
  int reset;
  int counter;
} rtcStore;

rtcStore rtcMem;

/*=== Seção de constantes (internal as standard) =============*/

/*--- Definição de atalhos para pinagens ---------------------*/

/* In C++, const global variable definitions have internal linkage by default, while non-const global variable definitions have external linkage by default. Thus, when defining const global variables to be used in external functions, their linkage must be set to external manually. Besides, in C++, const doesn't (necessarily) creates an object in memory, being able to act just like a #define (but with type and scope).*/

/*--- Umidity sensor constants -------------------------------*/
const int ANALOG_SOIL_DRY = 840; // Valor medido com o solo seco (esse valor pode e deve ser calibrado)
const int ANALOG_SOIL_WET = 200; // Valor medido com o solo molhado (esse valor pode e deve ser calibrado)
const int PERC_SOIL_DRY = 0; // Menor percentual do solo seco (0%)
const int PERC_SOIL_WET = 100; // Maior percentual do solo molhado (100%)

/*=== Seção de variáveis (external as standard) ==============*/

/*--- Inicialização de variáveis -----------------------------*/
int SoilMoisture;

/*=== Seção de configurações =================================*/

/*--- Informações de conexão ao Broker MQTT ------------------*/
const char* mqtt_server = "10.2.35.108"; // Introdução do IP do Broker MQTT - 107 (Tiago) - 108 (Emile)
WiFiClient espClient;
PubSubClient horta(espClient); // Nosso cliente agora se chama horta e é do tipo WiFiClient (outra opção seria EthernetClient)

/*=== Seção de setup - run once ==============================*/
void setup()
{
  /*=== Seção de configuração ================================*/

  /*--- Configuração da conexão Serial -----------------------*/
  delay(5000);
  Serial.begin(74880); /* Use 74880 for debug information concerning reset and reboot */

  /*--- RTC register of reset reason and number of resets ----*/
    /*--- RTC memory read and write parameters configuration -*/
    int buckets=(sizeof(rtcMem)/4);
    if (buckets==0) { buckets=1; }
    system_rtc_mem_read(RTCMEMORYSTART,&rtcMem,buckets*4); /* Lê os dados na memória em RTCMEMORYSTART e armazena na posição em que foi criada o struct rtcMem */
    /*--- Retrieve reset reason ------------------------------*/
    debugln("=======================================");
    debugln("Reset information");
    debugln("=======================================");
    rst_info* resetInfo; /* Definição de um ponteiro do tipo rst_info (esse tipo é um struct interno). */
    resetInfo = ESP.getResetInfoPtr(); /* Obtenção do endereço dos dados relativos ao último reset */
    rtcMem.reset = (*resetInfo).reason; /* Armazenamento da razão de reset no struct de dados a serem armazenados na memória RTC */
    debug("- Reset reason:");
    debugln(rtcMem.reset);
    /*
    Reset cause N°      Cause
    0                   Power reboot
    1                   Hardware WDT reset
    2                   Fatal exception
    3                   Software watchdog reset
    4                   Software reset
    5                   Deep-sleep
    6                   Hardware reset
    */
    /*--- Retrieve and save the number of resets -------------*/
    if (rtcMem.reset == 6 || rtcMem.counter == 3) /* Primeira inicialização da placa ou final de ciclo de 12 horas */
    {
      rtcMem.counter = -1;
    }
    ++rtcMem.counter;
    system_rtc_mem_write(RTCMEMORYSTART,&rtcMem,buckets*4); /* Pega os dados na posição de rtcMem e armazena na memória RTC na posição RTCMEMORYSTART */
    debug("- Number of resets after irrigation:");
    debugln(rtcMem.counter);

  /*--- Definição dos modos das pinagens ---------------------*/
  pinMode(D0,WAKEUP_PULLUP);

  /*--- Iniciação das pinagens -------------------------------*/
  WriteToPCF8574(ALLHIGH);

  /*--- Configuração do multiplexador PCF8574 (I2C) ----------*/
  Wire.begin();

  /*--- Configuração do multiplexador CD74HC40067 ------------*/
  setupMP();

  /*--- Configuração da conexão WiFi -------------------------*/
  beginWiFi();

  /*--- Configuração e conexão da comunicação MQTT -----------*/
  MQTTbegin(horta, mqtt_server);
  connectMQTT(horta);

  /*--- Configuração e inicialização do modo OTA -------------*/
  beginOTA();
  ArduinoOTA.handle();
  // Será necessário criar um interruptor na placa para ativação do modo OTA.

  /*=== Seção de comando =====================================*/

  /*--- Rain sensor using multiplexor ------------------------*/
  //rainsensor();

  /*--- Soil temperature sensor using multiplexor ------------*/

  /*--- Air temperature/umidity sensor -----------------------*/

  /*--- Soil umidity sensor usign multiplexor ----------------*/
  debugln("=======================================");
  debugln("Soil moisture");
  debugln("=======================================");
  AnalogReadMP(C0);
  debug("- AnalogInBin: "); debugln(analogInBin);
  SoilMoisture = constrain(analogInBin,ANALOG_SOIL_WET,ANALOG_SOIL_DRY); //Lê a umidade binária e mantém o valor lido dentro do intervalo de calibração
  SoilMoisture = map(SoilMoisture,ANALOG_SOIL_WET,ANALOG_SOIL_DRY,PERC_SOIL_WET,PERC_SOIL_DRY); //Executa a função "map" de acordo com o intervalo de 0% a 100%
  debug("- Soil moisture: "); debug(SoilMoisture); debugln("%"); // Imprime no monitor serial o percentual de umidade do solo
  char umid[8]; // Definindo uma variável character que atuará como string com no máximo 7 caracteres (o oitavo é o caracter nulo que identifica que a variável char será usada como string)
  dtostrf(SoilMoisture, 1, 0, umid); // Conversão de float em char dtostrf(float_value, min_width, num_digits_after_decimal, where_to_store_string)
  horta.publish("UmidadeSolo", umid);

  /*--- Seção de irrigação -----------------------------------*/
  if (rtcMem.counter == 0)
  {
    /*--- Irrigation activation/deactivation -----------------*/
    debugln("=======================================");
    debugln("Irrigation on/off");
    debugln("=======================================");
    debugln("- Irrigation will start in one second!");
    Serial.flush();
    delay(1000);
    WriteToPCF8574(P2);
    delay(100);
    WriteToPCF8574(ALLHIGH);
    debugln("- Irrigation is on!");
    Serial.flush();
    lightsleep(4); /* Ao entrar no modo light-sleep desconectamos a internet! Além disso, o tempo deve ser passado em minutos. */
    Serial.println("- Irrigation will turn off in one second!");
    Serial.flush();
    delay(1000);
    WriteToPCF8574(P1); 
    delay(100);
    WriteToPCF8574(ALLHIGH);
    Serial.println("- Irrigation is off!");
    Serial.flush();
    /*--- Water conspution sensor ----------------------------*/
  }
  /*--- Seção sem irrigação ----------------------------------*/
  else
  {
  }
  /*--- Acionamento do modo deepsleep ------------------------*/
  deepsleep(0.5); /* Ao entrar no modo deep-sleep desconectamos a internet! Além disso, o tempo deve ser passado em horas. */
}

/*=== Seção de loop - run in loop ============================*/
void loop()
{
  /*=== Seção de comando =====================================*/
}

/* char* p = "texto" indica que estamos definindo um ponteiro p que aponta para uma string armazenada na parte da memória referente ao código (somente leitura). Isso significa que o ponteiro p é armazenado na pilha de memória (stack memory -> temporária), enquanto a string referente ao texto está armazenada na memória referente ao código (portanto essa string não pode ser modificada como uma array). Caso usássemos char p = "texto", tanto a variável p como a string texto seriam armazenadas na pilha de memória na forma de array e, consequentemente ocupariam mais espaço. Isso é interessante apenas se quisermos criar uma string que possa ser modificada. Mais informações podem ser encontrada em: https://www.geeksforgeeks.org/whats-difference-between-char-s-and-char-s-in-c/ */

/* What is the difference between * and & in pointer?
The & is a unary operator in C which returns the memory address of the passed operand. This is also known as address of operator. <> The * is a unary operator which returns the value of object pointed by a pointer variable. It is known as value of operator. https://cplusplus.com/doc/tutorial/pointers/ */