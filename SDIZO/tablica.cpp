#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include "tablica.h"

using namespace std;





//funkcje tablicy

void tabmain::init(string nazwa) {//inicjalizacja tablicy poprzez wczytanie z pliku
    if (tablica != NULL) {
        purge();
        char s[]  = {""};

    }

    ifstream file(nazwa.c_str());
    int val;
    if (file.is_open()) {
        file >> rozm;
        if (rozm <= 0) {
            cout << "blad wczytania" << endl;
            system("PAUSE");
            exit(22);
        }
        if (file.fail()) {
            cout << "File error - READ SIZE" << endl;
            system("PAUSE");
            exit(20);
        } else {
            tablica = new int[rozm];
            for (int i = 0; i < rozm; i++) {
                file >> val;
                if (file.fail()) {
                    cout << "File error - READ DATA" << endl;
                    system("PAUSE");
                    exit(20);
                    break;
                } else {
                    tablica[i] = val;
                }
            }
        }
        file.close();
    } else {
        cout << "File error - OPEN" << endl;
        system("PAUSE");
        exit(20);
    }


}

void tabmain::menu() {
    //menu
    int wyb = 0;
    int li, gdz;


    boolean koniec = false;
    while (!koniec) {
        boolean test = testw();
        cout << "Co chcesz Zrobic?" << endl << endl;
        cout << "1-Wyszukaj liczbe" << endl;
        cout << "2-Wprowadz liczbe na poczatek" << endl;
        cout << "3-Wprowadz liczbe na koniec" << endl;
        cout << "4-Wprowadz liczbe w dowolny punkt" << endl;
        cout << "5-Usun liczbe z poczatku" << endl;
        cout << "6-Usun liczbe z konca" << endl;
        cout << "7-Usun liczbe ze srodka" << endl;
        cout << "8-Wyswietl dane" << endl;
        cout << "9-Wroc do MainMenu" << endl;
        cin >> wyb;
        switch (wyb) {
            case 1:
                search();
                break;
            case 2:
                gdz = 0;
                cout << endl << "Jaka liczbe chcesz wstawic?" << endl;
                cin >> li;
                insertp(gdz, li);
                if (test) {
                    show();
                    cout << endl;
                }
                break;
            case 3:
                gdz = rozm;
                cout << endl << "Jaka liczbe chcesz wstawic?" << endl;
                cin >> li;
                insertp(gdz, li);
                if (test) {
                    show();
                    cout << endl;
                }
                break;
            case 4:
                cout << endl << "Jaka liczbe chcesz wstawic?" << endl;
                cin >> li;
                cout << endl << "Gdzie chcesz ja wstawic?" << endl;
                cin >> gdz;
                insertp(gdz, li);
                if (test) {
                    show();
                    cout << endl;
                }
                break;
            case 5:

                gdz = 0;
                usun(gdz);
                if (test) {
                    show();
                    cout << endl;
                }
                break;
            case 6:

                gdz = rozm-1;
                usun(gdz);
                if (test) {
                    show();
                    cout << endl;
                }
                break;
            case 7:

                cout << endl << "Z jakiej pozycji?" << endl;
                cin >> gdz;
                usun(gdz);
                if (test) {
                    show();
                    cout << endl;
                }
                break;
            case 8:
                if (test) {
                    show();
                    cout << endl;
                }
                break;
            case 9:
                koniec = true;
                break;
            default:
                break;

        }
    }

}

void tabmain::show() {
    //wyświetlanie tablicy
    if (rozm<=0){
        cout << endl << "Tablica pusta" << endl;
        return;
    }

    cout << endl << endl;
    for (int i = 0; i < rozm; ++i) {
        cout << tablica[i] << " ";
    }


}

void tabmain::insertp(int pozycja, int co) {

    //wsadzanie elementu na pozycje

    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();

//zmienne
    int mi, n;
    mi = pozycja;
    n = co;
    boolean dobrze = true;
    if (mi < 0 || mi > rozm) {
        cout << endl << "Niewlasciwe miejsce:" << endl;
        dobrze = false;
    }
    if (dobrze) {

        rozm++;

        int *temptab = new int[(rozm)];
        int j = 0;
        for (int i = 0; i < rozm; ++i) {

            if (i == mi) {

                temptab[i] = n;
                i++;
                j++;
            }

            if (i < rozm) {
                temptab[i] = tablica[i - j];

            }

            if (((i + 1) == mi) && mi == (rozm - 1)) { //ostatnia pozycja
                temptab[(rozm - 1)] = n;


                break;
            }

        }
        delete[] tablica;
        tablica = temptab;

    }
    elapsed = read_QPC() - start;
    cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
    cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
    cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;


}

void tabmain::usun(int pozycja) {
// usuwanie

    if (rozm<=0){
        cout << endl << "Tablica pusta" << endl;
        return;
    }
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();


    int *temptab = new int[(rozm)];
    int j = 0;
    int mi = pozycja;
    boolean dobrze = true;
    if (mi < 0 || mi >= rozm) {
        cout << endl << "Niewlasciwe miejsce:" << endl;
        dobrze = false;
    }
    if (dobrze) {
        rozm--;
        temptab = new int[rozm];
        for (int i = 0; i < rozm + 1; ++i) {
            if (i == mi) {
                j++;
            }
            if (i < rozm) {
                temptab[i] = tablica[i + j];
            }


        }
        delete[] tablica;
        tablica = temptab;
    }
    elapsed = read_QPC() - start;
    cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
    cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
    cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;

}

void tabmain::search() {
    //wyszukiwanie
    int liczb;
    cout << endl << "Podaj szukana liczbe:" << endl;
    cin >> liczb;

    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();


    for (int i = 0; i < rozm; ++i) {
        if (tablica[i] == liczb) {
            cout << endl << "Znalezoino liczbe na pozycji: " << i << endl;
            break;
        }
        if (i == (rozm - 1)) {
            cout << endl << "Nie znalezoino liczby" << endl;
        }
    }
    elapsed = read_QPC() - start;
    cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
    cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
    cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
}

boolean tabmain::testw() {// test czy mała struktura
    boolean taknie = true;
    if (rozm > 40) {
        taknie = false;
    }
    return taknie;
}

void tabmain::purge() {
    //czyszczenie pamięci
    delete[] tablica;
    tablica=NULL;

}

long long int tabmain::read_QPC() {//pomiar czasu
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int) count.QuadPart);
}

tabmain::tabmain(string npliku) {//konstruktor
    cout <<endl<< "Tworze tablice" << endl;
    tablica = NULL;
    init(npliku);
}

tabmain::~tabmain() {//destruktor
    cout<<endl << "Niszcze tablice" << endl;
    purge();
}







