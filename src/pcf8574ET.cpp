/*=== Cabeçalho ==============================================*/
#include <pcf8574ET.h>

/*=== Informações sobre o PCF8574 ============================*/
/* The IO pins on this device are all quasi-bidirectional. A quasi-bidirectional I/O is either an input or output port without using a direction control register (ou seja, não rpecisamos iniciar as saídas P0 a P7 com OUTPUT ou INPUT). Driving the pin either weakly pulls the line up to Vdd or sinks the pin to GND. Reading the pin returns the actual status of the pin. In order to use a pin exclusively as an input, the pin should be driven HIGH (default at startup) so the pin remains weakly pulled to Vdd. The other device driving this pin should pull low for the device to read when called by the master.

When using the pins as inputs, the pins are set to HIGH by the MCU, which turns on a weak 100 uA internal pull-up to Vcc. They will read as HIGH if there is no input or if the pin is being driven HIGH by an external signal but can be driven LOW by an external signal that can easily override the weak pull-up.

If used as outputs, they can be driven LOW by the MCU by writing a LOW to that pin. A strong pull-down is turned on and stays on to keep the pin pulled LOW. If the pin is driven HIGH by the MCU, a strong pull-up is turned on for a short time to quickly pull the pin HIGH and then the weak 100uA pull-up is turned back on to keep the pin HIGH.

If the pins are set to be outputs and are driven LOW, it is important that an external signal does not also try to drive it HIGH or excessive current may flow and damage the part.

Informações sobre o uso do PCF8574 podem ser obtidas em: https://www.youtube.com/watch?v=uE9tPkjEj8A */

/*=== Inicialização de constantes externas ===================*/

/*--- Constantes de OUTPUT para as pinagens do PCF8574 -------*/
const unsigned char P0 = 0xFE; /* 11111110 em binário */
const unsigned char P1 = 0xFD; /* 11111101 em binário */
const unsigned char P2 = 0xFB; /* 11111011 em binário */
const unsigned char P3 = 0xF7; /* 11110111 em binário */
const unsigned char P4 = 0xEF; /* 11101111 em binário */
const unsigned char P5 = 0xDF; /* 11011111 em binário */
const unsigned char P6 = 0xBF; /* 10111111 em binário */
const unsigned char P7 = 0x7F; /* 01111111 em binário */
const unsigned char ALLLOW = 0x00;
const unsigned char ALLHIGH = 0xFF;

/* In C++, const global variable definitions have internal linkage by default, while non-const global variable definitions have external linkage by default. Thus, when defining const global variables to be used in external functions, their linkage must be set to external manually in header. Besides, in C++, const doesn't (necessarily) creates an object in memory, being able to act just like a #define (but with type and scope).*/

/* ALLHIGH é o padrão ao iniciar o PCF8574, tanto em modo INPUT quanto OUTPUT. Isso é bom para uso de relays ACTIVE LOW, que são ativados com sinal LOW e não HIGH. Os relays que funcionam da forma contrária, ou seja, que são ativados com sinal HIGH são chamados de ACTIVE HIGH.*/

/* O comando 0x indica que temos um número escrito em forma hexidecimal. Como estamos usando dois símbolos hexadecimais, os números representados são inteiros indo de 0 a 255. Essa é a razão pela qual usamos unsigned char e não int.*/

/* In C++, there are three distinct character types:
- char
- signed char
- unsigned char

If you are using character types for text, use the unqualified char:
- it is the type of character literals like 'a' or '0' (in C++ only, in C their type is int)
- it is the type that makes up C strings like "abcde"
- It also works out as a number value, but it is unspecified whether that value is treated as signed or unsigned. Beware character comparisons through inequalities - although if you limit yourself to ASCII (0-127) you're just about safe.

If you are using character types as numbers, use:
- signed char, which gives you at least the -127 to 127 range. (-128 to 127 is common)
- unsigned char, which gives you at least the 0 to 255 range.

The size of int and unsigned int is same, i.e 2 bytes for short and 4 bytes for long. They will differ only in which values to be used i.e the range. Example:
- short int ranges from -32768 to +32768
- unsigned short int ranges from 0 to 65535

The size of signed char and unsigned char is the same, i.e 1 byte . They will differ only in which values to be used i.e the range.Example:
- signed char ranges from -128 to +127
- unsigned char ranges from 0 to 255 */

/* Outras combinações podem ser usadas para porduzir output simultâneos de LOW nas portas do PCF8574. Por exemplo, poderíamos usar P0P1 = 0xFC (11111100 em binário) para enviar um sinal LOW para P0 e P1 ao mesmo tempo, enquanto as outras portas ficariam em HIGH. */

/*=== Inicialização de constantes internas ===================*/

/*=== Inicialização de variáveis externas ====================*/

/*=== Inicialização de variáveis internas ====================*/

/*=== Definição das funções ==================================*/

/*--- Função para escrita nos pinos do PCF8574 - OUTPUT ------*/
void WriteToPCF8574(unsigned char data) // Obs.: Se eu colocar const na definição do inout dessa função dá erro e eu não sei o porquê.
{
  Wire.beginTransmission(0x20); /* Slave addres - this address can be changed using the A0, A1 and A2 jumpers on PCF8574. */
  Wire.write(data);
  Wire.endTransmission();
}

/*--- Função para ler pinos do PCF8574 - INPUT ---------------*/