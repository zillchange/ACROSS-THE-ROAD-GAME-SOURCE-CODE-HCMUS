#include "CMOTOR.h"
#include "Console.h"
#include "Utility.h"
#include "Sound.h"
void CMOTOR::setToStartingPos() {
	setX(115);
	setY(6);
}

void CMOTOR::Move(int speed) {
	gotoXYClear(getX(), getY(), Motor);
	setX(getX() - speed);
	if (getX() + Motor[0].length() <= 4)
		setToStartingPos();
	gotoXY(getX(), getY(), Motor);
}

int CMOTOR::getWidth() const
{
	return Motor[0].length();
}

int CMOTOR::getHeight() const
{
	return Motor.size();
}
void CMOTOR::tell(int dirY) {
	if (isHaveIntersection(dirY, dirY + getHeight() - 1, 6, 6 + getHeight() - 1))
		PlaySound(TEXT("motor.wav"), NULL, SND_FILENAME | SND_ASYNC| SND_NOSTOP
		);
}