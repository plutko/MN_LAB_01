// Seidel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

float eps = 0.0001;
short MLI = 30;
short n = 5;
const short NMAX = 7;
double macierzA[NMAX][NMAX];

void wczytajDane()
{
	string line;
	cout << "Podaj rozmiar macierzy n: ";
	cin >> n;
	cout << "Podaj maksymalna liczbe iteracji MLI: ";
	cin >> MLI;
	cout << "Podaj epsilon eps: ";
	cin >> eps;

	ifstream plikWejsciowy;
	plikWejsciowy.open("Zestaw1.txt");
	while (getline(plikWejsciowy, line))
	{

	}

}


int main()
{


	wczytajDane();

	return 0;
}

