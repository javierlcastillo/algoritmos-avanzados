// Javier Luis Castillo
// A01658415
// Bases del codigo obtenido de GeeksForGeeks en la act pasada

#include <iostream> 
#include <vector>
#include <queue>
#include <climits> // Para INT_MAX

using namespace std;

// Aristass
struct Edge {
    int v; 
    int flow; 
    int C; 
    int rev;
};

struct Graph {
    int V; 
    int* level; //Nivel del nodo
    vector<Edge>* adj;

    Graph(int V)
    {
        adj = new vector<Edge>[V]; //lista de adj
        this->V = V;
        level = new int[V];
    }

    void addEdge(int u, int v, int C)
    {
        // Forward edge : 0 flow and C capacity
        Edge a{ v, 0, C, (int)adj[v].size() };

        // Back edge : 0 flow and 0 capacity
        Edge b{ u, 0, 0, (int)adj[u].size() };

        adj[u].push_back(a);
        adj[v].push_back(b); // reverse edge
    }

    bool BFS(int s, int t);
    int sendFlow(int s, int flow, int t, int ptr[]);
    int DinicMaxflow(int s, int t);
};

// Asignacion de niveles de nodo
// Flujo de s -> t 
bool Graph::BFS(int s, int t)
{
    for (int i = 0; i < V; i++)
        level[i] = -1;

    level[s] = 0; // Level of source vertex

    queue<int> q;
    q.push(s);

    vector<Edge>::iterator i; 
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // recorremos lista de adj
        for (i = adj[u].begin(); i != adj[u].end(); i++) {
            Edge& e = *i;
            if (level[e.v] < 0 && e.flow < e.C) {
                // Level of current vertex is,
                // level of parent + 1
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
    }
    // si no llegamos a destino se devuelve true
    return level[t] < 0 ? false : true;
}

// A DFS based function to send flow after BFS has
// figured out that there is a possible flow and
// constructed levels. This function called multiple
// constructed levels. This function is called multiple
// times for a single call of BFS.
// flow : Current flow send by parent function call
// start[] : To keep track of next edge to be explored.
//           start[i] stores  count of edges explored
//           from i.
//  u : Current vertex
//  t : Sink
//  t : Sink (destino)

// Funcion DFS
int Graph::sendFlow(int u, int flow, int t, int start[])
{
    // Sink reached
    if (u == t)
        return flow;

    // Trecorrido de lista de adj
    for (; start[u] < adj[u].size(); start[u]++) {
        Edge& e = adj[u][start[u]];

        if (level[e.v] == level[u] + 1 && e.flow < e.C) {
            int curr_flow = min(flow, e.C - e.flow);
            int temp_flow = sendFlow(e.v, curr_flow, t, start);

            if (temp_flow > 0) {
                // agrega flujo a edge
                e.flow += temp_flow;
                
                // elimina el flujo de reverse edge
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }

    return 0;
}

// O(V^2 E)
int Graph::DinicMaxflow(int s, int t)
{
    if (s == t)
        return -1;

    int total = 0; // resultado

    // se busca el flujo mientras sea posible llegar de s-> t
    while (BFS(s, t) == true) {
        // se guarda cuantos nodos se visitan
        int* start = new int[V + 1]{ 0 };

        while (int flow = sendFlow(s, INT_MAX, t, start)) {
            total += flow;
        }
          delete[] start;
    }

    return total;
}

int main()
{
    int n, m;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; i++){
        int u, v, c;
        cin >> u >> v >> c;
        g.addEdge(u - 1, v - 1, c);
    }
    cout << "The maximum speed is " << g.DinicMaxflow(0, n-1) << "." << endl; 
    return 0;
}