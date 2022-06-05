#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "MST.h"

using namespace std;


MSTmain::MSTmain(string nazwap, boolean los, int lw, float dens, boolean series) {
    macierz = NULL;
    listas = NULL;
    density = dens;
    sto = series;

    if (los) {
        cout << "Tworze losowy graf" << endl;
        lwierzch = lw;
        generategraff(lw, dens);
    } else {
        cout << "Tworze graf z pliku" << endl;
        wczytajzpliku(nazwap);
    }


}

MSTmain::~MSTmain() {
    purge();
}

void MSTmain::menu() {
    //menu
    int wyb = 0;
    boolean koniec = false;
    while (!koniec) {
        cout << "Co chcesz Zrobic?" << endl << endl;
        cout << "1-Wyswietl Macierz i Liste" << endl;
        cout << "2-Metoda Prima dla Macierzy" << endl;
        cout << "3-Metoda Prima dla Listy" << endl;
        cout << "4-Metoda Kruskala dla Macierzy" << endl;
        cout << "5-Metoda Kruskala dla Listy" << endl;
        cout << "6-Wroc do MainMenu" << endl;
        cin >> wyb;
        switch (wyb) {
            case 1:


                if (lwierzch < 26) {
                    show1();
                    cout << endl;
                    show2();
                }


                break;
            case 2:

                if (!sto) {//prim dla macierzy
                    long long int frequency;
                    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                    long long int t = primmac();
                    cout << "Time [s]  = " << fixed << setprecision(3) << (float) t / frequency << endl;
                    cout << "Time [ms] = " << setprecision(0) << (1000.0 * t) / frequency << endl;
                    cout << "Time [us] = " << setprecision(0) << (1000000.0 * t) / frequency << endl << endl;
                } else {
                    long long int suma = 0;
                    long long int frequency;
                    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                    for (int i = 0; i < 100; ++i) {
                        cout << "Graf " << i + 1 << endl;
                        long long int t = primmac();
                        suma += t;
                        cout << "Czas grafu [us] = " << setprecision(0) << (1000000.0 * t) / frequency << endl;
                        cout << "Suma czasu [us] = " << setprecision(0) << (1000000.0 * suma) / frequency << endl;
                        generategraff(lwierzch, density);

                    }
                    suma = suma / 100;
                    cout << "Czas dla 100 losowych grafow. Wierzcholki: " << lwierzch << " Gestosc: " << density * 100
                         << endl;
                    cout << "Time [s]  = " << fixed << setprecision(3) << (float) suma / frequency << endl;
                    cout << "Time [ms] = " << setprecision(0) << (1000.0 * suma) / frequency << endl;
                    cout << "Time [us] = " << setprecision(0) << (1000000.0 * suma) / frequency << endl << endl;
                }


                break;
            case 3:
                if (!sto) {// prim dla listy
                    long long int frequency;
                    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                    long long int t = primlists();
                    cout << "Time [s]  = " << fixed << setprecision(3) << (float) t / frequency << endl;
                    cout << "Time [ms] = " << setprecision(0) << (1000.0 * t) / frequency << endl;
                    cout << "Time [us] = " << setprecision(0) << (1000000.0 * t) / frequency << endl << endl;
                } else {
                    long long int suma = 0;
                    long long int frequency;
                    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                    for (int i = 0; i < 100; ++i) {
                        cout << "Graf " << i + 1 << endl;
                        long long int t = primlists();
                        suma += t;
                        cout << "Czas grafu [us] = " << setprecision(0) << (1000000.0 * t) / frequency << endl;
                        cout << "Suma czasu [us] = " << setprecision(0) << (1000000.0 * suma) / frequency << endl;
                        generategraff(lwierzch, density);

                    }
                    suma = suma / 100;
                    cout << "Czas dla 100 losowych grafow. Wierzcholki: " << lwierzch << " Gestosc: " << density * 100
                         << endl;
                    cout << "Time [s]  = " << fixed << setprecision(3) << (float) suma / frequency << endl;
                    cout << "Time [ms] = " << setprecision(0) << (1000.0 * suma) / frequency << endl;
                    cout << "Time [us] = " << setprecision(0) << (1000000.0 * suma) / frequency << endl << endl;
                }

                break;
            case 4:
                if (!sto) {// kruskal dla macierzy

                    long long int frequency;
                    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                    long long int t = kruskalmac();
                    cout << "Time [s]  = " << fixed << setprecision(3) << (float) t / frequency << endl;
                    cout << "Time [ms] = " << setprecision(0) << (1000.0 * t) / frequency << endl;
                    cout << "Time [us] = " << setprecision(0) << (1000000.0 * t) / frequency << endl << endl;
                } else {
                    long long int suma = 0;
                    long long int frequency;
                    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                    for (int i = 0; i < 100; ++i) {
                        cout << "Graf " << i + 1 << endl;
                        long long int t = kruskalmac();
                        suma += t;
                        cout << "Czas grafu [us] = " << setprecision(0) << (1000000.0 * t) / frequency << endl;
                        cout << "Suma czasu [us] = " << setprecision(0) << (1000000.0 * suma) / frequency << endl;
                        generategraff(lwierzch, density);

                    }
                    suma = suma / 100;
                    cout << "Czas dla 100 losowych grafow. Wierzcholki: " << lwierzch << " Gestosc: " << density * 100
                         << endl;
                    cout << "Time [s]  = " << fixed << setprecision(3) << (float) suma / frequency << endl;
                    cout << "Time [ms] = " << setprecision(0) << (1000.0 * suma) / frequency << endl;
                    cout << "Time [us] = " << setprecision(0) << (1000000.0 * suma) / frequency << endl << endl;
                }

                break;
            case 5:
                if (!sto) {// kruskal dla listy
                    long long int frequency;
                    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                    long long int t = kruskallists();
                    cout << "Time [s]  = " << fixed << setprecision(3) << (float) t / frequency << endl;
                    cout << "Time [ms] = " << setprecision(0) << (1000.0 * t) / frequency << endl;
                    cout << "Time [us] = " << setprecision(0) << (1000000.0 * t) / frequency << endl << endl;
                } else {
                    long long int suma = 0;
                    long long int frequency;
                    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                    for (int i = 0; i < 100; ++i) {
                        cout << "Graf " << i + 1 << endl;
                        long long int t = kruskallists();
                        suma += t;
                        cout << "Czas grafu [us] = " << setprecision(0) << (1000000.0 * t) / frequency << endl;
                        cout << "Suma czasu [us] = " << setprecision(0) << (1000000.0 * suma) / frequency << endl;
                        generategraff(lwierzch, density);

                    }
                    suma = suma / 100;
                    cout << "Czas dla 100 losowych grafow. Wierzcholki: " << lwierzch << " Gestosc: " << density * 100
                         << endl;
                    cout << "Time [s]  = " << fixed << setprecision(3) << (float) suma / frequency << endl;
                    cout << "Time [ms] = " << setprecision(0) << (1000.0 * suma) / frequency << endl;
                    cout << "Time [us] = " << setprecision(0) << (1000000.0 * suma) / frequency << endl << endl;
                }

                break;
            case 6:
                koniec = true;

                break;
            case 0:
                koniec = true;
                break;
            default:
                break;

        }
    }

}

int MSTmain::lkraw(int lwi, float densi) {// obliczanie liczby krawędzi dla generatora
    int likraw = ((lwi * (lwi - 1)) / 2) * densi;
    return likraw;
}


void MSTmain::generategraff(int lwi, float densi) {//generowanie losowego grafu
    srand(time(NULL));
    if ((macierz != NULL) || (listas != NULL)) {//czyszczenie
        purge();
    }

    listas = new ellisty *[lwi];
    macierz = new int *[lwi];

    for (int i = 0; i < lwi; ++i) {//wiersze w macierzy
        macierz[i] = new int[lwi];
    }

    for (int i = 0; i < lwi; ++i) {//zapełnianie wstępne maciezy i listy
        listas[i] = NULL;
        for (int j = 0; j < lwi; ++j) {
            macierz[i][j] = 999; // 999 to umowna nieskończoność
        }
    }


    int lk = lkraw(lwi, densi);
    lkrawedzi = lk;
    kraw *ttab = new kraw[lk];//tablica pomocnicza do generacji

    int w1 = 0;
    int w2 = 0;
    int w3 = 0;

    for (int i = 0; i < lk; ++i) {
        boolean repeating = true;
        w3 = rand() % 26;
        if (i < (lwi - 1)) {// ciągłość
            w1 = i;
            w2 = i + 1;
        } else {
            while (repeating) {//losowanie


                w1 = rand() % lwi;
                w2 = rand() % lwi;

                if (w1 != w2) {
                    repeating = false;
                    kraw temp;

                    for (int j = 0; j < lk; ++j) {
                        temp = ttab[j];
                        if (temp.wp == w1 && temp.wk == w2) {
                            repeating = true;

                            break;
                        }
                        if (temp.wp == w2 && temp.wk == w1) {
                            repeating = true;

                            break;
                        }


                    }
                }


            }


        }


        ttab[i].wp = w1;
        ttab[i].wk = w2;
        ttab[i].waga = w3;

    }

    kraw temp;
    for (int i = 0; i < lk; ++i) {//wprowadzenie danych do listy i macierzy
        temp = ttab[i];
        macierz[temp.wp][temp.wk] = temp.waga;
        macierz[temp.wk][temp.wp] = temp.waga;
        ellisty *p = new ellisty;
        p->wk = temp.wk;
        p->waga = temp.waga;
        p->next = listas[temp.wp];
        listas[temp.wp] = p;

        ellisty *r = new ellisty;
        r->wk = temp.wp;
        r->waga = temp.waga;
        r->next = listas[temp.wk];
        listas[temp.wk] = r;


    }
    delete[] ttab;


}

bool MSTmain::file_read_line(ifstream &file, int *tab, int size) {
    string s;
    getline(file, s);

    if (file.fail() || s.empty())
        return (false);

    istringstream in_ss(s);

    for (int i = 0; i < size; i++) {
        in_ss >> tab[i];
        if (in_ss.fail())
            return (false);
    }
    return (true);
}


void MSTmain::wczytajzpliku(string n) {

    if ((macierz != NULL) || (listas != NULL)) {//czyszczenie
        purge();
    }


    ifstream file;
    int tab[4];
    file.open(n.c_str());

    if (file.is_open()) {
        if (file_read_line(file, tab, 4)) {
            lkrawedzi = tab[0];
            lwierzch = tab[1];

            if (lkrawedzi < 1) {
                cout << "Błąd krawedzi" << endl;
                exit(20);
            }

            if (lwierzch < 2) {
                cout << "Błąd wierzcholkow" << endl;
                exit(20);
            }

            listas = new ellisty *[lwierzch];
            macierz = new int *[lwierzch];

            for (int i = 0; i < lwierzch; ++i) {//wiersze w macierzy
                macierz[i] = new int[lwierzch];
            }

            for (int i = 0; i < lwierzch; ++i) {//zapełnianie wstępne maciezy i listy
                listas[i] = NULL;
                for (int j = 0; j < lwierzch; ++j) {
                    macierz[i][j] = 999; // 999 to umowna nieskończoność
                }
            }
            for (int i = 0; i < lkrawedzi; i++)
                if (file_read_line(file, tab, 3)) {
                    int edge_start = tab[0];
                    int edge_end = tab[1];
                    int edge_weight = tab[2];

                    macierz[edge_start][edge_end] = edge_weight;
                    macierz[edge_end][edge_start] = edge_weight;
                    ellisty *p = new ellisty;
                    p->wk = edge_end;
                    p->waga = edge_weight;
                    p->next = listas[edge_start];
                    listas[edge_start] = p;

                    ellisty *r = new ellisty;
                    r->wk = edge_start;
                    r->waga = edge_weight;
                    r->next = listas[edge_end];
                    listas[edge_end] = r;


                } else {
                    cout << "File error - READ EDGE" << endl;
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

void MSTmain::purge() {//czyszczenie
    if (macierz == NULL) {
        cout << "macierz pusta" << endl;
        return;
    }
    if (listas == NULL) {
        cout << "lista pusta" << endl;
        return;
    }
    cout << "Czyszcze liste i macierz" << endl;

    for (int i = 0; i < lwierzch; i++) {
        delete[] macierz[i];
    }
    delete[] macierz;

    for (int i = 0; i < lwierzch; ++i) {
        ellisty *p = listas[i];
        ellisty *r;
        while (p) {
            r = p;
            p = p->next;
            delete r;
        }

    }
    delete[] listas;

    macierz = NULL;
    listas = NULL;

}

void MSTmain::show1() {// wyświetlanie macierzy
    cout << "     #";
    for (int i = 0; i < lwierzch; i++) cout << setw(4) << i;
    cout << endl;
    for (int i = 0; i < ((lwierzch + 2) * 4); i++) cout << "#";
    cout << endl;
    for (int i = 0; i < lwierzch; i++) {
        cout << setw(4) << i << " #";
        for (int j = 0; j < lwierzch; j++) {
            if (macierz[i][j] == 999) {
                cout << " ---";
            } else { cout << setw(4) << macierz[i][j]; }
        }
        cout << endl;
    }
}

void MSTmain::show2() {// wyświetlanie listy
    for (int i = 0; i < lwierzch; i++) {
        cout << "[ " << i << " ] =";
        ellisty *p = listas[i];
        while (p) {
            cout << setw(4) << p->wk << "|" << setw(2) << p->waga;
            p = p->next;
        }
        cout << endl;
    }
}

kraw MSTmain::minkraw(kraw2 *list, kraw2 *rozps) {


    int weight = 999;
    kraw2 *lk = list;
    kraw2 *lr = rozps;
    kraw minkraw;

    while (lk != NULL) {
        if (lk->waga < weight) {

            boolean nierozp = true;
            lr = rozps;
            while (lr != NULL) {

                if ((lk->wk == lr->wk) || (lk->wk == 0)) {
                    nierozp = false;
                    break;
                }

                lr = lr->next;

            }

            if (nierozp) {
                minkraw.waga = lk->waga;
                minkraw.wp = lk->wp;
                minkraw.wk = lk->wk;
                weight = lk->waga;
            }

        }
        lk = lk->next;
    }

    return minkraw;

}

long long int MSTmain::primmac() {

    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();

    int aktalnywierzch = 0;

    kraw2 *startcraw = NULL;// lista krawędzi łączących wierzchołki rozpatrzone z resztą
    kraw2 *endcraw = NULL;

    kraw2 *listakraws = NULL;
    kraw2 *listakrawk = NULL;

    int weight, rozpatrzone = 1, suma = 0;


    while (rozpatrzone < lwierzch) {

        for (int j = 0; j < lwierzch; ++j) {
            weight = macierz[aktalnywierzch][j];
            if (weight < 999) {
                kraw2 *temp = new kraw2;//dodawanie krawędzi do rozptrzenia

                temp->wp = aktalnywierzch;
                temp->wk = j;
                temp->waga = weight;
                temp->next = NULL;

                if (startcraw == NULL) {
                    startcraw = temp;
                    endcraw = temp;
                } else {
                    endcraw->next = temp;
                    endcraw = temp;
                }

            }
        }

        kraw dodana_krawedz = minkraw(startcraw, listakraws);// wybranie minimalnej z dostępnych krawędzi

        kraw2 *temp = new kraw2;// dodawanie krawędzi do listy rozpatrzonych
        temp->wp = dodana_krawedz.wp;
        temp->wk = dodana_krawedz.wk;
        temp->waga = dodana_krawedz.waga;
        temp->next = NULL;
        aktalnywierzch = dodana_krawedz.wk;
        suma += dodana_krawedz.waga;
        if (listakraws == NULL) {
            listakraws = temp;
            listakrawk = temp;
        } else {
            listakrawk->next = temp;
            listakrawk = temp;
        }
        rozpatrzone++;


    }
    elapsed = read_QPC() - start;

    if (!sto) {
        cout << "Krawedz / Waga" << endl;// wypisanie krawędzi
        kraw2 *temp = listakraws;
        while (temp != NULL) {
            cout << setw(2) << temp->wp << " - " << setw(2) << temp->wk << " /" << setw(2) << temp->waga << endl;
            temp = temp->next;
        }
        cout << "MST = " << suma << endl;
    }


    kraw2 *temp = listakraws;
    kraw2 *temp2;
    while (temp != NULL) {// czyszczenie list
        temp2 = temp;
        temp = temp->next;
        delete temp2;
    }
    temp = startcraw;
    while (temp != NULL) {
        temp2 = temp;
        temp = temp->next;
        delete temp2;
    }

    delete temp;
    return elapsed;

}


long long int MSTmain::primlists() {
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();

    int aktalnywierzch = 0;

    kraw2 *startcraw = NULL;// lista krawędzi łączących wierzchołki rozpatrzone z resztą
    kraw2 *endcraw = NULL;

    kraw2 *listakraws = NULL;
    kraw2 *listakrawk = NULL;

    int weight, rozpatrzone = 1, suma = 0;


    while (rozpatrzone < lwierzch) {

        ellisty *p = listas[aktalnywierzch];
        while (p != NULL) {
            weight = p->waga;

            kraw2 *temp = new kraw2;//dodawanie krawędzi do rozptrzenia

            temp->wp = aktalnywierzch;
            temp->wk = p->wk;
            temp->waga = weight;
            temp->next = NULL;

            if (startcraw == NULL) {
                startcraw = temp;
                endcraw = temp;
            } else {
                endcraw->next = temp;
                endcraw = temp;
            }
            p = p->next;

        }

        kraw dodana_krawedz = minkraw(startcraw, listakraws);// wybranie minimalnej z dostępnych krawędzi

        kraw2 *temp = new kraw2;// dodawanie krawędzi do listy rozpatrzonych
        temp->wp = dodana_krawedz.wp;
        temp->wk = dodana_krawedz.wk;
        temp->waga = dodana_krawedz.waga;
        temp->next = NULL;
        aktalnywierzch = dodana_krawedz.wk;
        suma += dodana_krawedz.waga;
        if (listakraws == NULL) {
            listakraws = temp;
            listakrawk = temp;
        } else {
            listakrawk->next = temp;
            listakrawk = temp;
        }
        rozpatrzone++;

    }
    elapsed = read_QPC() - start;
    if (!sto) {
        cout << "Krawedz / Waga" << endl;// wypisanie krawędzi
        kraw2 *temp = listakraws;
        while (temp != NULL) {
            cout << setw(2) << temp->wp << " - " << setw(2) << temp->wk << " /" << setw(2) << temp->waga << endl;
            temp = temp->next;
        }
        cout << "MST = " << suma << endl;
    }


    kraw2 *temp = listakraws;
    kraw2 *temp2;
    while (temp != NULL) {// czyszczenie list

        temp2 = temp;
        temp = temp->next;
        delete temp2;
    }
    temp = startcraw;
    while (temp != NULL) {

        temp2 = temp;
        temp = temp->next;
        delete temp2;
    }
    delete temp;
    return elapsed;

}

long long int MSTmain::kruskalmac() {

    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();

    int *grupa = new int[lwierzch];
    kraw *krawedzie = new kraw[lkrawedzi * 2];
    int k = 0, suma = 0;
    for (int i = 0; i < lwierzch; ++i) {
        grupa[i] = i;
    }


    kraw2 *listakraws = NULL;
    kraw2 *listakrawk = NULL;

    for (int i = 0; i < lwierzch; i++) {
        for (int j = 0; j < lwierzch; j++) {
            if (macierz[i][j] < 999) {

                kraw temp;//dodawanie krawędzi

                temp.wp = i;
                temp.wk = j;
                temp.waga = macierz[i][j];

                boolean npowt = true;
                for (int l = 0; l < k; ++l) {
                    kraw temp2 = krawedzie[l];
                    if (temp.wp == temp2.wk && temp.wk == temp2.wp){
                        npowt= false;
                        break;
                    }

                }

                if (npowt){
                    krawedzie[k] = temp;
                    k++;
                }



            }
        }
    }

    for (int i = 0; i < k - 1; i++)// sortowanie krawedzi
    {
        boolean przerwij = true;

        for (int j = 0; j < k - i - 1; j++) {

            if (krawedzie[j].waga > krawedzie[j + 1].waga) {
                przerwij = false;
                kraw temp = krawedzie[j];
                krawedzie[j] = krawedzie[j + 1];
                krawedzie[j + 1] = temp;

            }
        }
        if (przerwij) {
            break;
        }
    }

    int licznik = 0;
    for (int i = 0; i < lkrawedzi; ++i) {
        if (licznik == (lwierzch - 1)) {
            break;
        }
        kraw badanakraw = krawedzie[i];
        int a, b;
        a = grupa[badanakraw.wp];
        b = grupa[badanakraw.wk];
        if (a != b) {
            licznik++;

            kraw2 *temp = new kraw2;// dodawanie krawędzi do listy rozpatrzonych
            temp->wp = badanakraw.wp;
            temp->wk = badanakraw.wk;
            temp->waga = badanakraw.waga;
            temp->next = NULL;
            suma += badanakraw.waga;
            if (listakraws == NULL) {
                listakraws = temp;
                listakrawk = temp;
            } else {
                listakrawk->next = temp;
                listakrawk = temp;
            }

            for (int j = 0; j < lwierzch; ++j) {
                if (grupa[j] == b) {
                    grupa[j] = a;
                }

            }


        }


    }

    elapsed = read_QPC() - start;
    if (!sto) {
        cout << "Krawedz / Waga" << endl;// wypisanie krawędzi
        kraw2 *temp = listakraws;
        while (temp != NULL) {
            cout << setw(2) << temp->wp << " - " << setw(2) << temp->wk << " /" << setw(2) << temp->waga << endl;
            temp = temp->next;
        }
        cout << "MST = " << suma << endl;
    }


    delete[] grupa;
    delete[] krawedzie;
    kraw2 *temp = listakraws;
    kraw2 *temp2;
    while (temp != NULL) {// czyszczenie list

        temp2 = temp;
        temp = temp->next;
        delete temp2;
    }
    delete temp;
    return elapsed;
}

long long int MSTmain::kruskallists() {

    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();

    int *grupa = new int[lwierzch];
    kraw *krawedzie = new kraw[lkrawedzi * 2];
    int k = 0, suma = 0;
    for (int i = 0; i < lwierzch; ++i) {
        grupa[i] = i;
    }

    kraw2 *listakraws = NULL;
    kraw2 *listakrawk = NULL;

    for (int i = 0; i < lwierzch; i++) {
        ellisty *p = listas[i];
        while (p) {
            kraw temp;//dodawanie krawędzi

            temp.wp = i;
            temp.wk = p->wk;
            temp.waga = p->waga;
            boolean npowt = true;
            for (int l = 0; l < k; ++l) {
                kraw temp2 = krawedzie[l];
                if (temp.wp == temp2.wk && temp.wk == temp2.wp){
                    npowt= false;
                    break;
                }

            }

            if (npowt){
                krawedzie[k] = temp;
                k++;
            }
            p = p->next;
        }
    }


    for (int i = 0; i < k - 1; i++)// sortowanie krawedzi
    {
        boolean przerwij = true;

        for (int j = 0; j < k - i - 1; j++) {

            if (krawedzie[j].waga > krawedzie[j + 1].waga) {
                przerwij = false;
                kraw temp = krawedzie[j];
                krawedzie[j] = krawedzie[j + 1];
                krawedzie[j + 1] = temp;

            }
        }
        if (przerwij) {
            break;
        }
    }

    int licznik = 0;
    for (int i = 0; i < lkrawedzi; ++i) {
        if (licznik == (lwierzch - 1)) {
            break;
        }
        kraw badanakraw = krawedzie[i];
        int a, b;
        a = grupa[badanakraw.wp];
        b = grupa[badanakraw.wk];
        if (a != b) {
            licznik++;
            kraw2 *temp = new kraw2;// dodawanie krawędzi do listy rozpatrzonych
            temp->wp = badanakraw.wp;
            temp->wk = badanakraw.wk;
            temp->waga = badanakraw.waga;
            temp->next = NULL;
            suma += badanakraw.waga;
            if (listakraws == NULL) {
                listakraws = temp;
                listakrawk = temp;
            } else {
                listakrawk->next = temp;
                listakrawk = temp;
            }

            for (int j = 0; j < lwierzch; ++j) {
                if (grupa[j] == b) {
                    grupa[j] = a;
                }

            }


        }


    }
    elapsed = read_QPC() - start;
    if (!sto) {
        cout << "Krawedz / Waga" << endl;// wypisanie krawędzi
        kraw2 *temp = listakraws;
        while (temp != NULL) {
            cout << setw(2) << temp->wp << " - " << setw(2) << temp->wk << " /" << setw(2) << temp->waga << endl;
            temp = temp->next;
        }
        cout << "MST = " << suma << endl;
    }


    delete[] grupa;
    delete[] krawedzie;
    kraw2 *temp = listakraws;
    kraw2 *temp2;
    while (temp != NULL) {// czyszczenie list

        temp2 = temp;
        temp = temp->next;
        delete temp2;
    }
    delete temp;
    return elapsed;

}

long long int MSTmain::read_QPC() {//pomiar czasu
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int) count.QuadPart);
}






