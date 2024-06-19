/*=== Cabeçalho ==============================================*/
#include <sleep.h>

/*=== Inicialização de constantes externas ===================*/

/*=== Inicialização de constantes internas ===================*/

/*=== Inicialização de variáveis externas ====================*/

/*=== Inicialização de variáveis internas ====================*/

/*=== Definição das funções ==================================*/

/*--- Função callback para light-sleep -----------------------*/
void fpm_wakup_cb_func() { /* The callback function will be called after system woke up only if the force sleep time out. */
  wifi_fpm_close();   /* Disable force sleep function. */
  Serial.println("- Light sleep is over!");
  Serial.flush();
}
/* Não se deve usar funções do tipo delay() ou yield() em funções callback. Isso leva a um erro. */

/*--- Função para ativação do modo lightsleep ----------------*/
void lightsleep(float sleepTimeMinutes) /* Maximum light-sleep time is around 4 min. */
{
  /*--- Configuration ----------------------------------------*/
  uint64_t sleepTimeMilliSeconds = sleepTimeMinutes*60e3; /* Light sleep time in milliseconds (e3  indica que está multiplicado por 10^3). */
  timer_list = nullptr; /* For timer-based light sleep to work, the os timers need to be disconnected. */
  /*--- Disable WiFi connection ------------------------------*/
  WiFi.disconnect(true); /* Disconnection of wi-fi. Por esse motivo, caso seja necessário o uso do Wi-Fi após o light-sleep, o mesmo deverá ser reativado. */
  WiFi.mode(WIFI_OFF); /* Essa maneira de desconectar o Wi-FI resolveu o problema de software watchdog que eu estava tendo. */
  /*--- Enable light sleep -----------------------------------*/
  Serial.println("- Entering light sleep mode!");
  Serial.flush();
  wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
  wifi_fpm_open(); /* Enable force sleep function. */
  wifi_fpm_set_wakeup_cb(fpm_wakup_cb_func); /* for light sleep to be resumed from immediately after a time-out or interrupt (without waiting out the full length of the delay()), it is also necessary to register a callback function which takes a minimum amount of computation/IO time (in particular a Serial.println() followed by Serial.flush() seems to do the trick)*/
  wifi_fpm_do_sleep(sleepTimeMilliSeconds * 1000); /* light sleep function requires microsseconds */
  delay(sleepTimeMilliSeconds + 1); /* The ESP8266 will not enter sleep mode immediately, it is going to sleep in the system idle task. Thus, for timed light sleep to be entered, the sleep command must be followed by a delay() (idle task) that is at least 1ms longer than the sleep */
  yield();
  /* The ESP8266 is a little different than the standard Arduino boards in that it has the watchdog (WDT) turned on by default. If the watchdog timer isn't periodically reset then it will automatically reset your ESP8266. The watchdog is reset every time one of the following occurs:
    - Return from loop() (i.e., reach the end of the function)
    - You call delay()
    - You call yield() */
}

/*--- Função para ativação do modo deepsleep -----------------*/
void deepsleep(float sleepTimeHours)
{
  /*--- Configuration ----------------------------------------*/
  uint64_t sleepTimeMicroSeconds = sleepTimeHours*3600e6;
  /*--- Enable deep sleep ------------------------------------*/
  debugln("=======================================");
  debugln("Deep sleep activation");
  debugln("=======================================");
  debugln("- Entering  deep-sleep mode!");
  Serial.flush();
  ESP.deepSleep(sleepTimeMicroSeconds, WAKE_RF_DEFAULT);
}