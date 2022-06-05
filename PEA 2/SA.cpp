#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <climits>
#include "SA.h"

using namespace std;


SAmain::SAmain(string nazwap, int ms) {
    nrozw = 999999;
    macierz = NULL;
    rozwnaj = NULL;
    rozwst = NULL;
    mstart = ms;
    cout << "Tworze macierz z pliku" << endl;
    wczytajzpliku(nazwap);

}

SAmain::~SAmain() {
    purge();
}

bool SAmain::file_read_line(ifstream &file, int *tab, int size) {
    string s;
    getline(file, s);

    if (file.fail() || s.empty())
        return (false);

    // cout << s << endl;
    istringstream in_ss(s);

    for (int i = 0; i < size; i++) {
        in_ss >> tab[i];
        if (in_ss.fail())
            return (false);
    }
    return (true);
}

void SAmain::wczytajzpliku(string n) {
    if (macierz != NULL) {//czyszczenie
        purge();
    }


    ifstream file;
    int tab[1];
    file.open(n.c_str());

    if (file.is_open()) {

        if (file_read_line(file, tab, 0)) {
            if (file_read_line(file, tab, 1)) {
                lmiast = tab[0];

                if (lmiast < 2) {
                    cout << "Błąd miast" << endl;
                    exit(20);
                }
                int tab2[lmiast];

                macierz = new int *[lmiast];

                for (int i = 0; i < lmiast; ++i) {//wiersze w macierzy
                    macierz[i] = new int[lmiast];
                }


                for (int i = 0; i < lmiast; i++) {
                    if (file_read_line(file, tab2, lmiast)) {

                        for (int j = 0; j < lmiast; ++j) {
                            if (tab2[j] < 0) {
                                macierz[i][j] = 0;
                            } else {
                                macierz[i][j] = tab2[j];
                            }
                        }


                    } else {
                        cout << "File error - READ EDGE" << endl;
                        exit(20);
                    }
                }
                if (file_read_line(file, tab, 1)) {
                    hamilton = tab[0];
                } else {
                    cout << "File error - READ Hamilton" << endl;
                    exit(20);
                }

            } else {
                cout << "File error - READ INFO" << endl;
                exit(20);
            }


        } else {
            cout << "File error - READ INFO" << endl;
            exit(20);
        }


        file.close();
    } else {
        cout << "File error - OPEN" << endl;
        exit(20);
    }


}


double SAmain::randomnumber() {
    double los;

    los = (double) rand() / RAND_MAX;
//    cout<<"los: "<<los<<endl;
    return los;
}

double SAmain::getProbability(int difference, double temperature) {
    return exp(-1 * difference / temperature);
}

void SAmain::simulatedannealing() {



    int fst = nrozw;//rozwiązanie startowe
    int pier, drug, aktrozw = 0, najlepszeakualne;
    najlepszeakualne = nrozw;
    srand(time(NULL));
    double temperatura, chlodzenie = 0.9999999, mintemperatura = 0.00001, prawdopod;
    int indeks1 = 0, indeks2 = 0;
    int  roznica, licznikiter;

    float prd = 100.0 * (((float) fst - (float) hamilton) / (float) hamilton);
    cout << 0 << "    " << fst << "    "<<setprecision(5) << prd << "%" << endl;


    licznikiter = 1;

    temperatura = INT_MAX;

    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();


    while (temperatura > mintemperatura) {
        indeks1 = 1;
        indeks2 = 1;
        while (indeks1 == indeks2) {
            indeks1 = 1 + (rand() % (lmiast - 1));
            indeks2 = 1 + (rand() % (lmiast - 1));
        }

        pier = rozwst[indeks1];
        drug = rozwst[indeks2];
        rozwst[indeks1] = drug;
        rozwst[indeks2] = pier;
        aktrozw = obliczdroge();
        roznica = aktrozw - najlepszeakualne;


        if (roznica < 0 || (roznica > 0 && getProbability(roznica, temperatura) > randomnumber())) {

            najlepszeakualne = roznica + najlepszeakualne;
            if (najlepszeakualne < nrozw) {
                nrozw = najlepszeakualne;
                prd = 100.0 * (((float) nrozw - (float) hamilton) / (float) hamilton);
                cout << licznikiter << "    " << nrozw << "    "<<setprecision(5) << prd << "%" << endl;
                for (int n = 0; n < lmiast + 1; ++n) {
                    rozwnaj[n] = rozwst[n];
                }

            }

        } else {
            rozwst[indeks1] = pier;
            rozwst[indeks2] = drug;
        }

        temperatura = temperatura * chlodzenie;

        licznikiter++;
    }
    elapsed = read_QPC() - start;
    prd = 100.0 * (((float) fst - (float) hamilton) / (float) hamilton);
    cout << 0 << "    " << fst << "    "<<setprecision(5) << prd << "%" << endl;

    for (int i = 0; i < lmiast + 1; ++i) {
        if (i == 0) {
            cout << "Start: " << rozwnaj[i] << " -> ";
        } else if (i < lmiast) {
            cout << rozwnaj[i] << " -> ";
        } else {
            cout << rozwnaj[i];
        }

    }
    cout<<endl;

    cout << endl;
    cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed /
                                                          frequency << endl;
    cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
                                                 frequency << endl;
    cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
                                                 frequency << endl << endl;


}



void SAmain::poczrozw() {


    int droga = 0;

    rozwnaj = new int[lmiast + 1];
    rozwst = new int[lmiast + 1];
    rozwst[0] = mstart;
    rozwst[lmiast] = mstart;
    int visited[lmiast];
    for (int i = 0; i < lmiast; ++i) {
        visited[i] = 0;
    }
    visited[mstart] = 1;

    int pmiast = mstart;

    for (int i = 0; i < lmiast - 1; i++) {
        int max = 9999999;

        for (int j = 0; j < lmiast; ++j) {

            if (j != pmiast) {
                if (macierz[pmiast][j] < max && visited[j] == 0) {
                    max = macierz[pmiast][j];
                    rozwst[i + 1] = j;

                }

            }

        }

        pmiast = rozwst[i + 1];
        visited[pmiast] = 1;


    }


    for (int i = 0; i < lmiast + 1; ++i) {
        rozwnaj[i] = rozwst[i];
//        cout << rozwnaj[i] << endl;
    }

    for (int i = 0; i < lmiast; ++i) {
        droga = droga + macierz[rozwnaj[i]][rozwnaj[i + 1]];

    }
    nrozw = droga;


}


void SAmain::purge() {
    if (macierz == NULL) {
        cout << "macierz pusta" << endl;
        return;
    }

    cout << "Czyszcze macierz" << endl;

    for (int i = 0; i < lmiast; i++) {
        delete[] macierz[i];
    }
    delete[] macierz;
    delete[] rozwst;
    delete[] rozwnaj;
}

long long int SAmain::read_QPC() {

    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int) count.QuadPart);

}

int SAmain::obliczdroge() {

    int droga = 0;
    for (int i = 0; i < lmiast; ++i) {
        droga = droga + macierz[rozwst[i]][rozwst[i + 1]];

    }
    return droga;
}







