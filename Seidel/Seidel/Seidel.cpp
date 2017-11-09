// Seidel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

double eps = 0.0001;
short MLI = 30;
short n = 5;
const short NMAX = 6;
double A[NMAX][NMAX];
double B[NMAX];

void wczytajDane()
{
	string line;
	cout << "Podaj rozmiar macierzy n: ";
	cin >> n;
	cout << "Podaj maksymalna liczbe iteracji MLI: ";
	cin >> MLI;
	cout << "Podaj epsilon eps: ";
	cin >> eps;


	string linia = "";
	ifstream plikWejsciowy;
	plikWejsciowy.open("Zestaw.txt");
	if (plikWejsciowy.good())
	{
		for (short i = 1; i <= n; i++)
		{
			getline(plikWejsciowy, linia);
			short k = 0;
			for (short j = 1; j <= n; j++)
			{
				string temp = "";
				while (linia[k] != '\t')
				{
					temp += linia[k];
					k++;
				}
				k++;
				A[i][j] = atof(temp.c_str());
			}
			string temp = "";
			while (linia[k] != 0)
			{
				temp += linia[k];
				k++;
			}
			B[i] = atof(temp.c_str());
		}
		plikWejsciowy.close();
	}
	else
	{
		cout << "Nie otworzono pliku" << endl;
	}
}


int main()
{
	wczytajDane();
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
 			cout << A[i][j] << "    ";
		}
		cout << endl;
	}
	
	for (int i = 0; i <= n; i++)
	{
		cout << B[i] << "    ";
	}

	return 0;
}

