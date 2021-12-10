#pragma once
#include <string>
#include <vector>
using namespace std;

extern int mainMenuScreen;
extern int subMenuChoice;
extern bool isInApp;
extern int fileSaveChoice;
extern int level;

void menu();
void staticPart();
void menuControl();
void redirect();
void getSaveName(string saveName[3]);
void intro();
void outro();
