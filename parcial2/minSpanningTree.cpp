/* -> Algoritmo de PRIM
   El objetivo es buscar un conjunto de nodos en donde puedo generar
   un arbol con la menor expansion posible, sin ciclos. 
   
   Tiene 3 arreglos: S -> la solucion [arreglo de pairs en conexiones de nodos],
    Y -> nodos reecorridos, V-Y -> nodos por recorrer.
   La idea es ir buscando el menor costo posible entre cualquiera de los nodos
   -----------------------------------------------------------------------------
   -----------------------------------------------------------------------------
   */

/* -> Algoritmo de kruskal 
   El algoritmo de Kruskal, a diiferencia del de PRIM se basa en los arcos, e vez
   de en los nodos.*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <climits>
#include <queue>

#define INF INT_MAX

using namespace std;

struct Graph{
	// V = Cantidad de nodos (Vertex)
	// E = Cantidad de Arcos (Edges)
	int V, E, costMSTPrim, costMSTKruskal;
	vector<pair<int, pair<int, int>>> edges;	// Utilizar en Kruskal
	vector<vector<pair<int, int>>> adjList;		// Lista de Adj utilizado en Prim
	vector<pair<int, int>> selectedEdgesK;		// Arcos seleccionados por Kruskal
	vector<pair<int, int>> selectedEdgesP;		// Arcos seleccionados por Prim
	Graph(int V, int E){
		this->V = V;
		this->E = E;
		adjList.resize(V);
		costMSTKruskal = costMSTPrim = 0;
	}
	// u = salida del arco
	// v = llegada del arco
	// w = costo del arco

	void addEdge(int u, int v, int w){ // -> u vetice1, v vertice2, w costo
		//edges.push_back({w, {u, v}}); // -> utilizado en kruskal: first = costo, second = conexión
		adjList[u].push_back({v,w}); // -> utilizado en PRIM: pair<vertice2,costo>
		adjList[v].push_back({u,w}); // -> utilizado en PRIM: pair<vertice2,costo>

	}
	void load();
	void print();
	void kruskalMST();
	int primMST();
	void printEdgesP();
	void printEdgesK();
	vector<int> dijkstra(int s);
};


//Disjoint Sets (Union-Find)
struct DisjointSets{
	int *parent, *rank;
	int n;
	DisjointSets(int n){
		this->n = n;
		parent = new int[n+1];
		rank = new int[n+1];
		for (int i=0; i<=n; i++){
			rank[i] = 0;
			parent[i] = i;
		}
	}
	// Para encontrar el parent de 'u'
	int find(int u){
		if (u != parent[u]){
			parent[u] = find(parent[u]);
		}
		return parent[u];
	}
	void merge(int x, int y){
		x = find(x);
		y = find(y);
		if (rank[x] > rank[y]){
			parent[y] = x;
		}
		else{
			parent[x] = y;
		}
		if (rank[x] == rank[y]){
			rank[y]++;
		}
	}
};

void Graph::load(){
	char u_char, v_char;
	int u, v, w;
	for (int i=0; i<E; i++){
		cin >> u_char >> v_char >> w;
		u = u_char - 'A';
		v = v_char - 'A';
		addEdge(u, v, w);
	}
}

void Graph::print(){
	cout << "Adjacent List: " << endl;
	for (int i=0; i<V; i++){
		cout << i << ": ";
		for (int j=0; j<adjList[i].size(); j++){
			cout << "(" << adjList[i][j].first << ", " << adjList[i][j].second << ") ";
		}
		cout << endl;
	}
}

// Complejidad: O(N^2)]
int Graph::primMST(){
	int selSource = 0;
	costMSTPrim = 0; 
	unordered_set<int> selected;
	unordered_set<int> missing;
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
			}
		}
		costMSTPrim += minCost;
		selected.insert(selVertex);
		missing.erase(selVertex);
		selectedEdgesP.push_back({selSource, selVertex});
		connected--;
	}
	return selVertex;
}

// O(E logV)
vector<int> Graph::dijkstra(int s){
    vector<int> dist(V, INF);
    dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s}); // {cost, vertex}

    while (!pq.empty()){
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for(auto& edge : adjList[u]){
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

void Graph::printEdgesP(){
	cout << "Selected Edges Prim: ";
	for (auto it:selectedEdgesP){
		cout << "(" << it.first << ", " << it.second << ") ";
	}
	cout << endl;
}

// Complejiodad: O(E logE)
void Graph::kruskalMST(){
	sort(edges.begin(), edges.end());
	DisjointSets ds(V);
	costMSTKruskal = 0;
	for(auto it:edges){
		int p1 = ds.find(it.second.first);
		int p2 = ds.find(it.second.second);
		if(p1 != p2){
			costMSTKruskal += it.first;
			selectedEdgesK.push_back({it.second});
			ds.merge(it.second.first, it.second.second);
		}
	}
}

void Graph::printEdgesK(){
	cout << "Selected Edges Kruskal: ";
	for (auto it:selectedEdgesK){
		cout << "(" << it.first << ", " << it.second << ") ";
	}
	cout << endl;
}

void demostracionClase(){
	int V, E;
	cin >> V >> E;
	Graph g(V, E);
	g.load();
	// g.print();
	g.primMST();
	cout << "Costo total de MST por Prim es: " << g.costMSTPrim << endl;
	g.printEdgesP();
	g.kruskalMST();
	cout << "Costo total de MST por Kruskal es: " << g.costMSTKruskal << endl;
	g.printEdgesK();
}

int main(){
	int N, M; // N = numero de casas - M = numero de caminos;
	cin >> N >> M; 
	Graph g(N, M);
	g.load();
	int nodo = g.primMST();
	vector<int> djk = g.dijkstra(nodo);

	// Lo que hice fue encontar el mst, y basado en el ultimo nodo nodo que recorrio el algoritmo
	// aplique un djikstra para encontrar el camino mas corto de vuelta a casa.
	cout << djk[0] + g.costMSTPrim << endl;
	// cout << "Costo total de MST por Prim es: " << g.costMSTPrim << endl;
	// cout << "El ultimo nodo es: " << nodo << endl;
	// vector<int> djk = g.dijkstra(nodo);
	// cout << "El valor de regreso es: " << djk[0] << endl; 
	return 0;
}



/* Unidrected Graph
9 14
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 8 2
2 5 4
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7
*/