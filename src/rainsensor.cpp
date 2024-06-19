/*=== Cabeçalho ==============================================*/
#include <rainsensor.h>

/*=== Informações sobre o código =============================*/
/*
    - Em caso de ausência de chuva a leitura binária de A0 será de 1024, o que corresponde a 3,3V.
    - Em caso de chuva a leitura binária de A0 irá diminuir, indicando uma queda na leitura da voltagem.
    - Os níveis de chuva foram definidos da seguinte forma:
      -- Tempo totalmente seco: maior que 3,20V e menor ou igual a 3,30V
      -- Chuvisco: maior que 2,20V e menor que 3,20V
      -- Chuva de média intensidade: maior que 1,10V e menor que 2,20V"
      -- Chuva de alta intensidade: maior que 0,00V e menor que 1,10V"
*/

/*=== Inicialização de constantes externas ===================*/

/*=== Inicialização de constantes internas ===================*/

/*=== Inicialização de variáveis externas ====================*/

/*=== Inicialização de variáveis internas ====================*/

/*=== Definição das funções ==================================*/

/*--- Leitura do sensor de chuva -----------------------------*/
int rainsensor()
{
    /*--- Inicialização de variáveis internas ----------------*/
    int chuva = 0; /* Saída padrão do sensor de chuva */
    /*--- Código da função -----------------------------------*/
    Serial.println("=======================================");
    Serial.println("Sensor de chuva");
    Serial.println("=======================================");
    AnalogReadMP(C2); /* AnalogReadMP é uma função da biblioteca cd74hc4067ET */
    if (analogInVolt >= 3.20 && analogInVolt <= 3.30)
    {
        Serial.println("Nao esta chovendo.");
        chuva = 0;
    }
    else if (analogInVolt >= 2.20 && analogInVolt < 3.20) /* && is the logical AND in C++. ! is the logical NOT. || is the logical OR.*/
    {
        Serial.println("Chuva de baixa intensidade.");
        chuva = 1;
    }
    else if (analogInVolt >= 1.10 && analogInVolt < 2.20)
    {
        Serial.println("Chuva de media intensidade.");
        chuva = 2;
    }
    else if (analogInVolt >= 0.00 && analogInVolt < 1.10)
    {
        Serial.println("Chuva de grande intensidade.");
        chuva = 3;
    }
    else
    {
        Serial.println("ERRO! Problema na leitura do sensor: o input analogico nao se encontra dentro da faixa de tensao permitida.");
        chuva = 4;
    }
    return chuva;
}