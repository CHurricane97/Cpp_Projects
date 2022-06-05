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

#include "geneticAlgorithm.h"

using namespace std;


Gmain::Gmain(string nazwap, int ms, int pop, int selectionmethod, float mutation) {
    nrozw = 999999;
    macierz = NULL;
    rozwnaj = NULL;
    rozwst = NULL;
    selekcja = selectionmethod;
    mutProbab = mutation;
    mstart = ms;
    population = pop;
    cout << "Tworze macierz z pliku" << endl;
    wczytajzpliku(nazwap);

}

Gmain::~Gmain() {
    purge();
}

bool Gmain::file_read_line(ifstream &file, int *tab, int size) {
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

void Gmain::wczytajzpliku(string n) {
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

void Gmain::geneticAlgorithm() {
    srand(time(NULL));

    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();

    //rozwiązanie startowe do generowania populacji
    poczrozw();
    int fst = nrozw;
    float prd = 100.0 * (((float) fst - (float) hamilton) / (float) hamilton);
    cout << 0 << "    " << fst << "    " << setprecision(5) << prd << "%" << endl;



    //ustawianie populacji początkowej
    aktualnaPopulacja = new populationMember[population];
    for (int i = 0; i < population; ++i) {
        aktualnaPopulacja[i].proponowanaDroga = new int[lmiast + 1];
        for (int j = 0; j < lmiast + 1; ++j) {
            aktualnaPopulacja[i].proponowanaDroga[j] = rozwst[j];
            aktualnaPopulacja[i].wartosc = nrozw;
        }

    }

    //dywersyfikacja populacji początkowej
    for (int i = 1; i < population; ++i) {

        int ile = 0 + rand() % 10;
        for (int j = 0; j < ile; ++j) {
            mutate(i);
        }


    }
    sortpopulation();

    int licznikpoprawy = 0;
    int iteracja = 1;

    while (licznikpoprawy < 1000) {
        if (selekcja == 1) {
            roulette();
        } else {
            tournament(5);
        }

        ordercross();
        mutatechildren();
        for (int i = 0; i < population; ++i) {
            obliczdroge(i);
        }
        localimprovement();
        sortpopulation();
        boolean res=checksolutions(iteracja);
        if (res){
            licznikpoprawy=0;
        } else{
            licznikpoprawy++;
        }
        iteracja++;

    }
    elapsed = read_QPC() - start;
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




}


void Gmain::poczrozw() {


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
        int max = INT_MAX;

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


void Gmain::purge() {
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
    delete[] aktualnaPopulacja;
}

long long int Gmain::read_QPC() {

    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int) count.QuadPart);

}

int Gmain::obliczdroge(int indeks) {

    int droga = 0;
    for (int i = 0; i < lmiast; ++i) {
        droga = droga +
                macierz[aktualnaPopulacja[indeks].proponowanaDroga[i]][aktualnaPopulacja[indeks].proponowanaDroga[i +
                                                                                                                  1]];
    }
    aktualnaPopulacja[indeks].wartosc = droga;
    return droga;
}

void Gmain::mutate(int i) {

    int indeks1 = 1;
    int indeks2 = 1;

    while (indeks1 == indeks2) {
        indeks1 = 1 + (rand() % (lmiast - 1));
        indeks2 = 1 + (rand() % (lmiast - 1));
    }

    int nowadroga = aktualnaPopulacja[i].wartosc
                    - macierz[aktualnaPopulacja[i].proponowanaDroga[indeks1 -
                                                                    1]][aktualnaPopulacja[i].proponowanaDroga[indeks1]]
                    -
                    macierz[aktualnaPopulacja[i].proponowanaDroga[indeks1]][aktualnaPopulacja[i].proponowanaDroga[
                            indeks1 + 1]]
                    - macierz[aktualnaPopulacja[i].proponowanaDroga[indeks2 -
                                                                    1]][aktualnaPopulacja[i].proponowanaDroga[indeks2]]
                    -
                    macierz[aktualnaPopulacja[i].proponowanaDroga[indeks2]][aktualnaPopulacja[i].proponowanaDroga[
                            indeks2 + 1]];
    aktualnaPopulacja[i].wartosc = nowadroga;

    int pier = aktualnaPopulacja[i].proponowanaDroga[indeks1];
    int drug = aktualnaPopulacja[i].proponowanaDroga[indeks2];
    aktualnaPopulacja[i].proponowanaDroga[indeks1] = drug;
    aktualnaPopulacja[i].proponowanaDroga[indeks2] = pier;

    nowadroga = aktualnaPopulacja[i].wartosc
                + macierz[aktualnaPopulacja[i].proponowanaDroga[indeks1 -
                                                                1]][aktualnaPopulacja[i].proponowanaDroga[indeks1]]
                +
                macierz[aktualnaPopulacja[i].proponowanaDroga[indeks1]][aktualnaPopulacja[i].proponowanaDroga[
                        indeks1 + 1]]
                + macierz[aktualnaPopulacja[i].proponowanaDroga[indeks2 -
                                                                1]][aktualnaPopulacja[i].proponowanaDroga[indeks2]]
                +
                macierz[aktualnaPopulacja[i].proponowanaDroga[indeks2]][aktualnaPopulacja[i].proponowanaDroga[
                        indeks2 + 1]];
    aktualnaPopulacja[i].wartosc = nowadroga;

}

void Gmain::sortpopulation() {

    int i, j;
    bool swapped = false;
    for (i = 0; i < population - 1; i++) {
        swapped = false;
        for (j = 0; j < population - i - 1; j++) {

            if (aktualnaPopulacja[j].wartosc > aktualnaPopulacja[j + 1].wartosc) {
                swapped = true;
                populationMember temp = aktualnaPopulacja[j];
                aktualnaPopulacja[j] = aktualnaPopulacja[j + 1];
                aktualnaPopulacja[j + 1] = temp;
            }


        }
        if (swapped == false) {
            break;
        }


    }


}

void Gmain::tournament(int rozmiar) {//turniej
    nextparents = new int[population];
    int reszta = (10 * population / 100) + 1;
//    cout << "reszta " << reszta << endl;
    for (int i = 0; i < reszta; ++i) {
        nextparents[i] = i;
    }

    for (int k = reszta; k < population; ++k) {

        int indeks, indekszwyciezcy;
        int best = INT_MAX;

        for (int i = 0; i < rozmiar; ++i) {
            indeks = 0 + (rand() % (population));
            if (aktualnaPopulacja[indeks].wartosc < best) {
                best = aktualnaPopulacja[indeks].wartosc;
                indekszwyciezcy = indeks;
            }
        }
        nextparents[k] = indekszwyciezcy;


    }


}

void Gmain::roulette() {//ruletka
    int *fitness = new int[population];
    double *choosechance = new double[population];
    nextparents = new int[population];
    int max = 0, maxfit = 0;
    for (int i = 0; i < population; ++i) {
        if (aktualnaPopulacja[i].wartosc > max) {
            max = aktualnaPopulacja[i].wartosc;
        }
    }
    for (int i = 0; i < population; ++i) {
        fitness[i] = max - aktualnaPopulacja[i].wartosc;
        if (fitness[i] == 0) {
            fitness[i] += 1;
        }
        maxfit = maxfit + fitness[i];
    }
    for (int i = 0; i < population; ++i) {
        choosechance[i] = (double) fitness[i] / (double) maxfit;
//        cout << setprecision(10) << choosechance[i] << endl;
    }
    int reszta = (10 * population / 100) + 1;
//    cout << "reszta " << reszta << endl;
    for (int i = 0; i < reszta; ++i) {
        nextparents[i] = i;
    }
    for (int i = reszta; i < population; ++i) {
        double los = randomnumber();
        if (los==1){
            los=los-(double )0.00000001;
        }
        double gdziejestesmy = 0;
        int indekswyboru = 0;
        while (true) {
            gdziejestesmy = gdziejestesmy + choosechance[indekswyboru];
            if (gdziejestesmy > los) {
                nextparents[i] = indekswyboru;
                break;
            }
            indekswyboru++;

        }
    }


    delete[] fitness;
}

double Gmain::randomnumber() {
    double los;

    los = (double) rand() / RAND_MAX;
//    cout << "los: " << los << endl;
    if (los==1){return los-0,00000001;} else{
        return los;
    }

}

void Gmain::ordercross() {
    nastepnaPopulacja = new populationMember[population];
    for (int i = 0; i < population; ++i) {
        nastepnaPopulacja[i].proponowanaDroga = new int[lmiast + 1];
        for (int j = 0; j < lmiast + 1; ++j) {
            nastepnaPopulacja[i].proponowanaDroga[j] = 0;
        }

    }

    int reszta = (10 * population / 100) + 1;
//    cout << "reszta " << reszta << endl;
    for (int i = 0; i < reszta; ++i) {
        for (int j = 0; j < lmiast + 1; ++j) {
            nastepnaPopulacja[i].proponowanaDroga[j] = aktualnaPopulacja[i].proponowanaDroga[j];
        }
    }


    for (int i = reszta; i < population; ++i) {
        int p1, p2;
        p1 = nextparents[i - reszta];
        if (i == population - 1) {
            p2 = nextparents[0];
        } else {
            p2 = nextparents[i - reszta + 1];
        }

        int j = i + 2;
        while (p1 == p2) {
            if (j >= population - 1) {
                j = 0;
            }
            p2 = nextparents[j];
            j++;
        }
        int indeks1 = 1;
        int indeks2 = 1;

        while (indeks1 == indeks2) {
            indeks1 = 1 + (rand() % (lmiast - 1));
            indeks2 = 1 + (rand() % (lmiast - 1));
        }
        if (indeks1 > indeks2) {
            int tmp1 = indeks1;
            indeks1 = indeks2;
            indeks2 = tmp1;
        }
        int licznikmiast = 2;
        for (int k = indeks1; k < indeks2; ++k) {
            nastepnaPopulacja[i].proponowanaDroga[k] = aktualnaPopulacja[p1].proponowanaDroga[k];
            licznikmiast++;
        }
        int iteratordziecka = indeks2;
        int iteratorrodzica = iteratordziecka;

        while (licznikmiast < lmiast + 1) {
            if (iteratorrodzica >= lmiast) {
                iteratorrodzica = 1;
            }
            if (iteratordziecka >= lmiast) {
                iteratordziecka = 1;
            }
            boolean powt = true;

            for (int k = 1; k < lmiast + 1; ++k) {// sprawdzenie powtorzeń
                if (nastepnaPopulacja[i].proponowanaDroga[k] ==
                    aktualnaPopulacja[p2].proponowanaDroga[iteratorrodzica]) {
                    powt = false;
                    break;
                }

            }
            if (powt) {
                licznikmiast++;
                nastepnaPopulacja[i].proponowanaDroga[iteratordziecka] = aktualnaPopulacja[p2].proponowanaDroga[iteratorrodzica];
                iteratordziecka++;
            }
            iteratorrodzica++;


        }


    }
    delete[] aktualnaPopulacja;
    delete[] nextparents;
    aktualnaPopulacja = nastepnaPopulacja;


}

void Gmain::localimprovement() {

    int reszta = (10 * population / 100) + 1;


    for (int i = 0; i < reszta; ++i) {
boolean pop= false;
int tempdrog;
int i1, i2;
        for (int j = 1; j < lmiast  - 1; ++j) {
            for (int k = 1 + j; k < lmiast ; ++k) {

                int indeks1 = j;
                int indeks2 = k;
                if (indeks1 != indeks2) {

                    int staradroga = aktualnaPopulacja[i].wartosc;
//                    cout<<"star "<<staradroga<<endl;
                    int nowadroga = aktualnaPopulacja[i].wartosc- macierz[aktualnaPopulacja[i].proponowanaDroga[indeks1 -1]][aktualnaPopulacja[i].proponowanaDroga[indeks1]]-macierz[aktualnaPopulacja[i].proponowanaDroga[indeks1]][aktualnaPopulacja[i].proponowanaDroga[indeks1 + 1]]- macierz[aktualnaPopulacja[i].proponowanaDroga[indeks2 -1]][aktualnaPopulacja[i].proponowanaDroga[indeks2]]-macierz[aktualnaPopulacja[i].proponowanaDroga[indeks2]][aktualnaPopulacja[i].proponowanaDroga[indeks2 + 1]];aktualnaPopulacja[i].wartosc = nowadroga;
//                    cout<<"tempdrog"<<tempdrog<<endl;
                    int pier = aktualnaPopulacja[i].proponowanaDroga[indeks1];
                    int drug = aktualnaPopulacja[i].proponowanaDroga[indeks2];
                    aktualnaPopulacja[i].proponowanaDroga[indeks1] = drug;
                    aktualnaPopulacja[i].proponowanaDroga[indeks2] = pier;

                    nowadroga = aktualnaPopulacja[i].wartosc
                                + macierz[aktualnaPopulacja[i].proponowanaDroga[indeks1 -
                                                                                1]][aktualnaPopulacja[i].proponowanaDroga[indeks1]]
                                +
                                macierz[aktualnaPopulacja[i].proponowanaDroga[indeks1]][aktualnaPopulacja[i].proponowanaDroga[
                                        indeks1 + 1]]
                                + macierz[aktualnaPopulacja[i].proponowanaDroga[indeks2 -
                                                                                1]][aktualnaPopulacja[i].proponowanaDroga[indeks2]]
                                +
                                macierz[aktualnaPopulacja[i].proponowanaDroga[indeks2]][aktualnaPopulacja[i].proponowanaDroga[
                                        indeks2 + 1]];
//                    cout<<"tempdrog2"<<tempdrog<<endl;

                    if (nowadroga <= staradroga) {
                        pop=true;
                        i1=indeks1;
                        i2=indeks2;
                        tempdrog=nowadroga;
                        aktualnaPopulacja[i].proponowanaDroga[indeks1] = pier;
                        aktualnaPopulacja[i].proponowanaDroga[indeks2] = drug;
                        aktualnaPopulacja[i].wartosc = staradroga;
                    } else {
                        aktualnaPopulacja[i].proponowanaDroga[indeks1] = pier;
                        aktualnaPopulacja[i].proponowanaDroga[indeks2] = drug;
                        aktualnaPopulacja[i].wartosc = staradroga;
                    }


                }


            }
        }
        if (pop){
            aktualnaPopulacja[i].wartosc = tempdrog;

            int pier = aktualnaPopulacja[i].proponowanaDroga[i1];
            int drug = aktualnaPopulacja[i].proponowanaDroga[i2];
            aktualnaPopulacja[i].proponowanaDroga[i1] = drug;
            aktualnaPopulacja[i].proponowanaDroga[i2] = pier;
        }

    }






}

void Gmain::mutatechildren() {

    int reszta = (10 * population / 100) + 1;
    for (int i = reszta; i < population; ++i) {

        double probab = randomnumber();
        if (probab < mutProbab) {
            mutate(i);
        }
    }

}

boolean Gmain::checksolutions(int li) {
    boolean poprawa = false;
    int bestfound = nrozw;
    int indeks = -1;
    for (int i = 0; i < population; ++i) {
        if (aktualnaPopulacja[i].wartosc < bestfound) {
            bestfound = aktualnaPopulacja[i].wartosc;
            indeks = i;
            poprawa = true;
        }
    }
    if (poprawa) {
        nrozw = aktualnaPopulacja[indeks].wartosc;
        for (int j = 0; j < lmiast + 1; ++j) {
            rozwnaj[j] = aktualnaPopulacja[indeks].proponowanaDroga[j];


        }
        float prd = 100.0 * (((float) nrozw - (float) hamilton) / (float) hamilton);
        cout << li << "    " << nrozw << "    " << setprecision(5) << prd << "%" << endl;
    }


    return poprawa;
}


