#pragma once
#include "CPEOPLE.h"
#include "CBIRD.h"
#include "CDINAUSOR.h"
#include "CMOTOR.h"
#include "CTRUCK.h"
#include "CAMBULANCE.h"
#include <thread>
using namespace std;

class CGAME
{
public:
	CGAME();
	~CGAME();
	CPEOPLE& getPeople();
	int getDifficulty() const;
	int getLevel() const;
	int getMotorLimit() const;
	int getBirdLimit() const;
	int getDinLimit() const;
	int getTruckLimit() const;
	CTRUCK* getTruck() const;
	CMOTOR* getMotor() const;
	CDINAUSOR* getDinausor() const;
	CBIRD* getBird() const;

	void loseGame();
	void setLevel(int _level);
	void resetGame(int _difficulty);
	void exitGame(thread*);
	void startGame();
	bool saveGame(const int& slot);
	bool loadGame(const int& slot);
	void pauseGame(HANDLE);
	void remuseGame(HANDLE);
	void updatePosPeople(char direction);
	const int MAX_LEVEL = 9;
	void initMotorWay(CMOTOR motor[]);
	void initBirdWay(CBIRD bird[]);
	void initDinausorWay(CDINAUSOR dinausor[]);
	void initTruckWay(CTRUCK truck[]);

private:
	CTRUCK* truck;
	CMOTOR* motor;
	CDINAUSOR* dinausor;
	CBIRD* bird;
	CPEOPLE cn;
	CAMBULANCE* ambulance;
	int level;
	int difficulty;
	static int motorAmount;
	static int birdAmount;
	static int dinAmount;
	static int truckAmount;

	const int motorLimit = 4;
	const int birdLimit = 2;
	const int dinLimit = 2;
	const int truckLimit = 2;
	const int ambulanceLimit = 1;
};
