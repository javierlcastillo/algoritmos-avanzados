// Codigo base de act11.cpp adaptado por Gemini
// Javier Luis Castillo Solorzano
// A01658415
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

struct DisjointSets{
	int *parent, *rank;
	int n;
	DisjointSets(int n){
		this->n = n;
		parent = new int[n];
		rank = new int[n];
		for (int i=0; i<n; i++){
			rank[i] = 0;
			parent[i] = i;
		}
	}

	int find(int u){
		if (u != parent[u]){
			parent[u] = find(parent[u]);
		}
		return parent[u];
	}

	// merge por rank
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


struct Graph{
	int V, E;
	long long total_cost;
	vector<pair<int, pair<int, int>>> edges;

	Graph(int V, int E){
		this->V = V;
		this->E = E;
		total_cost = 0;
	}

    void addEdge(int u, int v, int w){
		edges.push_back({w, {u, v}});
	}

    void llenarCarreteras(){
        int a, b, c;
        for (int i = 0; i < E; i++){
            cin >> a >> b >> c;
            addEdge(a-1 , b-1, c);
        }
    }

    void kruskalMST(){
        sort(edges.begin(), edges.end());
        DisjointSets ds(V);
        total_cost = 0;
        int edges_count = 0;

        for(auto it:edges){
            int u = it.second.first;
            int v = it.second.second;
            int w = it.first;

            int p1 = ds.find(u);
            int p2 = ds.find(v);

            if(p1 != p2){
                total_cost += w;
                ds.merge(u, v);
                edges_count++;
            }
        }
        if (V > 0 && edges_count != V - 1) {
            total_cost = -1;
        }
    }
};


int main(){
    int ciudades, carreteras;
    cin >> ciudades >> carreteras;
    Graph g(ciudades, carreteras);
    g.llenarCarreteras();
    
    g.kruskalMST();

    if (g.total_cost == -1){
        cout << "IMPOSSIBLE" << endl;
    } else {
		cout << g.total_cost << endl;
    }
    
    return 0;
}