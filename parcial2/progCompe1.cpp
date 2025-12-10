// Javier Luis Castillo

#include <iostream>

using namespace std;

int solucion(int n, int d, string l){
    int next = -1;
    int i = 0;
    int contador = 0;
    while (i < n-1){
        //cout << "i: " << i << endl; 
        for (int j = d; j >= 1; j--){
            if (l[i+j] == '1'){
                next = i+j;
                //cout << "Found a jump on [" << i+j << "]" << endl;
                break;
            } else
                next = -1;
        }
        if (next != -1){
            //cout << "Next: " << next << endl;
            i = next;
            contador++;
        }else
            return -1;
    }
    return contador;
    

}

int main(){
    int n, d;
    string lillies;
    cin >> n >> d; 
    cin >> lillies;
    cout << solucion(n, d, lillies) << endl;
    return 0;
}

// 10010101 -> 4

// 101111100101 -> 3