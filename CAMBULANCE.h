#pragma once
#include "CVEHICLE.h"

class CAMBULANCE : public CVEHICLE {
public:
	void setToStartingPos();
	void Move(int speed);
	virtual int getWidth() const;
	virtual int getHeight() const;
};