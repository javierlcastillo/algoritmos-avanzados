// Javier Luis Castillo Solorzano
// A01658415

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cfloat>
#include <iomanip>
#include <string>

using namespace std;


struct Point{
    float x, y;
    string name;
    Point(){
        x = y = 0;
        name = "";
    }
    Point(float x_, float y_, string name_){
        this -> x = x_;
        this -> y = y_;
        this -> name = name_;
    }
};

bool compareX(const Point &p1, const Point &p2){
    return p1.x < p2.x;
}
bool compareY(const Point &p1, const Point &p2){
    return p1.y < p2.y;
}


float dist(Point &p1, Point &p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

float stripClosest(vector<Point> &strip, float dMenor, float &minDistance, Point &bestP1, Point &bestP2){
    float min_strip = dMenor;
    sort(strip.begin(), strip.end(), compareY);
    for (int i = 0; i < strip.size(); i++){
        for (int j = i+1; j < strip.size() && (strip[j].y - strip[i].y) < min_strip; j++){
            float d = dist(strip[i], strip[j]);
            if (d < min_strip){
                min_strip = d;
                if (min_strip < minDistance) {
                    minDistance = min_strip;
                    bestP1 = strip[i];
                    bestP2 = strip[j];
                }
            }
        }
    }
    return min_strip;
}

float bruteForce(vector<Point> &P, int ini, int fin, float &minDistance, Point &bestP1, Point &bestP2){
    float min_aux = FLT_MAX;
    for (int i = ini; i <= fin; i++){
        for (int j = i+1; j <= fin; j++){
            float d = dist(P[i], P[j]);
            if (d < min_aux) {
                min_aux = d;
            }
            if (d < minDistance) {
                minDistance = d;
                bestP1 = P[i];
                bestP2 = P[j];
            }
        }
    }
    return min_aux; 
}

float closest_Helper(vector<Point> &P, int ini, int fin, float &minDistance, Point &bestP1, Point &bestP2){
    if (fin-ini < 3){
        return bruteForce(P, ini, fin, minDistance, bestP1, bestP2);
    }
    int mid = ini + (fin - ini)/2;
    Point midPoint = P[mid];
    float d_izq = closest_Helper(P, ini, mid, minDistance, bestP1, bestP2);
    float d_der = closest_Helper(P, mid+1, fin, minDistance, bestP1, bestP2);
    float dMenor = min(d_izq, d_der);
    vector<Point> strip; 
    for (int i = ini; i <= fin; i++){
        if(abs(P[i].x - midPoint.x) < dMenor){
            strip.push_back(P[i]);
        }
    }
    return min(dMenor, stripClosest(strip, dMenor, minDistance, bestP1, bestP2));
}

// Complejidad O(n logn)
void closest(vector<Point> &P, float &minDistance, Point &bestP1, Point &bestP2){
    sort(P.begin(), P.end(), compareX);
    closest_Helper(P, 0, P.size()-1, minDistance, bestP1, bestP2);
}

int main(){
    Point bestP1, bestP2;
    float minDistance = FLT_MAX;
    int n;
    cin >> n; 
    vector<Point> P;
    for (int i = 0; i <n; i++){
        string name;
        float x, y;
        cin >> name >> x >> y;
        P.push_back(Point(x, y, name));
    }
    
    closest(P, minDistance, bestP1, bestP2);

    if (bestP1.name > bestP2.name){
        swap(bestP1, bestP2);
    }
    
    cout << setprecision(2) << fixed;
    cout << "Best friend in BeagleTown are: " << bestP1.name << " & " << bestP2.name << " (" << minDistance << ")" << endl;

    return 0; 
}
/*
5
Sparko 5 10
Rocky 2 30
Prue 1 15
Nico 10 2
Nerea 20 5
*/
