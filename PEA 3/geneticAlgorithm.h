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


struct populationMember{
    int wartosc;
    int *proponowanaDroga;
};

class Gmain {
private:

    int lmiast;
    int mstart;
    int nrozw;
    int population;
    int **macierz;
    int *rozwst;
    int *rozwnaj;
    int *nextparents;
    int selekcja;
    float mutProbab;
    populationMember *aktualnaPopulacja;
    populationMember *nastepnaPopulacja;

    int hamilton;
public:

    Gmain(string nazwap, int ms, int pop,int selectionmethod, float mutation);

    ~Gmain();


    bool file_read_line(ifstream &file, int tab[], int size);

    void wczytajzpliku(string n);

    void geneticAlgorithm();

    void mutate(int i);

    void mutatechildren();

    void sortpopulation();

    int obliczdroge(int indeks);

    void tournament(int rozmiar);

    void localimprovement();

    void ordercross();

    void roulette();

    void poczrozw();

    void purge();

    long long int read_QPC();

    boolean checksolutions(int li);

    double randomnumber();
};