#include "CAMBULANCE.h"
#include "Console.h"
#include "Utility.h"
#include "Sound.h"

void CAMBULANCE::setToStartingPos() 
{
	setX(5);
	setY(15);
}

void CAMBULANCE::Move(int speed) {
    gotoXYClear(getX(), getY(), Ambulance);
    setX(getX() + speed);
    if (getX() + Ambulance[0].length() >= 150)
        setToStartingPos();
    gotoXY(getX(), getY(), Ambulance);
}

int CAMBULANCE::getWidth() const
{
	return Ambulance[0].length();  
}

int CAMBULANCE::getHeight() const
{
	return Ambulance.size();
}