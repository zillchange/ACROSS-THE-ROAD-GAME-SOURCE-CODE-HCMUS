#include "CTRUCK.h"
#include "Console.h"
#include "Utility.h"
#include "Sound.h"
void CTRUCK::setToStartingPos() {
	setX(0);
	setY(13);
}

void CTRUCK::Move(int speed) {
	gotoXYClear(getX(), getY(), Truck);
	setX(getX() + speed); 
	if (getX() + Truck[0].length() >= 150)
		setToStartingPos();
	gotoXY(getX(), getY(), Truck);
}

int CTRUCK::getWidth() const
{
	return Truck[0].length();
}

int CTRUCK::getHeight() const
{
	return Truck.size();
}

void CTRUCK::tell(int dirY) {
	if (isHaveIntersection(dirY, dirY + getHeight() - 1, 13, 13 + getHeight() - 1))
		PlaySound(TEXT("truck.wav"), NULL, SND_FILENAME | SND_ASYNC| SND_NOSTOP
		);
}