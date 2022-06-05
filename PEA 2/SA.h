#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

#ifndef PEA_BF_H
#define PEA_BF_H

#endif //PEA_BF_H


class SAmain {
private:
    int lmiast;
    int mstart;
    int nrozw;
    int **macierz;
    int *rozwst;
    int *rozwnaj;

    int hamilton;
public:

    SAmain(string nazwap, int ms);

    ~SAmain();


    bool file_read_line(ifstream &file, int tab[], int size);

    void wczytajzpliku(string n);

    int obliczdroge();

    void simulatedannealing();

    double randomnumber();

    double getProbability(int difference, double temperature);

    void poczrozw();

    void purge();

    long long int read_QPC();

};