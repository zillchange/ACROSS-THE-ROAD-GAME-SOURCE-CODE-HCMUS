#include "CANIMAL.h"

CANIMAL::CANIMAL() : x(0), y(0) {}

int CANIMAL::getX() const
{
	return x;
}

int CANIMAL::getY() const
{
	return y;
}

void CANIMAL::setX(int _x)
{
	x = _x;
}

void CANIMAL::setY(int _y)
{
	y = _y;
}


vector<string> CANIMAL::Din = {
	"                 __       ",
	"  ``````````    / .)      ",
	"   ````````--._/ /\11`---9  ",
	"      / ```     / \11`--9   ",
	"  __ / (|    ( |  \11`-9    ",
	" /___.-'|_|--|_|          "
};

vector<string> CANIMAL::Bird = {
	"  _      _      _   ",
	">(.)__ <(.)__ =(.)__",
	" (___/  (___/  (___/"
};
