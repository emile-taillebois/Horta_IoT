/*=== Cabeçalho ==============================================*/
#include <setupMQTT.h>

/*=== Inicialização de constantes externas ===================*/

/*=== Inicialização de constantes internas ===================*/

/*=== Inicialização de variáveis externas ====================*/

/*=== Inicialização de variáveis internas ====================*/

/*=== Definição das funções ==================================*/

/*--- Função de configuração do Broker MQTT ------------------*/
void MQTTbegin(PubSubClient & client, const char* & mqtt_server) // Ler sobre Pass by reference vs Pass by value
{
  client.setServer(mqtt_server, 1883);
}

/*--- Função de conexão do Broker MQTT -----------------------*/
void connectMQTT(PubSubClient & client) // Ler sobre Pass by reference vs Pass by value
{
  debugln("=======================================");
  debugln("MQTT connection");
  debugln("=======================================");
  if (!client.connected()) {
    time_t futuro = time(NULL) + 10; //  A função time(arg) retorna o instante de tempo em segundos medido a partir de Jan 1, 1970, sendo
                                        //+ que arg é a variável de armazenamento com formato da classe time_t. No caso, como não queremos salvar
                                        //+ o instante imediato, mas sim definirmos um tempo futuro apra parada do while, colocamos arg como
                                        //+ NULL (não armazenado), mas somamos 10s ao instante atual e salvamos na variável futuro da classe time_t.
    while (!client.connected()) {
      Serial.print("- Attempting MQTT connection...");
      // Attempt to connect
      if (client.connect("ESP8266Client")) {  // Estamos nomeando nosso cliente de forma única. O comando é booleano e, caso retorne true, o cliente está conectado.
        Serial.println("connected");
        // Subscribe
        client.subscribe("UmidadeSolo");
      } else if (time(NULL) < futuro) { // Se o tempo de conexão não passar de 1 minutos
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      } else { // Se o tempo de conexão passar de 1 minutos, abortamos a conexão.
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println("The MQTT conection was aborted!");
        break;
      }
    }
  }
  client.loop();
}

//client.setCallback(callback);