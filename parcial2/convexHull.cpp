// Javier luis castillo
//A01658415

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;


struct Point {
    int x, y;
    Point(){
        x = y = 0;
    }
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }


};

Point p0;

//Distancia entre 2 puntos.
int distSq(Point &p1, Point &p2){
    return ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// 0==> P0.P1, P2
// 1 == A FAVOR DE LAS MANECILLAS
// 2 ==> EN CONTRA DE LAS MANECILLAS

int orientation(Point &p0, Point &p1, Point &p2){
    int v = (p1.y - p0.y) * (p2.x - p1.x) - (p1.x - p0.x) * (p2.y - p1.y);
    if (v == 0){
        return 0;
    }
    return (v > 0 ? 1: 2);
}


//Comparar 2 puntos
bool compare (Point &p1, Point &p2){
    int origen = orientation(p0, p1, p2);
    if (origen == 0){
        return (distSq(p0, p2) >= distSq(p0, p1));

    }
    return (origen == 2);

}
// cual es el tope del tope
Point nextToTop(stack<Point> &s){
    Point p = s.top();
    s.pop();
    Point resp = s.top();
    s.push(p);
    return resp;

} 

//Complejidad O(n logn)
void convex_hull(vector<Point> &points){
    int n = points.size();
    // Localizar al punto pivote.
    int yMin = points[0].y, minID = 0, x, y;
    for (int i = 1; i < n; i++){
         x = points[i].x;
         y = points[i].y;
        if (y < yMin || y == yMin &&  x < points[minID].x){
            yMin = y;
            minID = i;
        }
    }
    Point temp = points[0];
    points[0] = points[minID];
    points[minID] = temp;
    p0 = points[0];

    // Ordenrar puntos de acurdoal pivote dependiendo del angulo
    sort(points.begin() + 1, points.end(), compare);
    int m = 1;
    for (int i = 1; i < n; i++){
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0){
            i++;
        }
        points[m++] = points[i];
    }
    if (m < 3){
        cout << "No hay Poligono" << endl;
        return;
    }

    stack<Point> s;
    s.push(points[0]);
    s.push(points[1]);
    s.push(points[2]);
    for (int i = 3; i < m; i++){
        Point nTT = nextToTop(s);
        while (s.size() > 1 && orientation(nTT, s.top(), points[i]) != 2){

            s.pop();
            nTT = nextToTop(s);
            
        }
        s.push(points[i]);

    }

    while (!s.empty()){
        Point p = s.top();
        cout << "(" << p.x << ", " << p.y  << ")" << endl;
        s.pop();
    }
}

int main(){


    vector<Point> points;
    int n, x, y;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> x >> y;
        points.push_back(Point(x, y));
    }

    convex_hull(points);

    return 0;
}