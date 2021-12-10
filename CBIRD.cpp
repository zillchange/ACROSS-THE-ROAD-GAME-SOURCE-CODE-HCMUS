#include "CBIRD.h"
#include "Sound.h"
#include "Utility.h"
#include "Console.h"

void CBIRD::setToStartingPos() {
	setX(115);
	setY(20);
}

void CBIRD::Move(int speed) {
	gotoXYClear(getX(), getY(), Bird);
	setX(getX() - speed);
	if (getX() + Bird[0].length() <= 4)
		setToStartingPos();
	gotoXY(getX(), getY(), Bird);
}

int CBIRD::getWidth() const
{
	return Bird[0].length();
}

int CBIRD::getHeight() const
{
	return Bird.size();
}
void CBIRD::tell(int dirY) {
	//isHaveIntersection(mX, mX + width - 1, objX, objX + objwidth - 1)
	if (isHaveIntersection(dirY, dirY + getHeight() - 1, 20, 20 + getHeight() - 1))
		PlaySound(TEXT("animal.wav"), NULL, SND_FILENAME | SND_ASYNC| SND_NOSTOP
		);
}