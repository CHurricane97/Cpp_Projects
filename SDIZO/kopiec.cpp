#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include "kopiec.h"

using namespace std;



//funkcje kopca
void kopmain::init(string nazwa) {//inicjalizacja kopca poprzez wczytanie z pliku
    if (tablica != NULL) {
        purge();
    }

    ifstream file(nazwa.c_str());
    int val;
    if (file.is_open()) {
        file >> rozm;
        if (rozm<=0){
            cout<<"blad wczytania"<<endl;
            exit(22);
        }
        if (file.fail()) {
            cout << "File error - READ SIZE" << endl;
            exit(20);
        } else {
            tablica = new int[rozm];
            for (int i = 0; i < rozm; i++) {
                file >> val;
                if (file.fail()) {
                    cout << "File error - READ DATA" << endl;
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
        exit(20);
    }

    heapcreate();//naprawa kopca
}

void kopmain::heap(int inde) {
    // funkcja wewnętrzna do naprawy kopca
    int wieksze = inde;
    int l = 2 * inde + 1;
    int r = l + 1;
    if (l < rozm && tablica[l] > tablica[wieksze])
        wieksze = l;

    if (r < rozm && tablica[r] > tablica[wieksze])
        wieksze = r;

    if (wieksze != inde) {
        int temppp = tablica[inde];
        tablica[inde] = tablica[wieksze];
        tablica[wieksze] = temppp;

        heap(wieksze);
    }
}

void kopmain::heapcreate() {
    int ind = (rozm / 2) - 1;
    for (int i = ind; i >= 0; i--) {// naprawa kopca
        heap(i);
    }
}

void kopmain::menu() {
    //menu
    int wyb = 0;
    int li, gdz;
    boolean koniec = false;
    while (!koniec) {
        boolean test=testw();
        cout << "Co chcesz Zrobic?" << endl << endl;
        cout << "1-Wyszukaj liczbe" << endl;
        cout << "2-Wprowadz liczbe" << endl;
        cout << "3-Usun liczbe" << endl;
        cout << "4-Wyswietl dane" << endl;
        cout << "5-Wroc do MainMenu" << endl;
        cin >> wyb;
        switch (wyb) {
            case 1:
                search();
                break;
            case 2:
                cout << endl << "Jaka liczbe chcesz wstawic?" << endl;
                cin >> li;
                insertp(li);
                if (test) {
                    show();
                    cout<<endl;
                }
                break;
            case 3:
                usun();
                if (test) {
                    show();
                    cout<<endl;
                }
                break;
            case 4:
                if (test) {
                    show();
                    cout<<endl;
                }
                break;
            case 5:
                koniec = true;
                break;
            default:
                break;

        }
    }
}

void kopmain::show() {
    // wyświetlanie kopca
    cout << endl << endl;
    for (int i = 0; i < rozm; ++i) {

        if ((i==1)||(i==3)||(i==7)||(i==15)||(i==31)){
            cout << endl;
        }
        cout << tablica[i] << " ";

    }

}

void kopmain::insertp(int co) {
    //wsadzanie elementu

    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();


    int *temptab = new int[(rozm + 1)];
    for (int i = 0; i < rozm; ++i) {
        temptab[i] = tablica[i];
    }
    temptab[rozm] = co;
    delete[] tablica;
    tablica = temptab;
    rozm++;
    repairup();//nprawa kopca

    elapsed = read_QPC() - start;
    cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
    cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
    cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;

}

void kopmain::usun() {
//usuwanie elementu
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();


    if (rozm > 0) {
        int *temptab = new int[(rozm - 1)];
        int temppp = tablica[0];
        tablica[0] = tablica[rozm - 1];
        tablica[rozm - 1] = temppp;
        rozm--;
        for (int i = 0; i < rozm; ++i) {
            temptab[i] = tablica[i];
        }
        delete[] tablica;
        tablica = temptab;
        repairdown();
    }
    elapsed = read_QPC() - start;
    cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
    cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
    cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;

}

void kopmain::search() {
    //wyszukiwanie elementu
    int liczb;
    cout << endl << "Podaj szukana liczbe:" << endl;
    cin >> liczb;
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();

    if (tablica[0]<liczb){
        cout<<endl<<"Nie znaleziono liczby"<<endl;
    }else{
        int ind = (rozm / 2) - 1;//ostatni rodzic

        for (int i = 0; i <= ind; i++) {
            int l = 2 * i + 1;
            int r = l + 1;
            if (tablica[i]>=liczb){

                if (tablica[i]==liczb){
                    cout<<endl<<"Znaleziono liczbe na pozycji: "<<i<<endl;
                    break;
                }
                if (l>ind){//sprawdzanie liści

                    if (l < rozm){
                        if (tablica[l]==liczb){
                            cout<<endl<<"Znaleziono liczbe na pozycji: "<<l<<endl;
                            break;
                        }
                    }


                    if (r < rozm){
                        if (tablica[r]==liczb){
                            cout<<endl<<"Znaleziono liczbe na pozycji: "<<r<<endl;
                            break;
                        }
                    }

                }

            }

            if (i==ind){
                cout<<endl<<"Nie znaleziono liczby"<<endl;
            }

        }
    }


    elapsed = read_QPC() - start;
    cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
    cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
    cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
}

boolean kopmain::testw() {// test czy mała struktura
    boolean taknie= true;
    if (rozm>40){
        taknie= false;
    }
    return taknie;
}

void kopmain::purge() {
//czyszczenie pamięci
    delete[] tablica;
}

long long int kopmain::read_QPC() {
    //pomiar czasu
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int) count.QuadPart);
}

kopmain::kopmain(string npliku) {//konstruktor
    cout <<endl<< "Tworze kopiec" << endl;
    tablica = NULL;
    init(npliku);
}

kopmain::~kopmain() {//destruktor
    cout<<endl << "Niszcze kopiec" << endl;
    purge();
}

void kopmain::repairup() {//napraw w gore
    if (rozm<=1){return;}//jesli pusty kopiec albo 1 element
    int parentt = (rozm / 2) - 1;
    boolean k= false;
    while (!k){
        heap(parentt);

        if (parentt==0){
            k=true;
        }
        parentt=((parentt-1)/2);

    }

}

void kopmain::repairdown() {//napraw w dol
heap(0);
}
