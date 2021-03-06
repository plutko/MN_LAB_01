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
double alpha[NMAX][NMAX];
double beta[NMAX];
double XK[NMAX];
double XK1[NMAX];

void wczytajDane()
{
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
		for (int i = 1; i <= n; i++)
		{
			getline(plikWejsciowy, linia);
			short k = 0;
			for (int j = 1; j <= n; j++)
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

bool przeksztalcMacierz()
{
	//sprawdzenie czy nie wystepuje dzielenie przez zero
	for (int i = 1; i <= n; i++)
	{
		if (A[i][i] == 0)
		{
			return true;
		}
	}
	//przeksztalczenie macierzy
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i == j)
			{
				alpha[i][j] = 0;
			}
			else
			{
				alpha[i][j] = -(A[i][j] / A[i][i]);
			}
		}
		beta[i] = B[i] / A[i][i];
	}
	return false;
}

void iteracja()
{
	double norma = 0.0;
	int lit = 0;
	for (int i = 0; i <= n; i++)
	{
		XK1[i] = beta[i];
	}
	do
	{
		for (int i = 0; i <= n; i++)
		{
			XK[i] = XK1[i];
		}
		lit++;
		XK1[1] = beta[1];
		for (int j = 2; j <= n; j++)
		{
			XK1[1] += (alpha[1][j] * XK[j]);
		}

		for (int i = 2; i <= n; i++)
		{
			XK1[i] = beta[i];
			for (int j = 1; j <= (i - 1); j++)
			{
				XK1[i] += (alpha[i][j] * XK1[j]);
			}
			for (int j = i + 1; j <= n; j++)
			{
				XK1[i] += (alpha[i][j] * XK[j]);
			}
		}
		//for (int i = 0; i <= n; i++)
		//{
		//	cout << "XK1" << i << "  : " << XK1[i] << endl;
		//}
		//cout << endl;
		norma = 0.0;
		for (int i = 1; i <= n; ++i)
		{

			if (norma < (abs(XK1[i] - XK[i])))
				norma = abs(XK1[i] - XK[i]);
		}
		/*cout << "Norma: " << norma << endl;*/
	} while (!((norma <= eps) || (lit >= MLI)));


}

void ZapiszRaport()
{
	ofstream raport;
	raport.open("raport.txt");

	raport << "epsilon : " << eps << endl;
	raport << "Maksymalna liczba iteracji : " << MLI << endl << endl;
	raport << "Macierz A:";

	for (int i = 1; i <= n; ++i)
	{
		raport << endl;
		for (int j = 1; j <= n; ++j)
		{
			raport << A[i][j] << " ";
		}
	}

	raport << endl << endl << "wektor B:" << endl;

	for (int i = 1; i <= n; ++i)
	{
		raport << B[i] << endl;
	}

	raport << endl << "Macierz alfa:";

	for (int i = 1; i <= n; ++i)
	{
		raport << endl;
		for (int j = 1; j <= n; ++j)
		{
			raport << alpha[i][j] << '\t' << '\t';
		}
	}

	raport << endl << endl << "wektor beta:" << endl;

	for (int i = 1; i <= n; ++i)
	{
		raport << beta[i] << endl;
	}

	raport << endl << "przedostatni wektor : ";

	for (int i = 1; i <= n; ++i)
	{
		/*cout << XK[i];*/
		raport.precision(10);
		raport << scientific << '\t' << XK[i] << '\t';
	}

	raport << endl << "ostatni wektor : ";

	for (int i = 1; i <= n; ++i)
	{
		raport.precision(10);
		raport << scientific << '\t' << XK1[i] << '\t';
	}

	raport.close();
}

int main()
{
	wczytajDane();
	bool czyDzielimyPrzezZero = przeksztalcMacierz();
	if (czyDzielimyPrzezZero)
	{
		cout << "Macierz jest zle uwarunkowana, wystepuje dzielenie przez zero." << endl;
		return 0;  // ja tu wychodze z programu, ale trzeba bedzie i tak wypisac cos...?
	}
	iteracja();
	ZapiszRaport();
	string a;
	cin >> a;
	return 0;
}
