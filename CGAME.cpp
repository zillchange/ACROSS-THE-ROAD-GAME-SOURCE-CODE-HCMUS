#include "CGAME.h"
#include "CBIRD.h"
#include "CDINAUSOR.h"
#include "CMOTOR.h"
#include "CTRUCK.h"
#include "Utility.h"
#include "Console.h"

#include <fstream>
#include <sstream>
#include <thread>
#include <conio.h>

int CGAME::motorAmount = 1;
int CGAME::birdAmount = 1;
int CGAME::dinAmount = 1;
int CGAME::truckAmount = 1;

CGAME::CGAME()
{
    truck = new CTRUCK[truckLimit];
    motor = new CMOTOR[motorLimit];
    dinausor = new CDINAUSOR[dinLimit];
    bird = new CBIRD[birdLimit];
    ambulance = new CAMBULANCE[ambulanceLimit];
}

CGAME::~CGAME()
{
    delete[] truck;
    delete[] motor;
    delete[] dinausor;
    delete[] bird;
    delete[] ambulance;
}

CPEOPLE& CGAME::getPeople()
{
    return cn;
}

int CGAME::getDifficulty() const
{
    return difficulty;
}

int CGAME::getLevel() const
{
    return level;
}

int CGAME::getMotorLimit() const
{
    return motorLimit;
}

int CGAME::getBirdLimit() const
{
    return birdLimit;
}

int CGAME::getDinLimit() const
{
    return dinLimit;
}

int CGAME::getTruckLimit() const
{
    return truckLimit;
}

CTRUCK* CGAME::getTruck() const
{
    return truck;
}

CMOTOR* CGAME::getMotor() const
{
    return motor;
}

CDINAUSOR* CGAME::getDinausor() const
{
    return dinausor;
}

CBIRD* CGAME::getBird() const
{
    return bird;
}

void CGAME::loseGame() {
    
    system("cls"); // xóa màn hình
    Sleep(300); // chờ 300ms
    ambulance[0].setToStartingPos(); // set vị trí cho 
    gotoXY(50, 18,cn.getPlayer()); // in vị trí con ng
    int i = 1; 
    while (i < 30) { // để xe di chuyển cán qua người
        ambulance[0].Move(2);
        i++;
        Sleep(30);
    }
}

void CGAME::setLevel(int _level)
{
    if (_level >= 0 && _level <= MAX_LEVEL)
        level = _level;
}

void CGAME::resetGame(int _difficulty)
{
    difficulty = _difficulty;
    level = 0;
}

void CGAME::exitGame(thread* t)
{
    system("cls");
    t->join();
}

void CGAME::startGame()
{
    cn.resetPos();
    system("cls");
    printBorder();
    initDinausorWay(dinausor);
    initBirdWay(bird);
    initTruckWay(truck);
    initMotorWay(motor);
    gotoXY(cn.getX(), cn.getY(), cn.player);
}

bool CGAME::saveGame(const int& slot)
{
    string s[3];
    string time = getTime();
    std::ifstream ifs("save.txt");
    if (ifs.is_open())
    {
        for (int i = 0; i < 3; i++)
        {
            getline(ifs, s[i]);
        }
        ifs.close();
    }

    std::ofstream ofs("save.txt");
    if (ofs.is_open())
    {
        for (int i = 0; i < 3; i++)
        {
            if (i == slot - 1)
                ofs << difficulty << ';' << level << ';' << time;
            else
                ofs << s[i] << '\n';
        }
        ofs.close();
        return true;
    }
    return false;
}

//1; 8; Sun Oct 24 18:56 : 40 2021
//
//2; 3; Sun Oct 24 20:20 : 00 2021

bool CGAME::loadGame(const int& slot)
{
    string s;
    stringstream ss;
    std::ifstream ifs("save.txt");

    if (ifs.is_open())
    {
        for (int i = 0; i < slot; i++)
        {
            getline(ifs, s);
        }
        ss << s;
        ss >> difficulty;
        ss.ignore();
        ss >> level;
        ifs.close();
        return true;
    }
    return false;
}

void CGAME::pauseGame(HANDLE t)
{
    SuspendThread(t);
}

void CGAME::remuseGame(HANDLE t)
{
    ResumeThread(t);
}

void CGAME::updatePosPeople(char direction)
{
    switch (direction)
    {
    case 72:
        cn.Up(2);
        break;
    case 75:
        cn.Left(3);
        break;
    case 77:
        cn.Right(3);
        break;
    case 80:
        cn.Down(2);
        break;
    default:
        break;
    }
}

void CGAME::initMotorWay(CMOTOR motor[])
{
    motorAmount = 1;
    if (motorLimit < 1)
        return;
    else
        motor[0].setToStartingPos();

    for (int i = 0; i <= 15; i++)
    {
        for (int j = 0; j < motorAmount; j++)
        {
            motor[j].Move(2);
        }

        if (i == 15 && motorAmount < motorLimit)
        {
            i = 0;
            motorAmount++;
            motor[motorAmount - 1].setToStartingPos();
        }
        
    }
}

void CGAME::initBirdWay(CBIRD bird[])
{
    birdAmount = 1;
    if (birdLimit < 1)
        return;
    else
        bird[0].setToStartingPos();

    for (int i = 0; i <= 50; i++)
    {
        for (int j = 0; j < birdAmount; j++)
        {
            bird[j].Move(2);
        }

        if (i == 50 && birdAmount < birdLimit)
        {
            i = 0;
            birdAmount++;
            bird[birdAmount - 1].setToStartingPos();
        }
       
    }
}

void CGAME::initDinausorWay(CDINAUSOR dinausor[])
{
    dinAmount = 1;
    if (dinLimit < 1)
        return;
    else
        dinausor[0].setToStartingPos();

    for (int i = 0; i <= 25 ; i++)
    {
        for (int j = 0; j < dinAmount; j++)
        {
            dinausor[j].Move(2);
        }

        if (i == 25 && dinAmount < dinLimit)
        {
            i = 0;
            dinAmount++;
            dinausor[dinAmount - 1].setToStartingPos();
        }
       
    }
}

void CGAME::initTruckWay(CTRUCK truck[])
{
    truckAmount = 1;
    if (truckLimit < 1)
        return;
    else
        truck[0].setToStartingPos();

    for (int i = 0; i <= 30; i++)
    {
        for (int j = 0; j < truckAmount; j++)
        {
            truck[j].Move(2);
        }

        if (i == 30 && truckAmount < truckLimit)
        {
            i = 0;
            truckAmount++;
            truck[dinAmount - 1].setToStartingPos();
        }
       
    }
}

