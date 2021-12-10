#include "CPEOPLE.h"
#include "Sound.h"
#include "Utility.h"

vector <std::string> CPEOPLE::player = {
		" o ",
		"/I\\",
		"/ \\"
};

vector<std::string> CPEOPLE::getPlayer() {
	return player;
}
																			
CPEOPLE::CPEOPLE() : mX(WIDTH / 2 - 1), mY(HEIGHT - 7), mState(true), height(3), width(3) {}


void CPEOPLE::resetPos()
{
	gotoXYClear(mX, mY, player);
	mX = WIDTH / 2 - 1;
	mY = HEIGHT - 7;
	mState = true;
}

void CPEOPLE::Up(int step)
{
	while (step)
	{
		if (this->mY - step >= 4) //
		{
			gotoXYClear(this->mX, this->mY, player);
			this->mY -= step;
			gotoXY(mX, mY, player);
			return;
		}
		step--;
	}
}

void CPEOPLE::Left(int step)
{
	while (step)
	{
		if (this->mX - step >= 5)
		{
			gotoXYClear(this->mX, this->mY, player);
			this->mX -= step;
			gotoXY(mX, mY, player);
			return;
		}
		step--;
	}
}

void CPEOPLE::Right(int step)
{
	while (step)
	{
		if (this->mX + step <= WIDTH - 8)
		{
			gotoXYClear(this->mX, this->mY, player);
			this->mX += step;
			gotoXY(mX, mY, player);
			return;
		}
		step--;
	}
}

void CPEOPLE::Down(int step)
{
	while (step)
	{
		if (this->mY + step <= HEIGHT - 7)
		{
			gotoXYClear(this->mX, this->mY, player);
			this->mY += step;
			gotoXY(mX, mY, player);
			return;
		}
		step--;
	}
}

int CPEOPLE::getX() const
{
	return mX;
}

int CPEOPLE::getY() const
{
	return mY;
}

//
bool CPEOPLE::isImpact(CVEHICLE* vehicle, int sumVehicle)
{
	int objX, objY, objwidth, objHeight;
	for (int i = 0; i < sumVehicle; i++)
	{
		objX = vehicle[i].getX();
		objY = vehicle[i].getY();
		objwidth = vehicle[i].getWidth();
		objHeight = vehicle[i].getHeight();

		if (isHaveIntersection(mX, mX + width - 1, objX, objX + objwidth - 1) &&
			isHaveIntersection(mY, mY + width - 1, objY, objY + objHeight - 1))
		{
			mState = false;
			return true;
		}
	}
	return false;
}

bool CPEOPLE::isImpact(CANIMAL* animal, int sumAnimal)
{
	int objX, objY, objwidth, objHeight;
	for (int i = 0; i < sumAnimal; i++)
	{
		objX = animal[i].getX();
		objY = animal[i].getY();
		objwidth = animal[i].getWidth();
		objHeight = animal[i].getHeight();

		if (isHaveIntersection(mX, mX + width - 1, objX, objX + objwidth - 1) &&
			isHaveIntersection(mY, mY + height - 1, objY, objY + objHeight - 1))
		{
			mState = false;
			return true;
		}
	}
	return false;
}


bool CPEOPLE::isFinish()
{
	return mY == 4 ? true : false;
}

//
bool CPEOPLE::isDead()
{
	return !mState;
}

//phát ra tiếng khi va chạm
void CPEOPLE::tell() {
		PlaySound(TEXT("scream.wav"), NULL, SND_FILENAME | SND_ASYNC);
}