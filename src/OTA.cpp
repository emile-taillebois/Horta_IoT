/*=== Cabeçalho ==============================================*/
#include <OTA.h>

/*=== Inicialização de constantes externas ===================*/

/*=== Inicialização de constantes internas ===================*/

/*=== Inicialização de variáveis externas ====================*/

/*=== Inicialização de variáveis internas ====================*/

/*=== Definição das funções ==================================*/

/*--- Configação do modo OTA ---------------------------------*/
void beginOTA()
{
    debugln("=======================================");
    debugln("OTA connection");
    debugln("=======================================");
        /*--- OTA connection password ------------------------*/
        //ArduinoOTA.setPassword("admin");  /* No authentication by default */
        /*--- OTA configuration ------------------------------*/
        ArduinoOTA.onStart([]() {
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
            {
                type = "sketch";
            }
            else // U_FS
            {
                type = "filesystem";
            }
            // NOTE: if updating FS this would be the place to unmount FS using FS.end()
            debugln("- Start updating " + type);
        });
        ArduinoOTA.onEnd([]() {
            debugln("\nEnd");
        });
        ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
            debugf("Progress: %u%%\r", (progress / (total / 100)));
        });
        ArduinoOTA.onError([](ota_error_t error) {
            debugf("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR)
            {
                debugln("- Auth Failed");
            }
            else if (error == OTA_BEGIN_ERROR)
            {
                debugln("- Begin Failed");
            }
            else if (error == OTA_CONNECT_ERROR)
            {
                debugln("- Connect Failed");
            }
            else if (error == OTA_RECEIVE_ERROR)
            {
                debugln("- Receive Failed");
            }
            else if (error == OTA_END_ERROR)
            {
                debugln("- End Failed");
            }
        });
        ArduinoOTA.begin();
        debugln("- OTA connection is ready!");
        debug("- IP address: "); debugln(WiFi.localIP());
}