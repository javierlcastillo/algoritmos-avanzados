/* Para hacer el manejo de encender o apagar un bit, se utilizan las siguientes operaciones: 
 *      b|(1<<i)  -> recorremos el 00000001 a donde queramos apaagar
 *      para encender es b|&NOT(1<<i)  -> donde recorremos el 0000001 y le hacemos un and not con b
 *      ej: 
 *              b=01001000          i = 5 (de derecha a izq)
 *              
 */

#include <iostream>

using namespace std;

typedef unsigned char uchar;

// Enciende el pos bit de mask
uchar add(uchar mask, int pos){
    return (mask | (1 << pos));
}

// Apaga el pos bit de mask
uchar remove(uchar mask, int pos){
    return (mask & ~ (1 << pos));
}

// Pregunta si esta encendido o no el bit en mask
bool test(uchar mask, int pos){
    return ((mask & (1 << pos)) != 0); 
}

void print(uchar mask){
    for(int i = 7; i >= 0; i--){
        cout << test(mask, i) ? "1" : "0" ;
    }
    cout << endl;
}

int main(){
    // Pruba de corrimientos
    // ---------------------
    // long dato1, dato2;
    // int  corr;
    // cin >> dato1;
    // cin >> corr;
    // dato2 = dato1;
    // dato1 = dato1 << corr;
    // cout << dato1 << endl;
    // dato2 = dato2 >> corr;
    // cout << dato2 << endl;

    int pos; 
    uchar b = 11;
    print(b); 
    cout << "cual bit prendo?";
    cin >> pos;
    b = add(b, pos);
    print(b);
    cout << "Cual bit apago?";
    cin >> pos;
    b = remove(b, pos);
    print(b);
    uchar b2 = 27;
    print(b2);
    b2 = b2 << 4;
    print(b2);
    b2 = b2 >> 5;
    print(b2);
    return 0;


}