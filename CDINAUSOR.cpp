#include "CDINAUSOR.h"
#include "Console.h"
#include "Utility.h"
#include"Sound.h"
void CDINAUSOR::setToStartingPos() {
	setX(0);
	setY(26);
}

void CDINAUSOR::Move(int speed) {
	gotoXYClear(getX(), getY(), Din);
	setX(getX() + speed);
	if (getX() + Din[0].size() >= 112)
		setToStartingPos();
	gotoXY(getX(), getY(), Din);
}

int CDINAUSOR::getWidth() const
{
	return Din[0].length();
}

int CDINAUSOR::getHeight() const
{
	return Din.size();
}
void CDINAUSOR::tell(int dirY) {
	if (isHaveIntersection(dirY, dirY + getHeight() - 1, 26, 26 + getHeight() - 1))
		PlaySound(TEXT("trex.wav"), NULL, SND_FILENAME | SND_ASYNC| SND_NOSTOP
		);
		/*if (dirY <= 28 && dirY >= 24)*/
			

	
}