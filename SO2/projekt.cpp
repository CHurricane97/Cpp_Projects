
#include <ncurses.h>
#include <unistd.h>
#include <list>
#include <vector>
#include <thread>
#include <random>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <string>

using namespace std;

#define BLUE_PAIR 1
#define CYAN_PAIR 2
#define GREEN_PAIR 3
#define MAGENTA_PAIR 4
#define RED_PAIR 5
#define WHITE_PAIR 6
#define YELLOW_PAIR 7
#define GRAY_PAIR 8

int sizey = 45;
int sizex = 180;

bool blocked = false;
chrono::steady_clock::time_point beginProgram;
chrono::steady_clock::time_point prostokatStopTime;
chrono::duration<double> czasBezruchu;

int rectanglewidth = 20;
int rectangleheight = 5;
bool koniec = false;
double procCzasBezruchu = 0;
condition_variable cond;
condition_variable tim;
mutex m1;

// 2 etap
//  Jak kulka uderzy w prostokąt to w nim grzęźnie i prostokąt stoi a jak druga uderzy to uwalnia pierwszą i prostokąt
//

// 3 etap
// Liczyć procentowy czas bezruchu prostokąta od początku działania programu i modyfikować go co 10 sekund.
//

// szary obszar

struct rectangle
{

    int posy = 5;
    int posx = 1;
    int posx2 = 20;
    int sleepx = 50'000;
    int widh = 20;
    int height = 5;
    int color = 8;
    char ch = 'O';
};
// piłka
struct ball
{
    int posy = 40;
    int posx = 50;
    int sleepx = 150'000;
    int sleepy = 150'000;
    bool active = true;
    bool rightLeft = true;
    bool upDown = true;
    bool insideRectangle = false;
    int bounces = 0;
    char ch = 'X';
    int color = 4;
};
ball *blockedBall = NULL;
rectangle r;
list<ball> BALL_INFO_LIST;

// wyswietlanie ramki boiska
void drawField()
{

    for (int i = 0; i < sizey; i++)
    {
        for (int j = 0; j < sizex; j++)
        {
            if (i == 0 || i == sizey - 1 || j == 0 || j == sizex - 1)
            {
                mvaddch(i, j, '#');
            }
        }
    }
}

void aktualizujCzasBezruchu() // aktualizacja czasu bezruchu
{
    while (!koniec)
    {
        if (!blocked)
        {
            unique_lock<mutex> tl(m1);
            tim.wait(tl, []
                     { return (blocked || koniec); });
        }

        prostokatStopTime = chrono::steady_clock::now();

        if (blocked)
        {
            unique_lock<mutex> tl(m1);
            tim.wait(tl, []
                     { return !blocked; });
        }

        czasBezruchu += chrono::steady_clock::now() - prostokatStopTime;
    }
    return;
}

void aktualizujProcentowyCzasBezruchu() // aktualizacja procentowego czasu bezruchu do wyświetlenia
{
    chrono::duration<double> czas;

    while (!koniec)
    {
        if (blocked)
        {
            procCzasBezruchu = ((czasBezruchu + (chrono::steady_clock::now() - prostokatStopTime)) / (chrono::steady_clock::now() - beginProgram)) * 100;
        }
        else
        {
            procCzasBezruchu = ((czasBezruchu) / (chrono::steady_clock::now() - beginProgram)) * 100;
        }

        sleep(10);
    }
    return;
}

// wyswietlanie
void drawBalls()
{
    mvprintw(sizey + 2, sizex / 2, "Wcisnij \"q\" zeby wyjsc");
    mvprintw(13, 181, "Czas Bezruchu");
    mvprintw(14, 181, "Prostokata [%]");
    for (int i = 15; i < 22; i++)
    {
        for (int j = 181; j < 197; j++)
        {
            if (i == 15 || i == 21 || j == 181 || j == 196)
            {
                mvaddch(i, j, '#');
            }
        }
    }

    list<vector<int>> list1;
    rectangle dr = r;

    nodelay(stdscr, TRUE);
    int ch;

    while (true)
    {

        if ((ch = getch()) == ERR)
        {

            drawField();
            // zamazywanie ostatniej pozycji piłki
            while (!list1.empty())
            {
                vector<int> v = list1.front();
                list1.pop_front();
                mvaddch(v[0], v[1], ' ');
            }

            // zamazanie prostokąta
            for (int i = 0; i < dr.height; i++)
            {
                for (int j = 0; j < dr.widh; j++)
                {
                    if (dr.posx + j >= 1)
                    {
                        mvaddch(dr.posy + i, dr.posx + j, ' ');
                    }
                }
            }
            // rysowanie prostokąta
            dr = r;
            attron(COLOR_PAIR(dr.color));

            for (int i = 0; i < dr.height; i++)
            {
                for (int j = 0; j < dr.widh; j++)
                {
                    if (dr.posx + j >= 1)
                    {
                        mvaddch(dr.posy + i, dr.posx + j, dr.ch);
                    }
                }
            }

            attroff(COLOR_PAIR(dr.color));
            // rysowanie piłek
            auto it = BALL_INFO_LIST.begin();
            for (auto it = BALL_INFO_LIST.begin(); it != BALL_INFO_LIST.end(); it++)
            {
                ball b = (*it);
                if (b.active)
                {
                    attron(COLOR_PAIR(b.color));
                    mvaddch(b.posy, b.posx, b.ch);
                    attroff(COLOR_PAIR(b.color));
                    list1.push_back({b.posy, b.posx});
                }
                else
                {
                    it = BALL_INFO_LIST.erase(it--);
                }
            }

            mvprintw(17, 183, "      ");
            string s = to_string(procCzasBezruchu);
            mvprintw(17, 183, s.c_str());
            refresh();

            usleep(1'000);
        }
        else if (ch == 'q')
        { // kończenie
            m1.lock();
            koniec = true;
            m1.unlock();
            blocked = false;
            blockedBall = NULL;
            cond.notify_all();
            tim.notify_all();
            return;
        }
    }
    return;
}

// generator losowy
int numberWhole(int min, int max)
{
    int wyb = rand() % max + min;
    return wyb;
}

// przemieszczanie szarego obszaru

void moveRectangle(rectangle *r)
{

    while (!koniec)
    {
        while (((*r).posx2 + 2 <= sizex - 1) && !koniec)
        {
            if (blocked)
            {
                unique_lock<mutex> rl(m1);
                cond.wait(rl, []
                          { return !blocked; });
            }

            (*r).posx++;
            (*r).posx2++;
            usleep((*r).sleepx);
        }
        (*r).sleepx = numberWhole(30'000, 150'000);
        (*r).posx = sizex - 21;
        (*r).posx2 = sizex - 2;
        while (((*r).posx > 1) && !koniec)
        {
            if (blocked)
            {
                unique_lock<mutex> rl(m1);
                cond.wait(rl, []
                          { return !blocked; });
            }
            (*r).posx--;
            (*r).posx2--;
            usleep((*r).sleepx);
        }
        (*r).sleepx = numberWhole(30'000, 150'000);
        (*r).posx = 1;
        (*r).posx2 = 20;
    }
    return;
}
// kolizja z prostokątem
void colisionWithRectangle(ball *b)
{

    if (blockedBall == NULL)
    {
        if (!koniec)
        {
            blocked = true;   // blokowanie prostokąta
            tim.notify_all(); // notyfikowanie czasomierza bezruchu prostokąta
            blockedBall = b;  // blokowanie piłki
        }
    }
}

// przemieszczanie piłki prawo/lewo
void moveBallRightLeft(ball *b)
{
    while (!koniec)
    {
        // sprawdzanie czy już nie jest w prostoką
        if (!(*b).insideRectangle)
        {
            if ((*b).posy >= 5 && (*b).posy < 10)
            {
                if ((*b).posx >= r.posx && (*b).posx <= r.posx + 19)
                {
                    (*b).insideRectangle = true; // ustawienie że piłka w prostokącie

                    unique_lock<mutex> bl(m1);
                    colisionWithRectangle(b);
                    cond.wait(bl, [&]
                              { return (blockedBall != b) ? true : false; }); // zatrzymanie piłki jezeli jest ona piłką zablokowaną
                    if (blockedBall != NULL)                                  // jeżeli jakaś piłka zablokowana
                    {
                        blockedBall = NULL; // zwalnianie piłki
                        blocked = false;    // zwalnianie prostokąta
                        tim.notify_all();   // notyfikowanie czasomierza bezruchu prostokąta
                        cond.notify_all();  // powiadomienie wszystkich
                    }
                }
            }
        }
        else
        {
            if (b == blockedBall) // zabezpieczenie dla drugiego wątku
            {
                unique_lock<mutex> bl(m1);
                cond.wait(bl, [&]
                          { return (blockedBall != b) ? true : false; });
            }
            if ((*b).posy < 5 || (*b).posy >= 10 || (*b).posx < r.posx || (*b).posx > r.posx + 19)
            {
                (*b).insideRectangle = false;
            }
        }

        if ((*b).rightLeft)
        {
            (*b).posx++;
            if ((*b).posx >= sizex - 2)
            {
                (*b).rightLeft = false;
                (*b).bounces++;
            }
        }
        else
        {
            (*b).posx--;
            if ((*b).posx <= 1)
            {
                (*b).rightLeft = true;
                (*b).bounces++;
            }
        }

        usleep((*b).sleepx);

        if ((*b).bounces == 6)
        {

            (*b).active = false;
            return;
        }
    }
    return;
}
// przemieszczanie piłki góra/dół
void moveBallUpDown(ball *b)
{
    while (!koniec)
    {
        // sprawdzanie czy już nie jest w prostoką
        if (!(*b).insideRectangle)
        {
            if ((*b).posy >= 5 && (*b).posy < 10)
            {
                if ((*b).posx >= r.posx && (*b).posx <= r.posx + 19)
                {
                    (*b).insideRectangle = true; // ustawienie że piłka w prostokącie

                    unique_lock<mutex> bl(m1);
                    colisionWithRectangle(b);
                    cond.wait(bl, [&]
                              { return (blockedBall != b) ? true : false; }); // zatrzymanie piłki jezeli jest ona piłką zablokowaną
                    if (blockedBall != NULL)                                  // jeżeli jakaś piłka zablokowana
                    {
                        blockedBall = NULL; // zwalnianie piłki
                        blocked = false;    // zwalnianie prostokąta
                        tim.notify_all();
                        cond.notify_all(); // powiadomienie wszystkich
                    }
                }
            }
        }
        else
        {
            if (b == blockedBall) // zabezpieczenie dla drugiego wątku
            {
                unique_lock<mutex> bl(m1);
                cond.wait(bl, [&]
                          { return (blockedBall != b) ? true : false; });
            }
            if ((*b).posy < 5 || (*b).posy >= 10 || (*b).posx < r.posx || (*b).posx > r.posx + 19)
            {
                (*b).insideRectangle = false;
            }
        }

        if ((*b).upDown)
        {
            (*b).posy--;
            if ((*b).posy <= 1)
            {
                (*b).upDown = false;
                (*b).bounces++;
            }
        }
        else
        {
            (*b).posy++;
            if ((*b).posy >= sizey - 2)
            {
                (*b).upDown = true;
                (*b).bounces++;
            }
        }

        usleep((*b).sleepy);
        if ((*b).bounces == 6)
        {
            (*b).active = false;
            return;
        }
    }
    return;
}

int main()
{
    beginProgram = chrono::steady_clock::now();
    czasBezruchu = beginProgram - beginProgram;
    srand(time(NULL));
    initscr();
    start_color();
    init_pair(BLUE_PAIR, COLOR_BLUE, COLOR_BLACK);
    init_pair(CYAN_PAIR, COLOR_CYAN, COLOR_BLACK);
    init_pair(GREEN_PAIR, COLOR_GREEN, COLOR_BLACK);
    init_pair(MAGENTA_PAIR, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(RED_PAIR, COLOR_RED, COLOR_BLACK);
    init_pair(WHITE_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(YELLOW_PAIR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(GRAY_PAIR, 8, COLOR_BLACK);

    drawField();
    refresh();

    list<thread> threadList;
    thread RectangleThread(move(thread(moveRectangle, &(r))));
    thread printBallsThread(drawBalls);
    thread czasomierz(aktualizujCzasBezruchu);
    thread wyswietlCzas(aktualizujProcentowyCzasBezruchu);

    curs_set(0);
    // tworzenie piłek
    while (!koniec)
    {

        ball b;

        b.posy = sizey - 3;

        b.posx = numberWhole(5, sizex - 5);
        b.sleepx = numberWhole(30'000, 35'000);
        b.sleepy = numberWhole(50'000, 100'000);

        if (b.posx > sizex / 2)
        {
            b.rightLeft = true;
        }
        else
        {
            b.rightLeft = false;
        }

        b.upDown = true;

        b.color = numberWhole(1, 7);

        BALL_INFO_LIST.push_back(b);

        threadList.push_back(move(thread(moveBallUpDown, &(BALL_INFO_LIST.back()))));
        threadList.push_back(move(thread(moveBallRightLeft, &(BALL_INFO_LIST.back()))));

        sleep(numberWhole(1, 5));
    }

    printBallsThread.join();

    RectangleThread.join();

    czasomierz.join();
    wyswietlCzas.join();

    while (!threadList.empty())
    {
        threadList.front().join();
        threadList.pop_front();
    }

    endwin();

    return 0;
}