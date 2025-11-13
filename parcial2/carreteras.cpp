// Javier Luis Castillo Solorzano
// A01658415
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <climits>
#include <queue>

#define INF INT_MAX

using namespace std;


struct Graph{
	// V = Cantidad de nodos (Vertex)
	// E = Cantidad de Arcos (Edges)
	int V, E, costMSTPrim, costMSTKruskal, presupuesto;
	vector<pair<int, pair<int, int>>> edges;	// Utilizar en Kruskal
	vector<vector<pair<int, int>>> adjList;		// Lista de Adj utilizado en Prim
	vector<pair<int, int>> selectedEdgesK;		// Arcos seleccionados por Kruskal
	vector<pair<int, int>> selectedEdgesP;		// Arcos seleccionados por Prim
	Graph(int V, int E){
		this->V = V;
		this->E = E;
		adjList.resize(V);
		costMSTKruskal = costMSTPrim = presupuesto = 0;
	}
	// u = salida del arco
	// v = llegada del arco
	// w = costo del arco
    void addEdge(int u, int v, int w){ // -> u vetice1, v vertice2, w costo
		edges.push_back({w, {u, v}}); // -> utilizado en kruskal: first = costo, second = conexión
		adjList[u].push_back({v,w}); // -> utilizado en PRIM: pair<vertice2,costo>
		adjList[v].push_back({u,w}); // -> utilizado en PRIM: pair<vertice2,costo>
	}

    void llenarCarreteras(){
        int a, b, c;
        for (int i = 0; i < E; i++){
            cin >> a >> b >> c;
            addEdge(a-1 , b-1, c);
        }
    }

    void print(){
	cout << "Adjacent List: " << endl;
	for (int i=0; i<V; i++){
		cout << i << ": ";
		for (int j=0; j<adjList[i].size(); j++){
			cout << "(" << adjList[i][j].first + 1 << ", " << adjList[i][j].second + 1 << ") ";
		}
		cout << endl;
	}
    }

    void primMST(){
	int selSource = 0;
	costMSTPrim = 0; 
	unordered_set<int> selected;
	unordered_set<int> missing;
    unordered_map<int, pair<int, int>> sobrantes;
    queue<pair<int, pair<int,int>>> sobrantess; // <source, <arrival, costo>>
    int minimo_sobrante = INF;
	selected.insert(0);
	for(int i=1; i<V; i++) {
		missing.insert(i);
	}
	int connected = V-1, minCost, selVertex; 
	while (connected) {
		minCost = INF;
		for(auto it1:selected){
			for(auto it2: adjList[it1]){
				if(missing.find(it2.first) != missing.end() && it2.second < minCost){
					minCost = it2.second;
					selVertex = it2.first;
					selSource = it1;
				} 
                // else{
                //     sobrantes[it2.second] = {it1, it2.first};
                //     sobrantess.push({it1, {it2.first, it2.second}});
                //     if (it2.second < minimo_sobrante){
                //         minimo_sobrante = it2.second;
                //     }
                // }
			}
		}
		costMSTPrim += minCost;
		selected.insert(selVertex);
		missing.erase(selVertex);
		selectedEdgesP.push_back({selSource, selVertex});
		connected--;
	}
    // int presupuesto_restante = presupuesto - costMSTPrim; 
    // pair<int, pair<int,int>> temp;
    // while (!sobrantess.empty()){
    //     //selectedEdgesP.push_back(sobrantes.find(minimo_sobrante));
    //     temp = sobrantess.front();
    //     if (temp.second.second < presupuesto_restante){
    //             selectedEdgesP.push_back({temp.first ,temp.second.first});
    //     }
    //     sobrantess.pop();
    //     }
    //     // selected.instert(sobrantess)
    //     minimo_sobrante = 100;

	//return selVertex;
    }

    void printEdgesP(){
	cout << "Selected Edges Prim: ";
	for (auto it:selectedEdgesP){
		cout << "(" << it.first + 1 << ", " << it.second +1  << ") ";
	}
	cout << endl;
}
};


int main(){
    int ciudades, carreteras, presupuesto;
    cin >> ciudades >> carreteras;
    Graph g(ciudades, carreteras);
    g.llenarCarreteras();
    cin >> presupuesto;
    g.presupuesto = presupuesto;
    g.primMST();
    if (g.costMSTPrim > g.presupuesto){ // si el presupuesto es menor, devuelve imposible
        cout << "IMPOSIBLE" << endl;
    } else {
        g.printEdgesP();
        cout << "sobraron " << g.costMSTPrim - g.presupuesto << "." << endl;
    }
    // NO LOGRE MANEJAR BIEN LOS NODOS SOBRANTES. la idea es recorrer los nodos sobrantes que tienen costo menor al presupuesto
    // restante. To be continued...
    
    return 0;
}