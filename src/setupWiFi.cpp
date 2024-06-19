/*=== Cabeçalho ==============================================*/
#include <setupWiFi.h>

/*=== Inicialização de constantes externas ===================*/

/*=== Inicialização de constantes internas ===================*/

/*=== Inicialização de variáveis externas ====================*/

/*=== Inicialização de variáveis internas ====================*/

/*=== Definição das funções ==================================*/

/*--- Função de conexão à internet ---------------------------*/
void beginWiFi()
{
    WiFi.mode(WIFI_STA); /* O modo STA é usado para conectar o módulo ESP a uma rede Wi-Fi estabelecida por um ponto de acesso.*/
    time_t futuro = time(NULL) + 30; /* A função time(arg) retorna o instante de tempo em segundos medido a partir de Jan 1, 1970, sendo que arg é a variável de armazenamento com formato da classe time_t. No caso, como não queremos salvar o instante imediato, mas sim definirmos um tempo futuro para parada do while, colocamos arg como NULL (não armazenado), mas somamos 30s ao instante atual e salvamos na variável futuro da classe time_t. */
    debugln("=======================================");
    debugln("WiFi connection");
    debugln("=======================================");
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        debug("- Connecting to ");
        debugln(STASSID);
        WiFi.begin(STASSID, STAPSK);
        if (time(NULL) > futuro) /* Se o tempo de conexão passar de 30 segundos, abortamos a conexão. */
        {
            debugln("- Connection Failed! Skipping connection!");
            break;
        }
        else if (WiFi.waitForConnectResult() != WL_CONNECTED)
        {
            debugln("- Connection Failed! Trying again...");
        }
        else
        {
            debugln("- WiFi connected!");
            debug("- IP address: "); debugln(WiFi.localIP());
        }
    }
}