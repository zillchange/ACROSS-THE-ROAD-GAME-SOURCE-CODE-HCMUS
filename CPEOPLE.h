#pragma once
#include "console.h"
#include "CANIMAL.h"
#include "CVEHICLE.h"

#include <vector>
#include <string>
using namespace std;

class CPEOPLE
{
public:
	CPEOPLE();
	void resetPos();
	void Up(int step);
	void Left(int step);
	void Right(int step);
	void Down(int step);
	int getX() const;
	int getY() const;
	bool isImpact(CVEHICLE* vehicle, int sumVehicle);
	bool isImpact(CANIMAL* animal, int sumAnimal);
	bool isFinish();
	bool isDead();
	static vector <string> player;

	vector<string> getPlayer();
	void tell();
private:
	int mX, mY, height, width;
	bool mState;
};