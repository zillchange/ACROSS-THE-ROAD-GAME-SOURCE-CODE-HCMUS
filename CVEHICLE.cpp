#include "CVEHICLE.h"

CVEHICLE::CVEHICLE() : x(0), y(0) {}

int CVEHICLE::getX() const
{
	return x;
}

int CVEHICLE::getY() const
{
	return y;
}

void CVEHICLE::setX(int _x)
{
	x = _x;
}

void CVEHICLE::setY(int _y)
{
	y = _y;
}

vector<string> CVEHICLE::Truck = {
	"!____-   =_==   ",
	"|__\\___|/    |  ",
	"|  _     _    `.",
	"'-(_)----(_)---'"
};

vector<string> CVEHICLE::Motor = {
	"   ,_o   " ,
	".-/c-/,::",
	"(_)'==(_)"
};

vector<string> CVEHICLE::Ambulance = {
	" _____________           " ,
	"|       _     |          ",
	"|     _| |_   |__________",
	"|    |_   _|  |    |     |",
	"|      |_|    |    |_____|",
	"|_____________|__________|",
	"   (O)               (O)"
};
