#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "TS.h"

using namespace std;


TSmain::TSmain(string nazwap, int ms) {
    nrozw = 999999;
    macierz = NULL;
    rozwnaj = NULL;
    rozwst = NULL;
    mstart = ms;
    cout << "Tworze macierz z pliku" << endl;
    wczytajzpliku(nazwap);

}

TSmain::~TSmain() {
    purge();
}

bool TSmain::file_read_line(ifstream &file, int *tab, int size) {
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

void TSmain::wczytajzpliku(string n) {
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


void TSmain::tabusearch() {


    int **tabicarozwtabu;//tablica zakazów
    int limittabu;//ilość iteracji zakaz pozostaje w tabeli zakazów
    int *nastrozwstartowe;
    srand(time(NULL));

    nastrozwstartowe = new int[lmiast + 1];
    int fst = nrozw;//rozwiązanie startowe
    if (lmiast < 10) {
        limittabu = lmiast;
    } else {
        limittabu = 100;
    }
    tabicarozwtabu = new int *[lmiast];
    for (int i = 0; i < lmiast; ++i) {
        tabicarozwtabu[i] = new int[lmiast];
    }
    for (int j = 0; j < lmiast; ++j) {
        for (int i = 0; i < lmiast; ++i) {// zapełnienie tablicy tabu rozwiązaniami startowymi
            tabicarozwtabu[j][i] = 0;
        }
    }


    boolean koniec = true;
    int temproz, aktrozw, indekszmiany1, indekszmiany2, licznikpoprawy = 0, licznikiter = 0;
    aktrozw = nrozw;

    float prd = 100.0 * (((float) fst - (float) hamilton) / (float) hamilton);
    cout << 0 << "    " << fst << "    "<<setprecision(5) << prd << "%" << endl;


    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();

    while (koniec) {//pętla główna
        licznikiter++;
        temproz = 999999;// minimum sąsiedztwa dla danej iteracji

        for (int i = 1; i < lmiast; ++i) {
            for (int j = 1; j < lmiast; ++j) {
                int pier, drug, poprzedrozw = 0;
                if (i != j) {

                    pier = rozwst[i];
                    drug = rozwst[j];
                    poprzedrozw = aktrozw;
                    rozwst[i] = drug;
                    rozwst[j] = pier;

                    aktrozw = obliczdroge();
                    if (aktrozw < temproz) {//najlepsze lokalnie

                        if (tabicarozwtabu[pier][drug] == 0 ||
                            aktrozw < nrozw) {//jeśli ruch nie w tabu lub rozwiązanie lepsze niż najlepsze dotychczasowe
                            temproz = aktrozw;
                            indekszmiany1 = pier;
                            indekszmiany2 = drug;
                            for (int n = 0; n < lmiast + 1; ++n) {
                                nastrozwstartowe[n] = rozwst[n];
                            }


                        }


                    }

                    aktrozw = poprzedrozw;
                    rozwst[i] = pier;
                    rozwst[j] = drug;
                }


            }
        }
        //następne najlepsze dopuszcalne rozwiązanie
        aktrozw = temproz;
        for (int i = 0; i < lmiast + 1; ++i) {
            rozwst[i] = nastrozwstartowe[i];
        }
        for (int j = 0; j < lmiast; ++j) {
            for (int i = 0; i < lmiast; ++i) {// zmniejszenie zakazów o jedną turę
                if (tabicarozwtabu[j][i] > 0) {
                    tabicarozwtabu[j][i] = tabicarozwtabu[j][i] - 1;
                }

            }
        }

        tabicarozwtabu[indekszmiany1][indekszmiany2] = limittabu;
        tabicarozwtabu[indekszmiany2][indekszmiany1] = limittabu;


        licznikpoprawy++;
        if (temproz < nrozw) {
            licznikpoprawy = 0;
            nrozw = temproz;
            for (int n = 0; n < lmiast + 1; ++n) {
                rozwnaj[n] = rozwst[n];
            }
            prd = 100.0 * (((float) nrozw - (float) hamilton) / (float) hamilton);
            cout << licznikiter << "    " << nrozw << "    " <<setprecision(5)<< prd << "%" << endl;

        }
        if (licznikpoprawy == 8000) {//jeśli stagnacja to przemieszanie
            int jeden, dwa, zamiennik1, zamiennik2;
            for (int i = 0; i < lmiast; ++i) {
                jeden = 1;
                dwa = 1;
                while (jeden == dwa) {
                    jeden = 1 + (rand() % (lmiast - 1));
                    dwa = 1 + (rand() % (lmiast - 1));
                }
                zamiennik1 = rozwst[jeden];
                zamiennik2 = rozwst[dwa];

                rozwst[jeden] = zamiennik2;
                rozwst[dwa] = zamiennik1;

            }
            aktrozw = obliczdroge();


        }

        if (licznikpoprawy > 10000 || licznikiter > 1000000) {
            koniec = false;
        }

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
    cout << endl;
    cout << endl;
    cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed /
                                                          frequency << endl;
    cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
                                                 frequency << endl;
    cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
                                                 frequency << endl << endl;
    for (int i = 0; i < lmiast; i++) {
        delete[] tabicarozwtabu[i];
    }
    delete[] tabicarozwtabu;
    delete[] nastrozwstartowe;
}

void TSmain::poczrozw() {


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


void TSmain::purge() {
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

long long int TSmain::read_QPC() {

    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int) count.QuadPart);

}

int TSmain::obliczdroge() {

    int droga = 0;
    for (int i = 0; i < lmiast; ++i) {
        droga = droga + macierz[rozwst[i]][rozwst[i + 1]];

    }
    return droga;
}


