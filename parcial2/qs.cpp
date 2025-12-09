// Algoritmo de quicksort
// Autor: YO

#include <iostream>
#include <vector>

using namespace std;

// Tipo 1 ==> pivote = ini
void part1(vector<int> &v, int ini, int fin, int &piv){
	piv = ini;
	int temp;
	int j = ini; 	// j ==> el último de los menores;
	for (int k=ini+1; k<=fin; k++){
		if (v[k] < v[piv]){
			temp = v[++j];
			v[j] = v[k];
			v[k] = temp;
		}
	}
	piv = j;
	temp = v[ini];
	v[ini] = v[piv];
	v[piv] = temp;
}

// Tipo 2 ==> pivote = fin
void part2(vector<int> &v, int ini, int fin, int &piv){
	piv = ini;
	int temp = v[fin];
	v[fin] = v[ini];
	v[ini] = temp;
	int j = ini; 	// j ==> el último de los menores;
	for (int k=ini+1; k<=fin; k++){
		if (v[k] < v[piv]){
			temp = v[++j];
			v[j] = v[k];
			v[k] = temp;
		}
	}
	piv = j;
	temp = v[ini];
	v[ini] = v[piv];
	v[piv] = temp;
}
// Regresa el índice de la mediana
int median(vector<int> &v, int ini, int mid, int fin){
	if (v[ini] < v[mid] && v[mid] < v[fin]){
		return mid;
	}
	if (v[ini] < v[fin] && v[fin] < v[mid]){
		return fin;
	}
	return ini;
}

// Tipo 3 ==> pivote = mediana de ini, fin o medio
void part3(vector<int> &v, int ini, int fin, int &piv){
	int mid = (fin+ini)/2;
	int temp;
	if (ini+1 != fin){
		mid = median(v, ini, mid, fin); // Regresa el indice de la mediana
		temp = v[ini];
		v[ini] = v[mid];
		v[mid] = temp;
	}
	piv = ini;
	int j = ini; 	// j ==> el último de los menores;
	for (int k=ini+1; k<=fin; k++){
		if (v[k] < v[piv]){
			temp = v[++j];
			v[j] = v[k];
			v[k] = temp;
		}
	}
	piv = j;
	temp = v[ini];
	v[ini] = v[piv];
	v[piv] = temp;
}
void quicksort(vector<int> &v, int ini, int fin, long long &cont, int tipo){
	if (ini < fin){
		int piv;
		cont += (fin-ini);
		switch (tipo){
			case 1: part1(v, ini, fin, piv);
					break;
			case 2: part2(v, ini, fin, piv);
					break;
			case 3: part3(v, ini, fin, piv);
					break;
		}
		quicksort(v, ini, piv-1, cont, tipo);
		quicksort(v, piv+1, fin, cont, tipo);
	}
}
int main(){
	// v1 ==> El pivote sera el valor del inicio
	// v2 ==> El pivote sera el valor del fin
	// v3 ==> EL pivote será la mediana entre ini fin y medio
	vector<int> v1, v2, v3;
	int dato;
	long long cont;
	while (cin >> dato){
		v1.push_back(dato);
		v2.push_back(dato);
		v3.push_back(dato);
	}
	cont = 0;
	// Tipo
	// 1 = pivote inicio
	// 2 = pivote fin
	// 3 = pivote mediana
	quicksort(v1, 0, v1.size()-1, cont, 1);
	//cout << v1.size() << endl;
	//for (int i=0; i<v1.size(); i++){
	//	cout << v1[i] << endl;
	//}
	cout << "Comparaciones 1: "<< cont << endl;
	cont = 0;
	quicksort(v2, 0, v2.size()-1, cont, 2);
	cout << "Comparaciones 2: "<< cont << endl;
	cont = 0;
	quicksort(v3, 0, v3.size()-1, cont, 3);
	cout << "Comparaciones 3: "<< cont << endl;
	return 0;
}