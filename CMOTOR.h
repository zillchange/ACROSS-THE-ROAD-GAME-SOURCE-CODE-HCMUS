#pragma once
#include "CVEHICLE.h"

class CMOTOR : public CVEHICLE {
public:
	void setToStartingPos();
	void Move(int speed);
	virtual int getWidth() const;
	virtual int getHeight() const;
	virtual void tell(int);
};