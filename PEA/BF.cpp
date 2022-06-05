#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <bits/stdc++.h>
#include "BF.h"

using namespace std;


BFmain::BFmain(string nazwap, int ms) {
    macierz = NULL;
    mstart = ms;
    cout << "Tworze macierz z pliku" << endl;
    wczytajzpliku(nazwap);

}

BFmain::~BFmain() {
    purge();
}

bool BFmain::file_read_line(ifstream &file, int *tab, int size) {
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

void BFmain::wczytajzpliku(string n) {
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

void BFmain::bruteforce() {

    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    start = read_QPC();

    boolean first=true;
    int fst=0;
    int droga[lmiast + 1];
    int drogaost[lmiast + 1];
    droga[0] = mstart;
    droga[lmiast] = mstart;
    drogaost[0] = mstart;
    drogaost[lmiast] = mstart;
    vector<int> vertex;
    for (int i = 0; i < lmiast; i++) {
        if (i != mstart) {
            vertex.push_back(i);
        }

    }
    int min_path = INT_MAX;
    do {


        int current_pathweight = 0;


        int k = mstart;
        for (int i = 0; i < vertex.size(); i++) {

            current_pathweight += macierz[k][vertex[i]];
            droga[i + 1] = vertex[i];
            k = vertex[i];
        }
        current_pathweight += macierz[k][mstart];



        if (min_path > current_pathweight) {
            for (int i = 0; i < lmiast+1; ++i) {
                drogaost[i]=droga[i];
            }
            float prd=100.0 * (((float )current_pathweight - (float )hamilton) / (float )hamilton);
            cout <<current_pathweight<<"    " << prd << "%" << endl;
            min_path = current_pathweight;
            if(first){
                first=false;
                fst=current_pathweight;
            }
        }


    }
    while (
            next_permutation(vertex.begin(), vertex.end()));
    elapsed = read_QPC() - start;
    cout << endl;
    float prd=100.0 * (((float )fst - (float )hamilton) / (float )hamilton);
    cout <<fst<<"    " << prd << "%" << endl;
    for (int i = 0; i < lmiast + 1; ++i) {
        if (i == 0) {
            cout << "Start: " << drogaost[i] << " -> ";
        } else if (i<lmiast){
            cout << drogaost[i] << " -> ";
        } else{
            cout << drogaost[i];
        }

    }
    cout << endl;
    cout << "Time [s]  = " << fixed << setprecision(3) << (float)elapsed /
                                                          frequency << endl;
    cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
                                                 frequency << endl;
    cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
                                                 frequency << endl << endl;

}


void BFmain::purge() {
    if (macierz == NULL) {
        cout << "macierz pusta" << endl;
        return;
    }

    cout << "Czyszcze macierz" << endl;

    for (int i = 0; i < lmiast; i++) {
        delete[] macierz[i];
    }
    delete[] macierz;
}

long long int BFmain::read_QPC() {

        LARGE_INTEGER count;
        QueryPerformanceCounter(&count);
        return((long long int)count.QuadPart);

}


