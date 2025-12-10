#include <iostream>
#include <vector>
#include <algorithm>

const long long INF = 1e18;
using namespace std;

struct Graph{
    int n, m;
    vector<vector<long long>> matAdj;

    Graph(int n, int m){
        this->n = n;
        this->m = m;
        initMatAdj();
    }

    void initMatAdj (){
        matAdj.assign(n, vector<long long>(n, INF));
        for (int i = 0; i < n; i++){
            matAdj[i][i] = 0;
        }
    }

    void leeDatos() {
        int u, v, w;
        for (int i = 0; i < m; i++){
            cin >> u >> v >> w;
            matAdj[u - 1][v - 1] = min(matAdj[u - 1][v - 1], (long long)w);
        }
    }

    void Floyd(){
        for(int k = 0; k < n; k++){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if (matAdj[i][k] != INF && matAdj[k][j] != INF) {
                        matAdj[i][j] = min(matAdj[i][j], matAdj[i][k] + matAdj[k][j]);
                    }
                }
            }
        }
    }

    void solucion(){
        for (int i = 0; i < n; i++){
            cout << matAdj[0][i] << " ";
        }
        cout << endl;
    }
};

int main(){
    int n, m;
    cin >> n >> m;
    Graph g(n, m);
    g.leeDatos();
    g.Floyd();
    g.solucion();

    return 0;
}