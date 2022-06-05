#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "ShortestPath.h"


SPmain::SPmain(string nazwap, boolean los, int lw, float dens, boolean series) {
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

SPmain::~SPmain() {
    purge();
}

void SPmain::menu() {
    //menu
    int wyb = 0;
    boolean koniec = false;
    while (!koniec) {
        cout << "Co chcesz Zrobic?" << endl << endl;
        cout << "1-Wyswietl Macierz i Liste" << endl;
        cout << "2-Metoda Dijkstry dla Macierzy" << endl;
        cout << "3-Metoda Dijkstry dla Listy" << endl;
        cout << "4-Metoda Bellmana-Forda dla Macierzy" << endl;
        cout << "5-Metoda Bellmana-Forda dla Listy" << endl;
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

                if (!sto) {// dijkstra macierz
                    long long int frequency;
                    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                    long long int t = dijkstramac();
                    cout << "Time [s]  = " << fixed << setprecision(3) << (float) t / frequency << endl;
                    cout << "Time [ms] = " << setprecision(0) << (1000.0 * t) / frequency << endl;
                    cout << "Time [us] = " << setprecision(0) << (1000000.0 * t) / frequency << endl << endl;
                } else {
                    long long int suma = 0;
                    long long int frequency;
                    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                    for (int i = 0; i < 100; ++i) {
                        cout << "Graf " << i + 1 << endl;
                        long long int t = dijkstramac();
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
                if (!sto) {// dijkstra lista
                    long long int frequency;
                    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                    long long int t = dijkstralist();
                    cout << "Time [s]  = " << fixed << setprecision(3) << (float) t / frequency << endl;
                    cout << "Time [ms] = " << setprecision(0) << (1000.0 * t) / frequency << endl;
                    cout << "Time [us] = " << setprecision(0) << (1000000.0 * t) / frequency << endl << endl;
                } else {
                    long long int suma = 0;
                    long long int frequency;
                    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                    for (int i = 0; i < 100; ++i) {
                        cout << "Graf " << i + 1 << endl;
                        long long int t = dijkstralist();
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
                if (!sto) {//bel-ford macierz

                    long long int frequency;
                    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                    long long int t = belmanfmac();
                    cout << "Time [s]  = " << fixed << setprecision(3) << (float) t / frequency << endl;
                    cout << "Time [ms] = " << setprecision(0) << (1000.0 * t) / frequency << endl;
                    cout << "Time [us] = " << setprecision(0) << (1000000.0 * t) / frequency << endl << endl;
                } else {
                    long long int suma = 0;
                    long long int frequency;
                    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                    for (int i = 0; i < 100; ++i) {
                        cout << "Graf " << i + 1 << endl;
                        long long int t = belmanfmac();
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
                if (!sto) {//bel-ford lista
                    long long int frequency;
                    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                    long long int t = belmanflist();
                    cout << "Time [s]  = " << fixed << setprecision(3) << (float) t / frequency << endl;
                    cout << "Time [ms] = " << setprecision(0) << (1000.0 * t) / frequency << endl;
                    cout << "Time [us] = " << setprecision(0) << (1000000.0 * t) / frequency << endl << endl;
                } else {
                    long long int suma = 0;
                    long long int frequency;
                    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
                    for (int i = 0; i < 100; ++i) {
                        cout << "Graf " << i + 1 << endl;
                        long long int t = belmanflist();
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

int SPmain::lkraw(int lwi, float densi) {
    int likraw = ((lwi * (lwi - 1)) / 2) * densi;
    return likraw;
}

void SPmain::loswpwk(int l) {// losowe krawędzie startowe i końcowe
    srand(time(NULL));
    int w1 = 0;
    int w2 = 0;
    while (w1 == w2) {
        w1 = rand() % l;
        w2 = rand() % l;
    }
    wierzchp = w1;
    wierzchk = w2;
}

void SPmain::generategraff(int lwi, float densi) {
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

    for (int i = 0; i < lk; ++i) {
        ttab[i].wp = ttab[i].wk = ttab[i].waga = -22;
    }

    int w1 = 0;
    int w2 = 0;
    int w3 = 0;

    for (int i = 0; i < lk; ++i) {
        boolean repeating = true;
        w3 = rand() % 26;
        if (i < (lwi - 1)) {// ciągłość
            w1 = i;
            w2 = i + 1;
        } else if (i == (lwi - 1)) {
            w1 = i;
            w2 = 0;
        } else {
            while (repeating) {// losowanie

//
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
        ellisty *p = new ellisty;
        p->wk = temp.wk;
        p->waga = temp.waga;
        p->next = listas[temp.wp];
        listas[temp.wp] = p;

    }
    loswpwk(lwi);
    delete[] ttab;
}

bool SPmain::file_read_line(ifstream &file, int *tab, int size) {
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

void SPmain::wczytajzpliku(string n) {
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
            wierzchp = tab[2];
            wierzchk = tab[3];

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
                    ellisty *p = new ellisty;
                    p->wk = edge_end;
                    p->waga = edge_weight;
                    p->next = listas[edge_start];
                    listas[edge_start] = p;


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

void SPmain::show1() {// wyświetlenie macierzy
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

void SPmain::show2() {// wyświetlenie listy
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

long long int SPmain::dijkstramac() {
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();


    //tworzenie macierzy pomocniczych
    boolean *rozpatrzony = new boolean[lwierzch];
    int *poprzednik = new int[lwierzch];
    int *droga = new int[lwierzch];
    //zapełnienie macierzy
    for (int i = 0; i < lwierzch; ++i) {
        poprzednik[i] = -2;
        droga[i] = 999999;
        rozpatrzony[i] = false;
    }
    //ustalenie wartości dla wierzchołka startowego
    poprzednik[wierzchp] = -1;
    droga[wierzchp] = 0;

    for (int i = 0; i < lwierzch; ++i) {

        int min = 999999, badanywierzchoek = 0;

        for (int j = 0; j < lwierzch; ++j) {//znaezienie wierzchołka niezbadanego z najkrótszą trasą
            if (!rozpatrzony[j]) {
                if (droga[j] < min) {
                    min = droga[j];
                    badanywierzchoek = j;
                }
            }
        }

        for (int j = 0; j < lwierzch; ++j) {//relaksacja istniejących krawędzi
            kraw temp;
            temp.wp = badanywierzchoek;
            temp.wk = j;
            temp.waga = macierz[badanywierzchoek][j];

            if (temp.waga < 0) {// ostrzerzenie
                cout << endl << "WYKRYTO KRAWEDZ UJEMNA" << endl;
                cout << "WYNIK MOZE BYC NIEPOPRAWNY" << endl;

            }

            if (temp.waga < 999) {
                if (temp.wk == wierzchp) {
                    //
                } else if (droga[temp.wk] > (droga[badanywierzchoek] + temp.waga)) {
                    droga[temp.wk] = (droga[badanywierzchoek] + temp.waga);
                    poprzednik[temp.wk] = badanywierzchoek;
                }
            }


        }
        rozpatrzony[badanywierzchoek] = true;
    }


    elscie **scierzka;// lista ścierzek do wyświetlaniawyników
    scierzka = new elscie *[lwierzch];


    for (int i = 0; i < lwierzch; ++i) {//zapełnianie wstępne
        scierzka[i] = NULL;
    }

    for (int i = 0; i < lwierzch; ++i) {
        elscie *p = new elscie;
        p->path = i;
        p->next = NULL;
        scierzka[i] = p;
        int pop = poprzednik[i];
        while (pop != -1) {

            p = new elscie;
            p->path = pop;
            p->next = scierzka[i];
            scierzka[i] = p;
            pop = poprzednik[pop];

        }

    }

    elapsed = read_QPC() - start;
    if (!sto) {
        //wyniki
        cout << "Start: " << wierzchp << " Koniec: " << wierzchk << endl;
        cout << "  End:  " << "Dist: " << "Path: " << endl;
        for (int i = 0; i < lwierzch; i++) {
            cout << setw(4) << i << " | " << setw(4) << droga[i] << " | ";
            elscie *p = scierzka[i];
            while (p) {
                cout << setw(4) << p->path << " ";
                p = p->next;
            }
            cout << endl;
        }
    }

// czyszczeine listy ścierzek
    for (int i = 0; i < lwierzch; ++i) {
        elscie *p = scierzka[i];
        elscie *r;
        while (p) {
            r = p;
            p = p->next;
            delete r;
        }

    }
    delete[] scierzka;
    return elapsed;

}

long long int SPmain::dijkstralist() {
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();

//tworzenie macierzy pomocniczych
    boolean *rozpatrzony = new boolean[lwierzch];
    int *poprzednik = new int[lwierzch];
    int *droga = new int[lwierzch];
    //zapełnienie macierzy
    for (int i = 0; i < lwierzch; ++i) {
        poprzednik[i] = -2;
        droga[i] = 999999;
        rozpatrzony[i] = false;
    }
    //ustalenie wartości dla wierzchołka startowego
    poprzednik[wierzchp] = -1;
    droga[wierzchp] = 0;

    for (int i = 0; i < lwierzch; ++i) {

        int min = 999999, badanywierzchoek = 0;

        for (int j = 0; j < lwierzch; ++j) {//znaezienie wierzchołka niezbadanego z najkrótszą trasą
            if (!rozpatrzony[j]) {
                if (droga[j] < min) {
                    min = droga[j];
                    badanywierzchoek = j;
                }
            }
        }
        ellisty *p = listas[badanywierzchoek];
        while (p) {
            if (p->waga < 0) {// ostrzerzenie
                cout << endl << "WYKRYTO KRAWEDZ UJEMNA" << endl;
                cout << "WYNIK MOZE BYC NIEPOPRAWNY" << endl;

            }
            if (p->wk == wierzchp) {
                //
            } else if (droga[p->wk] > (droga[badanywierzchoek] + p->waga)) {
                droga[p->wk] = (droga[badanywierzchoek] + p->waga);
                poprzednik[p->wk] = badanywierzchoek;
            }
            p = p->next;
        }

        rozpatrzony[badanywierzchoek] = true;
    }


    elscie **scierzka;// lista ścierzek do wyświetlaniawyników
    scierzka = new elscie *[lwierzch];


    for (int i = 0; i < lwierzch; ++i) {//zapełnianie wstępne
        scierzka[i] = NULL;
    }

    for (int i = 0; i < lwierzch; ++i) {
        elscie *p = new elscie;
        p->path = i;
        p->next = NULL;
        scierzka[i] = p;

        int pop = poprzednik[i];
        while (pop != -1) {

            p = new elscie;
            p->path = pop;
            p->next = scierzka[i];
            scierzka[i] = p;
            pop = poprzednik[pop];

        }

    }
    elapsed = read_QPC() - start;
    if (!sto) {
        //wyniki
        cout << "Start: " << wierzchp << " Koniec: " << wierzchk << endl;
        cout << "  End:  " << "Dist: " << "Path: " << endl;
        for (int i = 0; i < lwierzch; i++) {
            cout << setw(4) << i << " | " << setw(4) << droga[i] << " | ";
            elscie *p = scierzka[i];
            while (p) {
                cout << setw(4) << p->path << " ";
                p = p->next;
            }
            cout << endl;
        }
    }

// czyszczeine listy ścierzek
    for (int i = 0; i < lwierzch; ++i) {
        elscie *p = scierzka[i];
        elscie *r;
        while (p) {
            r = p;
            p = p->next;
            delete r;
        }

    }
    delete[] scierzka;
    return elapsed;
}

long long int SPmain::belmanfmac() {
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();

//tworzenie macierzy pomocniczych
    int *poprzednik = new int[lwierzch];
    int *droga = new int[lwierzch];
    //zapełnienie macierzy
    for (int i = 0; i < lwierzch; ++i) {
        poprzednik[i] = -2;
        droga[i] = 999999;
    }
    //ustalenie wartości dla wierzchołka startowego
    poprzednik[wierzchp] = -1;
    droga[wierzchp] = 0;

    for (int k = 0; k < lwierzch - 1; ++k) {
        boolean zakoncz=true;
        for (int i = 0; i < lwierzch; ++i) {
            for (int j = 0; j < lwierzch; ++j) {
                if (macierz[i][j] < 999) {
                    if (j == wierzchp) {
                        //
                    } else if (droga[j] > (droga[i] + macierz[i][j])) {
                        zakoncz= false;
                        droga[j] = (droga[i] + macierz[i][j]);
                        poprzednik[j] = i;
                    }
                }
            }
        }

        if (zakoncz){
            break;
        }

    }


    for (int i = 0; i < lwierzch; ++i) {//sprawdzenie cyklu ujemnego
        for (int j = 0; j < lwierzch; ++j) {
            if (macierz[i][j] < 999) {

                if (droga[j] > (droga[i] + macierz[i][j])) {
                    // ostrzerzenie
                    cout << endl << "WYKRYTO CYKL UJEMNY" << endl;
                    cout << "WYNIK MOZE BYC NIEPOPRAWNY" << endl;
                    goto pospr;
                }
            }
        }
    }

pospr:





    elscie **scierzka;// lista ścierzek do wyświetlaniawyników
    scierzka = new elscie *[lwierzch];


    for (int i = 0; i < lwierzch; ++i) {//zapełnianie wstępne
        scierzka[i] = NULL;
    }

    for (int i = 0; i < lwierzch; ++i) {
        elscie *p = new elscie;
        p->path = i;
        p->next = NULL;
        scierzka[i] = p;

        int pop = poprzednik[i];
        while (pop != -1) {
            if (pop == i) {
                break;
            }
            boolean przerwij = false;
            elscie *r = scierzka[i];
            while (r) {
                if (r->path == pop) {
                    przerwij = true;
                    break;
                }
                r = r->next;
            }
            if (przerwij){
                break;
            }

            p = new elscie;
            p->path = pop;
            p->next = scierzka[i];
            scierzka[i] = p;
            pop = poprzednik[pop];

        }

    }
    elapsed = read_QPC() - start;
    if (!sto) {
        //wyniki
        cout << "Start: " << wierzchp << " Koniec: " << wierzchk << endl;
        cout << "  End:  " << "Dist: " << "Path: " << endl;
        for (int i = 0; i < lwierzch; i++) {
            cout << setw(4) << i << " | " << setw(4) << droga[i] << " | ";
            elscie *p = scierzka[i];
            while (p) {
                cout << setw(4) << p->path << " ";
                p = p->next;
            }
            cout << endl;
        }
    }

// czyszczeine listy ścierzek
    for (int i = 0; i < lwierzch; ++i) {
        elscie *p = scierzka[i];
        elscie *r;
        while (p) {
            r = p;
            p = p->next;
            delete r;
        }

    }
    delete[] scierzka;
    return elapsed;

}

long long int SPmain::belmanflist() {
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();

//tworzenie macierzy pomocniczych
    int *poprzednik = new int[lwierzch];
    int *droga = new int[lwierzch];
    //zapełnienie macierzy
    for (int i = 0; i < lwierzch; ++i) {
        poprzednik[i] = -2;
        droga[i] = 999999;
    }
    //ustalenie wartości dla wierzchołka startowego
    poprzednik[wierzchp] = -1;
    droga[wierzchp] = 0;

    for (int i = 0; i < lwierzch - 1; ++i) {
        boolean zakoncz=true;
        for (int j = 0; j < lwierzch; ++j) {
            ellisty *p = listas[j];
            while (p) {
                if (p->wk == wierzchp) {
                    //
                } else if (droga[p->wk] > (droga[j] + p->waga)) {
                    zakoncz= false;
                    droga[p->wk] = (droga[j] + p->waga);
                    poprzednik[p->wk] = j;
                }
                p = p->next;
            }
        }
        if (zakoncz){
            break;
        }

    }

    for (int j = 0; j < lwierzch; ++j) {//sprawdzenie cyklu ujemnego
        ellisty *p = listas[j];
        while (p) {
            if (droga[p->wk] > (droga[j] + p->waga)) {
                // ostrzerzenie
                cout << endl << "WYKRYTO CYKL UJEMNY" << endl;
                cout << "WYNIK MOZE BYC NIEPOPRAWNY" << endl;
                goto pospr2;
            }
            p = p->next;
        }
    }

    pospr2:






    elscie **scierzka;// lista ścierzek do wyświetlaniawyników
    scierzka = new elscie *[lwierzch];


    for (int i = 0; i < lwierzch; ++i) {//zapełnianie wstępne
        scierzka[i] = NULL;
    }

    for (int i = 0; i < lwierzch; ++i) {
        elscie *p = new elscie;
        p->path = i;
        p->next = NULL;
        scierzka[i] = p;

        int pop = poprzednik[i];
        while (pop != -1) {
            if (pop == i) {
                break;
            }
            boolean przerwij = false;
            elscie *r = scierzka[i];
            while (r) {
                if (r->path == pop) {
                    przerwij = true;
                    break;
                }
                r = r->next;
            }
            if (przerwij){
                break;
            }
            p = new elscie;
            p->path = pop;
            p->next = scierzka[i];
            scierzka[i] = p;
            pop = poprzednik[pop];

        }

    }

    elapsed = read_QPC() - start;

    if (!sto) {
        //wyniki
        cout << "Start: " << wierzchp << " Koniec: " << wierzchk << endl;
        cout << "  End:  " << "Dist: " << "Path: " << endl;
        for (int i = 0; i < lwierzch; i++) {
            cout << setw(4) << i << " | " << setw(4) << droga[i] << " | ";
            elscie *p = scierzka[i];
            while (p) {
                cout << setw(4) << p->path << " ";
                p = p->next;
            }
            cout << endl;
        }
    }


// czyszczeine listy ścierzek
    for (int i = 0; i < lwierzch; ++i) {
        elscie *p = scierzka[i];
        elscie *r;
        while (p) {
            r = p;
            p = p->next;
            delete r;
        }

    }
    delete[] scierzka;
    return elapsed;
}


void SPmain::purge() {
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

long long int SPmain::read_QPC() {//pomiar czasu
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int) count.QuadPart);
}






