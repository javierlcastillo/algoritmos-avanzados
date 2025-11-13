// Javier Luis Castillo 
// A01658415 

#include <iostream>
#include <vector>

using namespace std;

struct obj{
    int valor, paginas;
};

int MochilaDP(vector<obj> &datos, int N, int GASTO){
    vector<int> dp (GASTO+1, 0);
    for(int i = 0; i < N; i++){
        for (int j = GASTO; j >= datos[i].valor; j--){
            dp[j] = max(dp[j], datos[i].paginas + dp[j - datos[i].valor]);
        }
    }
    return dp[GASTO];
}

void llenarLibros(int n, int p, vector<obj> &libros){
    int price, pages;
    for (int i = 0; i < libros.size(); i++){
        cin >> price;
        libros[i].valor = price;
    }
    for (int i = 0; i < libros.size(); i++){
        cin >> pages;
        libros[i].paginas = pages;
    }
}
int solucion(int n, int p){
    vector<obj> libros(n);
    llenarLibros(n,p,libros);
    return  MochilaDP(libros, n, p);
}
int main(){
    int n, p;
    cin >> n >> p;
    cout << solucion(n, p);
    return 0; 
}