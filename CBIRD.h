#pragma once
#include "CANIMAL.h"

class CBIRD : public CANIMAL {
public:
	void setToStartingPos();
	virtual void Move(int speed);
	virtual int getWidth() const;
	virtual int getHeight() const;
	virtual void tell(int);
};