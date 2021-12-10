#pragma once
#include <string>
#include <vector>
#include <Windows.h>
using namespace std;

extern int WIDTH;
extern int HEIGHT;
extern bool CUR_SHOW;
void SetWindowSize(SHORT width, SHORT height);
void SetScreenBufferSize(SHORT width, SHORT height);
void FixConsoleWindow();
void ShowCur(bool CursorVisibility);
void SetFont(int size, const wchar_t* font);				//Đổi size chữ, màu chữ trong console
int whereX();												//Trả về vị trí x hiện tại của con trỏ màn hình
int whereY();												//Trả về vị trí y hiện tại của con trỏ màn hình
void gotoXY(SHORT posX, SHORT posY);						//Đưa con trỏ đến vị trí x, y
void gotoXY(int x, int y, string text);				//Đưa con trỏ đến vị trí x, y và in ra một đoạn string
void gotoXY(int x, int y, string text, int backgound_color, int text_color);
void gotoXY(int x, int y, vector <string> text);	//Đưa con trỏ đến vị trí x, y và in ra một vector string (ví dụ cái logo crossing road)
void gotoXYClear(int x, int y, vector <string> text);
void SetColor(int backgound_color, int text_color);			//Đổi màu nền, màu chữ sẽ in
void initWindow();
void printBorder(int posX = 4, int posY = 3);
