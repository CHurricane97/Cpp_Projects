#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <bits/stdc++.h>
#include "BB.h"

using namespace std;

BBmain::BBmain(string nazwap, int ms) {
    macierz = NULL;
    mstart = ms;
    finalres = INT_MAX;
    fst = 0;
    first = true;
    cout << "Tworze macierz z pliku" << endl;
    wczytajzpliku(nazwap);

    visited = new bool[lmiast];
    drogaost = new int[lmiast + 1];
}

BBmain::~BBmain() {
    purge();
}

bool BBmain::file_read_line(ifstream &file, int *tab, int size) {
    string s;
    getline(file, s);

    if (file.fail() || s.empty())
        return (false);

    //cout << s << endl;
    istringstream in_ss(s);

    for (int i = 0; i < size; i++) {
        in_ss >> tab[i];
        if (in_ss.fail())
            return (false);
    }
    return (true);
}

void BBmain::wczytajzpliku(string n) {
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

void BBmain::branchandbound() {

    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();

    int droga[lmiast + 1];

    droga[0] = mstart;
    droga[lmiast] = mstart;

    int curr_bound = 0;

    for (int i = 0; i < lmiast + 1; ++i) {
        droga[i] = -1;

    }
    for (int i = 0; i < lmiast; ++i) {
        visited[i] = false;

    }


    for (int i = 0; i < lmiast; i++) {
        curr_bound += ((pmin(i) + smin(i)) / 2);
    }


    cout << curr_bound << endl;


    visited[0] = true;
    droga[0] = 0;


    frec(curr_bound, 0, 1, droga);

    elapsed = read_QPC() - start;

    cout << endl;
    float prd = 100.0 * (((float) fst - (float) hamilton) / (float) hamilton);
    cout << fst << "    " << prd << "%" << endl;
    for (int i = 0; i < lmiast + 1; ++i) {
        if (i == 0) {
            cout << "Start: " << drogaost[i] << " -> ";
        } else if (i < lmiast) {
            cout << drogaost[i] << " -> ";
        } else {
            cout << drogaost[i];
        }

    }
    cout << endl;
    cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed /
                                                          frequency << endl;
    cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
                                                 frequency << endl;
    cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
                                                 frequency << endl << endl;


}


void BBmain::frec(int cbound, int cweight, int level, int *cpath) {

    if (level == lmiast) {

        if (macierz[cpath[level - 1]][cpath[0]] != 0) {

            int curr_res = cweight +
                           macierz[cpath[level - 1]][cpath[0]];


            if (curr_res < finalres) {
                for (int i = 0; i < lmiast; i++) {
                    drogaost[i] = cpath[i];
                    drogaost[lmiast] = cpath[0];
                    finalres = curr_res;


                }
                float prd = 100.0 * (((float) curr_res - (float) hamilton) / (float) hamilton);
                cout << curr_res << "    " << prd << "%" << endl;
                if (first) {
                    first = false;
                    fst = curr_res;
                }

            }
        }
        return;
    }


    for (int i = 0; i < lmiast; i++) {

        if (macierz[cpath[level - 1]][i] != 0 &&
            visited[i] == false) {
            int temp = cbound;
            cweight += macierz[cpath[level - 1]][i];


            if (level == 1) {

                cbound -= ((pmin(cpath[level - 1]) +
                            pmin(i)) / 2);
            } else {
                cbound -= ((smin(cpath[level - 1]) +
                            pmin(i)) / 2);

            }


            if (cbound + cweight < finalres) {
                cpath[level] = i;
                visited[i] = true;


                frec(cbound, cweight, level + 1,
                     cpath);
            }


            cweight -= macierz[cpath[level - 1]][i];
            cbound = temp;


            memset(visited, false, sizeof(visited) * lmiast);
            for (int j = 0; j <= level - 1; j++) {
                visited[cpath[j]] = true;
            }

        }
    }

}

int BBmain::pmin(int i) {
    int min = INT_MAX;
    for (int k = 0; k < lmiast; k++)
        if (macierz[i][k] < min && i != k)
            min = macierz[i][k];
    return min;
}

int BBmain::smin(int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < lmiast; j++) {
        if (i == j)
            continue;

        if (macierz[i][j] <= first) {
            second = first;
            first = macierz[i][j];
        } else if (macierz[i][j] <= second &&
                   macierz[i][j] != first)
            second = macierz[i][j];
    }
    return second;
}


void BBmain::purge() {
    if (macierz == NULL) {
        cout << "macierz pusta" << endl;
        return;
    }

    cout << "Czyszcze macierz" << endl;

    for (int i = 0; i < lmiast; i++) {
        delete[] macierz[i];
    }
    delete[] macierz;
    delete[] visited;
    delete[] drogaost;
}

long long int BBmain::read_QPC() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int) count.QuadPart);
}








