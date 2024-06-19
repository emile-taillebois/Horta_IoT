/*=== Cabeçalho ==============================================*/
#include <cd74hc4067ET.h>

/*=== Inicialização de constantes externas ===================*/

/*--- Códigos de seleção da pinagem do multiplexador ---------*/
const int C0 [4] = {0,0,0,0};
const int C1 [4] = {1,0,0,0};
const int C2 [4] = {0,1,0,0};
const int C3 [4] = {1,1,0,0};
const int C4 [4] = {0,0,1,0};
const int C5 [4] = {1,0,1,0};
const int C6 [4] = {0,1,1,0};
const int C7 [4] = {1,1,1,0};
const int C8 [4] = {0,0,0,1};
const int C9 [4] = {1,0,0,1};
const int C10 [4] = {0,1,0,1};
const int C11 [4] = {1,1,0,1};
const int C12 [4] = {0,0,1,1};
const int C13 [4] = {1,0,1,1};
const int C14 [4] = {0,1,1,1};
const int C15 [4] = {1,1,1,1};

/* In C++, const global variable definitions have internal linkage by default, while non-const global variable definitions have external linkage by default. Thus, when defining const global variables to be used in external functions, their linkage must be set to external manually in header. Besides, in C++, const doesn't (necessarily) creates an object in memory, being able to act just like a #define (but with type and scope).*/

/*=== Inicialização de constantes internas ===================*/

/*--- Configuração das pinagens para uso do multiplexador ----*/
const int s0 = D5;
const int s1 = D6;
const int s2 = D7;
const int s3 = D8;
const int SIG = A0;
const int controlPin[] = {s0, s1, s2, s3};

/*=== Inicialização de variáveis externas ====================*/

/*--- Inicialização das variáveis de saída analógica ---------*/
int analogInBin = 0;
float analogInVolt = 0.0;

/*=== Inicialização de variáveis internas ====================*/

/*=== Definição das funções ==================================*/

/*--- Função para setup inicial do multiplexador -------------*/
void setupMP()
{
    /*--- Definição dos modos das pinagens de controle -------*/
    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
    /*--- Definição do modo padrão das pinagens de controle --*/
    digitalWrite(s0, LOW);
    digitalWrite(s1, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
}

/*--- Função para leitura analógica do multiplexador ---------*/
void AnalogReadMP(const int channel[4])
{
    for(int i = 0; i < 4; i ++) // for(variável, condição, incremento)
    {
        digitalWrite(controlPin[i], channel[i]);
    }
    analogInBin = analogRead(SIG);
    analogInVolt = (analogRead(SIG) * 3.3)/1024.0;
}

/* Na função acima, criei uma função void (que a princípio não possui retorno), mas usei duas variáveis definidas de forma global (extern) para devolver a leitura binária da saída analógica e sua conversão em voltagem. Dessa forma consigo usar funções void e mesmo assim obter diversos retornos da minha função. Com esse tipo de técnica consigo construir funções que devolvem mais de um valor, o que o cpp a princípio não permite. 

No caso das saídas serem do mesmo tipo teríamos outra alternativa: posso criar uma array e construir a função como sendo do tipo ponteiro: https://www.digitalocean.com/community/tutorials/return-array-in-c-plus-plus-function . Nesse caso, o ponteiro do return aponta para a minha array.*/