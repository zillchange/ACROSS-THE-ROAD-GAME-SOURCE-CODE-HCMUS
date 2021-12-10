#pragma once
#include <vector>
#include <string>
using namespace std;

class CVEHICLE {
private:
	int x, y;
public:
	CVEHICLE();

	static vector<string> Truck;
	static vector<string> Motor;
	static vector<string> Ambulance;

	virtual void Move(int speed) = 0;

	int getX() const;
	int getY() const;
	void setX(int _x);
	void setY(int _y);

	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
};
