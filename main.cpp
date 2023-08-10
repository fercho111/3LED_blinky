/* Ejemplo 3LED_bliny para cusos universitarios
 */

#include "mbed.h"
#include <iostream>


// Periodo de parpadeo máximo común divisor - MCD - para los LEDs del LED RGB  
#define BLINKING_PERIOD     20
#define BLINKING_UNITS      "ms"
#define BLINKING_RATE       20ms    // Falta concatenación de BLINKING_PERIOD y BLINKING_UNITS 
// Periodos de parpadeo adimensionalizados de los LEDs: Tx = LEDx_PERIOD * BLINKING_RATE 
#define LEDR_PERIOD         5
#define LEDG_PERIOD         7
#define LEDB_PERIOD         11
// Objeto para establecer la comunicación serial con el Pc
UnbufferedSerial serial(USBTX, USBRX, 9600);
using namespace std;

int mcm(int a, int b);
int mcm(int a, int b, int c);

int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut ledR(LED1, 1);
    DigitalOut ledG(LED2, 1);
    DigitalOut ledB(LED3, 1);
    // Variable contador - periodos del mcm de los LEDs
    int count = 0;
    int ledr_period;
    int ledg_period;
    int ledb_period;

    cout << "Por favor ingrese el periodo de parpadeo del led rojo" << endl;
    cin >> ledr_period;
    cout << "Usted ingreso" << ledr_period << endl;

    cout << "Por favor ingrese el periodo de parpadeo del led verde" << endl;
    cin >> ledg_period;
    cout << "Usted ingreso" << ledg_period << endl;

    cout << "Por favor ingrese el periodo de parpadeo del led azul" << endl;
    cin >> ledb_period;
    cout << "Usted ingreso" << ledb_period << endl;

    int blinky = mcm(ledr_period, ledb_period, ledg_period);

    cout << blinky << endl;

    while (true) {
        if(count % ledr_period == 0) {
            ledR = !ledR;
            cout << "LedR = " << count * BLINKING_PERIOD << BLINKING_UNITS << endl;
        }
        if(count % ledg_period == 0) {
            ledG = !ledG;
            cout << "LedG = " << count * BLINKING_PERIOD << BLINKING_UNITS << endl;
        }
        if(count % ledb_period == 0) {
            ledB = !ledB;
            cout << "LedB = " << count * BLINKING_PERIOD << BLINKING_UNITS << endl;
        }

        ThisThread::sleep_for(static_cast<uint32_t>(blinky));
        count += 1;
    }
}

int mcm(int a, int b) {
    if (b == 0)
        return a;
    return mcm(b, a % b);
}

// Function to calculate the least common multiple (LCM) of three integers
int mcm(int a, int b, int c) {
    int gcd_of_ab = mcm(a, b);
    int gcd_of_abc = mcm(gcd_of_ab, c);

    int lcm = (a * b * c) / gcd_of_abc;
    return lcm;
}