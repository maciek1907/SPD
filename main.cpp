#include <iostream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

/******************************************************************************************************/

struct zadanie {
	int nr;
	int r;
	int p; // moment dostepnosci
	int q; // czas wykonywania tab
	int sumRP;
	int sumPQ;
};

void wys(vector<zadanie> tab,int n)
{

	for (int i = 0; i < n; i++) {
        cout<<tab[i].nr<<" "<<tab[i].r<<" "<<tab[i].p<<" "<<tab[i].q<<" "<< i<<" "<<tab[i].sumPQ<<" "<<tab[i].sumRP<<endl;

	}
}

/******************************************************************************************************/

inline void swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
};

void wypiszElementy(int **tablica, int iloscZadan, int iloscMaszyn)
{
    cout << "******************" << endl << "Dla macierzy terminow zakonczenia: " << endl << endl;
    for (int i = 0; i < iloscZadan; i++)
    {
        for (int j = 0; j < iloscMaszyn; j++)
        {
            cout << tablica[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void permutacje(int **tablicaZadan, int i, int iloscZadan, int iloscMaszyn)
{
    if (i<iloscZadan-1)
    {
        for (int j = i; j < iloscZadan; j++)
        {
            swap(tablicaZadan[i], tablicaZadan[j]);
            permutacje(tablicaZadan, i+1, iloscZadan, iloscMaszyn);
            swap(tablicaZadan[i], tablicaZadan[j]);
        }
    }
    else
    {
    int **harmonogram = new int *[iloscZadan];
        for(int i = 0; i < iloscZadan; i++)
            harmonogram[i] = new int[iloscMaszyn];

    int suma = 0;

        for (int i = 0; i < iloscZadan; i++)
            for (int j = 0; j < iloscMaszyn; j++)
            {
                if (i == 0 && j == 0) {harmonogram[i][j] = tablicaZadan[i][j]; suma += harmonogram[i][j];}
                else if (i == 0 && j != 0) {harmonogram[i][j] = harmonogram[i][j-1] + tablicaZadan[i][j]; suma += harmonogram[i][j];}
                else if (i != 0 && j == 0) {harmonogram[i][j] = harmonogram[i-1][j] + tablicaZadan[i][j]; suma += harmonogram[i][j];}
                else {harmonogram[i][j] = max(harmonogram[i][j-1], harmonogram[i-1][j]) + tablicaZadan[i][j]; suma += harmonogram[i][j];}
            }
        wypiszElementy(harmonogram,iloscZadan,iloscMaszyn);
        cout << "Czas wykonania wynosi: " << harmonogram[iloscZadan-1][iloscMaszyn-1] << endl << endl;
    }
}

void generujLosowe()
{
    int iloscZadan = 0;
    int iloscMaszyn = 3;
    srand (time(NULL));
    fstream inputRandom;
    inputRandom.open("inputRandom.txt",ios::out);
    cout << "Ile zadan: ";
    cin >> iloscZadan;

    inputRandom << iloscZadan << " " << iloscMaszyn << endl;

    for (int i = 0; i < iloscZadan; i++)
    {
        for (int j = 0; j < iloscMaszyn; j++)
        {
            inputRandom << rand() % 50 + 1 << " ";
        }
        inputRandom << endl;
    }
}

int main()
{
    int **tablicaZadan, iloscZadan, iloscMaszyn;

    /* PRZEGLAD ZUPELNY */

    cout << "Przeglad zupelny dla ta000. Nacisnij dowolny przycisk aby kontynuowac." << endl;
    getchar();
    fstream input;
    input.open("inputData.txt");
    if(input)
    {
        input >> iloscZadan;
        input >> iloscMaszyn;

        tablicaZadan = new int *[iloscZadan];
        for(int i = 0; i < iloscZadan; i++)
            tablicaZadan[i] = new int[iloscMaszyn];

        for (int i = 0; i < iloscZadan; i++)
            for (int j = 0; j < iloscMaszyn; j++)
            input >> tablicaZadan[i][j];
    }
    input.close();
    cout << "Zadania: " << iloscZadan << ", Maszyny: " << iloscMaszyn << endl << endl;
    permutacje(tablicaZadan,0,iloscZadan,iloscMaszyn);

    /* DANE LOSOWE */

    cout << "Losowe dane. Wprowadz ponizsze wartosci." << endl;
    generujLosowe();
    input.open("inputRandom.txt");
    if(input)
    {
        input >> iloscZadan;
        input >> iloscMaszyn;

        tablicaZadan = new int *[iloscZadan];
        for(int i = 0; i < iloscZadan; i++)
            tablicaZadan[i] = new int[iloscMaszyn];

        for (int i = 0; i < iloscZadan; i++)
            for (int j = 0; j < iloscMaszyn; j++)
            input >> tablicaZadan[i][j];
    }
    input.close();

    getchar();
    delete tablicaZadan;

    /******************************************************************************************************/

    /* ALGORYTM JOHNSONA */

    cout << "Algorytm Johnsona - wariant na trzy maszyny. Nacisnij dowolny przycisk aby kontynuowac" << endl;
    getchar();

    int c = 0;
	char nazwapliku[100];
	fstream plik;
	int n = 10; // liczba zadan

	cout << "Podaj nazwe pliku" << endl;
	cin >> nazwapliku;
	plik.open(nazwapliku, ios::in);
	if (plik.good() != true)
		cout << "Blad wczytywania pliku" << endl;
	plik >> n;
	cout << "tutaj n:" << n << endl;
	vector<zadanie> tab;

	for (int i = 0; i < n; i++) {
    zadanie tmp;
		tmp.nr = i;
		plik >> tmp.r;
		plik >> tmp.p;
		plik >> tmp.q;
		tmp.sumRP = tmp.r + tmp.p;
		tmp.sumPQ = tmp.q + tmp.p;
		tab.push_back(tmp);
	}

	zadanie tmp;
	vector<zadanie> L1,L2;
	int i, j, k, l = n;
	bool PQ;
	cout<<endl;
	while (!tab.empty())
	{
	    tmp = tab[0];
	    k=0;
		for (i = 0; i < l - 1; i++)
		{
			if (tmp.sumPQ > tmp.sumRP)
			{
			    PQ=false;
				if (tmp.sumRP > tab[i + 1].sumPQ)
				{
					PQ = true;
					tmp = tab[i+1];
					k = i+1;
				}
				if (tmp.sumRP > tab[i + 1].sumRP)
				{
					PQ = false;
					tmp = tab[i+1];
					k = i+1;
				}
			}
			else
			{
			    PQ=true;
				if (tmp.sumPQ > tab[i + 1].sumPQ)
				{
					tmp = tab[i+1];
					k = i+1;
					PQ = true;
				}
				if (tmp.sumPQ > tab[i + 1].sumRP)
				{
					tmp = tab[i+1];
					k = i+1;
					PQ = false;
				}
			}
		}
		if (!PQ)
		{
		    //cout<<k<<" "<<tab[k].sumRP<<" "<<tab[k].nr<<endl;
			L1.push_back(tab[k]);
			tab[k]=tab.back();
			tab.pop_back();
		}
		else
		{
		    //cout<<k<<" "<<tab[k].sumPQ<<" "<<tab[k].nr<<endl;
			L2.push_back(tab[k]);
			tab[k]=tab.back();
			tab.pop_back();
		}
		l--;
	}
int tablica[n][3];
int o=0;
cout<<endl;
for(int p=0;p<L1.size();p++)
{
    //cout<< L1[p].r<<" "<<L1[p].p<<" "<<L1[p].q<<" "<< p<<" "<<o<<" "<<L1[p].sumRP<<endl;
    tablica[o][0]=L1[p].r;
    tablica[o][1]=L1[p].p;
    tablica[o++][2]=L1[p].q;
}
cout<<endl;
for(int p=L2.size()-1;p>=0;p--)
{
 //   cout<< L2[p].r<<" "<<L2[p].p<<" "<<L2[p].q<<" "<<p<<" "<<o<<" "<<L2[p].sumPQ<<endl;
    tablica[o][0]=L1[p].r;
    tablica[o][1]=L1[p].p;
    tablica[o++][2]=L1[p].q;
}
	/*wyliczanie c*/
	int C=0;
        int M = 0;
	        for (int i = 0; i < n; i++)
            {
                M=max(M,tablica[i][0])+tablica[i][1];
                C=max(C,M+tablica[i][2]);
            }
        cout << "Czas wykonania wynosi: " << C << endl << endl;
};
