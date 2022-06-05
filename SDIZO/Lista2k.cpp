#include<windows.h>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include "Lista2k.h"


using namespace std;


//funkcje list
void listmain::init(string nazwa) {//inicjalizacja listy poprzez wczytanie z pliku
    if (head!=NULL){
        purge();
    }


    ifstream file(nazwa.c_str());
    int val;
    head = NULL;
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
            for (int i = 0; i < rozm; i++) {
                file >> val;
                if (file.fail()) {
                    cout << "File error - READ DATA" << endl;
                    system("PAUSE");
                    exit(20);

                } else {
                    insertk(val, true);
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

void listmain::menu() {
//menu
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);

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
                insertp(li);
                if (test) {
                    show();
                    cout << endl;
                }
                break;
            case 3:
                gdz = rozm;
                cout << endl << "Jaka liczbe chcesz wstawic?" << endl;
                cin >> li;
                insertk(li, false);
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


                inserts(gdz, li);


                if (test) {
                    show();
                    cout << endl;
                }
                break;
            case 5:
                start = read_QPC();

                gdz = 0;
                usun(gdz);
                elapsed = read_QPC() - start;
                cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
                cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
                if (test) {
                    show();
                    cout << endl;
                }
                break;
            case 6:
                gdz = (rozm - 1);
                start = read_QPC();
                usun(gdz);
                elapsed = read_QPC() - start;
                cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
                cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
                if (test) {
                    show();
                    cout << endl;
                }
                break;
            case 7:
                cout << endl << "Z jakiej pozycji?" << endl;
                cin >> gdz;
                start = read_QPC();
                usun(gdz);
                elapsed = read_QPC() - start;
                cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
                cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
                cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
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

void listmain::show() {
    // wyświetlanie listu
    ellisty *temp = head;
    printf("\nOd Poczatku: \n");
    while (temp != NULL) {
        printf("%d ", temp->liczba);
        temp = temp->next;
    }
    printf("\n\n\n");

    temp = head;
    if (temp == NULL) return;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    printf("Od tylu: \n");
    while (temp != NULL) {
        printf("%d ", temp->liczba);
        if (temp)
            temp = temp->prev;
    }
    printf("\n");
}

void listmain::insertp(int co) {
    //wsadzenie elementu na początek
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    start = read_QPC();


    ellisty *newNode = GetNewel(co);
    if (head == NULL) {
        head = newNode;
        tail = head;
        rozm++;
        return;
    }
    head->prev = newNode;
    newNode->next = head;
    head = newNode;
    rozm++;


    elapsed = read_QPC() - start;
    cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
    cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
    cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;

}

void listmain::insertk(int co, boolean inic) {
    //wsadzenie elementu na koniec
    ellisty *temp = head;
    ellisty *newNode = GetNewel(co);

    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);


    if (!inic) {
        rozm++;
        start = read_QPC();
    }


    if (head == NULL) {
        head = newNode;
        tail = head;
        if (!inic) { rozm++; }
        return;
    }

    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;

    if (!inic) {
        elapsed = read_QPC() - start;
        cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
        cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
        cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
    }

}

void listmain::inserts(int gdz, int co) {
    //wsadzenie elementu na środek
    boolean dobrze = true;


    if (gdz < 0 || gdz > rozm) {
        cout << endl << "Niewlasciwe miejsce:" << endl;
        dobrze = false;
    }
    if (dobrze) {//przypadki skrajne
        ellisty *temp = head;
        if (gdz == 0) {
            insertp(co);
            return;
        }
        if (gdz == (rozm)) {
            insertk(co, false);
            return;
        }

        long long int frequency, start, elapsed;
        QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
        start = read_QPC();

        for (int j = 0; j < (gdz - 1); ++j) {
            temp = temp->next; //element n-1
        }
        ellisty *temp2 = temp->next; //n element
        ellisty *temp3 = GetNewel(co);
        temp->next = temp3;
        temp3->prev = temp;
        temp2->prev = temp3;
        temp3->next = temp2;
        rozm++;

        elapsed = read_QPC() - start;
        cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
        cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
        cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;


    }


}

void listmain::usun(int pozycja) {
    //usuwanie elementu
    boolean dobrze = true;
    if (head==NULL){
        cout << endl << "Lista pusta:" << endl;
        return;
    }

    if (pozycja < 0 || pozycja >= rozm) {
        cout << endl << "Niewlasciwe miejsce:" << endl;
        dobrze = false;
    }
    if (dobrze) {


        ellisty *temp = head;//z początku
        if (pozycja == 0) {

            if (rozm>1){
                head = temp->next;
                delete temp;
                head->prev = NULL;
                rozm--;
                return;
            } else{//1 element
                delete head;
                head=NULL;
                tail=NULL;
                rozm--;
                return;
            }

        }
        if (pozycja == (rozm - 1)) {//z końca
            if (rozm>1){
                temp = tail;
                tail = temp->prev;
                tail->next = NULL;
                delete temp;
                rozm--;
                return;
            } else{//1 element
                delete head;
                head=NULL;
                tail=NULL;
                rozm--;
                return;
            }
        }


        for (int j = 0; j < (pozycja - 1); ++j) {
            temp = temp->next; //element n-1
        }
        ellisty *temp2 = temp->next; //n element
        temp->next = temp2->next;
        ellisty *temp3 = temp2->next; //n+1 element
        temp3->prev = temp;
        delete temp2;
        rozm--;


    }


}


boolean listmain::testw() {// test czy mała struktura
    boolean taknie = true;
    if (rozm > 40) {
        taknie = false;
    }
    return taknie;
}

ellisty *listmain::GetNewel(int x) {
    ellisty *newNode = new ellisty();
    newNode->liczba = x;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void listmain::search() {
    //wyszukiwanie
    boolean dobrze = true;
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);

    if (head == NULL) {
        cout << endl << "Pusta lista:" << endl;
        dobrze = false;
    }
    if (dobrze) {
        int liczb;
        cout << endl << "Podaj szukana liczbe:" << endl;
        cin >> liczb;

        start = read_QPC();

        ellisty *temp = head;
        for (int i = 0; i < rozm; ++i) {


            if (temp->liczba == liczb) {
                cout << endl << "Znaleziono liczbe na pozycji: " << i << endl;
                break;
            }

            if (i == (rozm - 1)) {
                cout << endl << "Nie znalezoino liczby" << endl;
            }
            temp = temp->next;
        }
    }
    elapsed = read_QPC() - start;
    cout << "Time [s]  = " << fixed << setprecision(3) << (float) elapsed / frequency << endl;
    cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
    cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) / frequency << endl << endl;
}

void listmain::purge() {
//czyszczenie pamięci
    ellisty *temp = head;
    if (temp == NULL) {
        cout << endl << "Pusta Lsta" << endl;
        return;
    }
    while (temp != NULL) {
        ellisty *temp2 = temp->next;
        delete temp;
        temp = temp2;
    }
    rozm = 0;
    head = NULL;
    tail = NULL;

}

long long int listmain::read_QPC() {
    //pomiar czasu
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int) count.QuadPart);
}

listmain::listmain(string npliku) {//konstruktor
    cout <<endl<< "Tworze liste" << endl;
    head = NULL;
    tail=NULL;
    init(npliku);
}

listmain::~listmain() {// destruktor
    cout << endl<< "Niszcze liste" << endl;
    purge();
}



