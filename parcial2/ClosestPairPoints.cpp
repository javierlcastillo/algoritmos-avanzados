// Javier Luis Castillo
// A017¿658415
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cfloat>
#include <iomanip>

using namespace std;

struct Point{
    float x, y;
    Point(){
        x = y = 0;
    }
    Point(float x_, float y_){
        this -> x = x_;
        this -> y = y_;
    }
};

bool compareX(const Point &p1, const Point &p2){
    return p1.x < p2.x;
}
bool compareY(const Point &p1, const Point &p2){
    return p1.y < p2.x;
}


float dist(Point &p1, Point &p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

float stripClosest(vector<Point> &strip, float dMenor){
    float min_strip = FLT_MAX;
    sort(strip.begin(), strip.end(), compareY);
    for (int i = 0; i < strip.size(); i++){
        for (int j = i+1; j < strip.size(); j++){
            min_strip = min(min_strip, dist(strip[i], strip[j]));
        }
    }
    return min_strip;
}

float bruteForce(vector<Point> &P, int ini, int fin){
    float min_aux = FLT_MAX;
    for (int i = ini; i < fin; i++){
        for (int j = i+1; j <= fin; j++){
            min_aux = min(min_aux, dist(P[i], P[j]));
        }
    }
    return min_aux; 
}

float closest_Helper(vector<Point> &P, int ini, int fin){
    if (fin-ini < 3){
        return bruteForce(P, ini, fin);
    }
    int mid = (fin - ini)/2;
    Point midPoint = P[mid];
    float d_izq = closest_Helper(P, ini, mid);
    float d_der = closest_Helper(P, mid+1, fin);
    float dMenor = min(d_izq, d_der);
    vector<Point> strip; 
    for (int i = ini; i <= fin; i++){
        if(abs(P[i].x - midPoint.x) < dMenor){
            strip.push_back(P[i]);
        }
    }
    float ds = stripClosest(strip, dMenor);
    return ds;
}

// Complejidad O(n logn)
float closest(vector<Point> &P){
    sort(P.begin(), P.end(), compareX);
    return closest_Helper(P, 0, P.size()-1);
}

int main(){
    // n = cant puntos
    int n;
    float x, y;
    cin >> n; 
    vector<Point> P(n);
    for (int i = 0; i <n; i++){
        cin >> x >> y;
        P[i].x = x;
        P[i].y = y;
    }
    float d = closest(P);
    cout << setprecision(2) << fixed;
    cout << "La distancia menor es de: " << d << endl;
    return 0; 
}
/*
5
5 10
2 30
1 15
10 2
20 5
*/