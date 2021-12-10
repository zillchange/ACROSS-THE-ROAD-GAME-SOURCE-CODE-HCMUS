#pragma once
#include <vector>
#include <string>
using namespace std;

class CANIMAL {
private:
	int x, y;
public:
	CANIMAL();
	static vector<string> Din;
	static vector<string> Bird;

	virtual void Move(int speed) = 0;
	
	int getX() const;
	int getY() const;
	void setX(int _x);
	void setY(int _y);

	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;

	
};
