#include "Menu.h"
#include "console.h"
#include <sstream>
#include <conio.h>
#include <fstream>
#include <iostream>
using namespace std;

int mainMenuScreen = 0;                             //Biến này dùng để chuyển đổi giữa các giao diện menu. vd: =0 là giao diện màn hình chính, =1 là giao diện chọn file save, =2 là giao diện chọn độ khó
int subMenuChoice = 0;                              //Biến này dùng để theo dõi người dùng đã chọn ô nào trong menu. vd ở mainMenuScreen = 0 thì người dùng đang ở màn hình chính, subMenuChoice = 2 là người dùng đã chọn exit game
int fileSaveChoice = -1;                            //Biến này dùng để theo dõi người dùng đã chọn file save nào trong menu
bool isStillInMenu;                          //Biến này bằng false thì sẽ thoát khỏi menu rồi
string saveName[3];                                 //Biến lưu tên game save ở các slot
string space = "                      ";            //Nếu ở một slot nào đó không có thông tin save game thì màn hình sẽ in ra chuỗi này

vector<string> logo = {
    "   __________  ____  __________ _____   ________   ____  ____  ___    ____ ",
    "  / ____/ __ \\/ __ \\/ ___/ ___//  _/ | / / ____/  / __ \\/ __ \\/   |  / __ \\",
    " / /   / /_/ / / / /\\__ \\\\__ \\ / //  |/ / / __   / /_/ / / / / /| | / / / /",
    "/ /___/ _, _/ /_/ /___/ /__/ // // /|  / /_/ /  / _, _/ /_/ / ___ |/ /_/ / ",
    "\\____/_/ |_|\\____//____/____/___/_/ |_/\\____/  /_/ |_|\\____/_/  |_/_____/  "
};

vector<string> powered_text = {
    "      ____                                   __   __             __                          ______",
    "     / __ \\____ _      _____  ________  ____/ /  / /_  __  __   / /____  ____ _____ ___     <  <  /",
    "    / /_/ / __ \\ | /| / / _ \\/ ___/ _ \\/ __  /  / __ \\/ / / /  / __/ _ \\/ __ `/ __ `__ \\    / // / ",
    "   / ____/ /_/ / |/ |/ /  __/ /  /  __/ /_/ /  / /_/ / /_/ /  / /_/  __/ /_/ / / / / / /   / // /  ",
    "  /_/    \\____/|__/|__/\\___/_/   \\___/\\__,_/  /_.___/\\__, /   \\__/\\___/\\__,_/_/ /_/ /_/   /_//_/   ",
    "                                                    /____/                                         "
};

vector<string> welcome = {
" _       __________    __________  __  _________",
"| |     / / ____/ /   / ____/ __ \\/  |/  / ____/",
"| | /| / / __/ / /   / /   / / / / /|_/ / __/   ",
"| |/ |/ / /___/ /___/ /___/ /_/ / /  / / /___   ",
"|__/|__/_____/_____/\\____/\\____/_/  /_/_____/   "
};

vector<string> goodbye = {
"   __________  ____  ____  ______  ________",
"  / ____/ __ \\/ __ \\/ __ \\/ __ ) \\/ / ____/",
" / / __/ / / / / / / / / / __  |\\  / __/   ",
"/ /_/ / /_/ / /_/ / /_/ / /_/ / / / /___   ",
"\\____/\\____/\\____/_____/_____/ /_/_____/   "
};

vector<string> congrats = {
"   __________  _   ____________  ___  ___________ __",
"  / ____/ __ \\/ | / / ____/ __ \\/   |/_  __/ ___// /",
" / /   / / / /  |/ / / __/ /_/ / /| | / /  \\__ \\/ / ",
"/ /___/ /_/ / /|  / /_/ / _, _/ ___ |/ /  ___/ /_/  ",
"\\____/\\____/_/ |_/\\____/_/ |_/_/  |_/_/  /____(_)   "
};

void menu()
{
    isStillInMenu = true;
    getSaveName(saveName);                          //Đầu tiên là lấy tên các lần save game trước
    while (isStillInMenu)
    {
        staticPart();                               //In ra phần tĩnh không có hoạt hoạ tương ứng với từng menu
        menuControl();                              //Nhận input và xử lý "hoạt hoạ" tương ứng với từng menu
        redirect();                                 //Sau khi người dùng chọn thì mình sẽ điều hướng người dùng đi nơi khác, vd ở menu chính người dùng chọn new game thì hàm này sẽ thiết lập thông số sao cho 2 hàm trên sẽ in ra màn hình chọn độ khó cho game
    }
}

void staticPart()
{
    system("cls");
    printBorder();
    if (mainMenuScreen != 3)
    {
        gotoXY(24, 10, logo);
        gotoXY(24, 15, "POWERED BY TEAM 11");
    }

    switch (mainMenuScreen)
    {
    case 0:
        gotoXY(50, 23, "       CONTINUE       ", 4, 15);
        gotoXY(50, 24, "       NEW GAME       ", 16, 11);
        gotoXY(50, 25, "         EXIT         ");
        break;

    case 1:
        gotoXY(50, 22, "       File save      ");
        gotoXY(50, 23, saveName[0], 4, 15);
        gotoXY(50, 24, saveName[1], 16, 11);
        gotoXY(50, 25, saveName[2]);
        gotoXY(50, 26, "         BACK         ");
        break;

    case 2:
        gotoXY(50, 23, "         EASY         ", 4, 15);
        gotoXY(50, 24, "        NORMAL        ", 16, 11);
        gotoXY(50, 25, "         HARD         ");
        gotoXY(50, 26, "         BACK         ");
        break;

    case 3:
        system("cls");
        gotoXY(50, 22, "You've reach level: " + std::to_string(level + 1));
        gotoXY(50, 23, "        REPLAY        ", 4, 15);
        gotoXY(50, 24, "         EXIT         ", 16, 11);
        gotoXY(35, 10, congrats);
        break;
    default:
        break;
    }
}

void selectString(int& yp, string& newS)
{
    switch (mainMenuScreen)
    {
    case 0:
        switch (yp)
        {
        case 23:
            newS = "       CONTINUE       ";
            break;
        case 24:
            newS = "       NEW GAME       ";
            break;
        case 25:
            newS = "         EXIT         ";
            break;
        default:
            if (yp < 23)
                yp++;
            else
                yp--;
            break;
        }
        break;

    case 1:
        switch (yp)
        {
        case 23:
            newS = saveName[0];
            break;
        case 24:
            newS = saveName[1];
            break;
        case 25:
            newS = saveName[2];
            break;
        case 26:
            newS = "         BACK         ";
            break;
        default:
            if (yp < 23)
                yp++;
            else
                yp--;
            break;
        }
        break;

    case 2:
        switch (yp)
        {
        case 23:
            newS = "         EASY         ";
            break;
        case 24:
            newS = "        NORMAL        ";
            break;
        case 25:
            newS = "         HARD         ";
            break;
        case 26:
            newS = "         BACK         ";
            break;
        default:
            if (yp < 23)
                yp++;
            else
                yp--;
            break;
        }
        break;

    case 3:
        switch (yp)
        {
        case 23:
            newS = "        REPLAY        ";
            break;
        case 24:
            newS = "         EXIT         ";
            break;
        default:
            if (yp < 23)
                yp++;
            else
                yp--;
            break;
        }
        break;

    default:
        break;
    }
}

void menuControl()
{
    int yp = 23, yOld = yp;
    bool print = true;
    string oldString = "", newString = "";
    while (true)
    {
        if (print)
        {

            selectString(yp, newString);

            gotoXY(50, yOld, oldString);

            gotoXY(50, yp, newString, 4, 15);
            SetColor(16, 11);
            yOld = yp;
            oldString = newString;
            print = false;
        }
        if (_kbhit())
        {
            char c = _getch();
            if (c == -32)
            {
                print = true;
                c = _getch();
                if (c == 72)
                {
                    yp--;
                }
                else if (c == 80)
                {
                    yp++;
                }
            }
            if (c == 13)
            {
                subMenuChoice = yp - 23;
                break;
            }
        }
    }
}

void redirect()
{
    switch (mainMenuScreen)
    {
    case 0:
        switch (subMenuChoice)
        {
        case 0:                         //Continue
            mainMenuScreen = 1;             
            break;
        case 1:                         //Newgame
            mainMenuScreen = 2;             
            break;
        case 2:                         //Exit
            isStillInMenu = false;
            isInApp = false;
            outro();
            break;

        default:
            break;
        }
        break;

    case 1:
        switch (subMenuChoice)
        {
        case 0:                         //Filesave_1
            if (saveName[0] != space)
            {
                fileSaveChoice = 0;
                isStillInMenu = false;
            }
            break;
        case 1:                         //Filesave_2
            if (saveName[1] != space)
            {
                fileSaveChoice = 1;
                isStillInMenu = false;
            }
            break;
        case 2:                         //Filesave_3
            if (saveName[2] != space)
            {
                fileSaveChoice = 2;
                isStillInMenu = false;
            }
            break;
        case 3:                         //Back
            mainMenuScreen = 0;
            break;
        default:
            break;
        }
        break;

    case 2:
        switch (subMenuChoice)
        {
        case 0:                         //Easy

            isStillInMenu = false;
            break;
        case 1:                         //Medium

            isStillInMenu = false;
            break;
        case 2:                         //Hard

            isStillInMenu = false;
            break;
        case 3:                         //Back
            mainMenuScreen = 0;
            break;

        default:
            break;
        }
        break;

    case 3:
        switch (subMenuChoice)
        {
        case 0:                         //Replay
            mainMenuScreen = 1;

            break;
        case 1:                         //Exit
            mainMenuScreen = 0;
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
}

void getSaveName(string saveName[3])
{
    string s, time;
    stringstream ss;
    int difficulty, level;
    std::ifstream ifs("save.txt");
    
    if (ifs.is_open())
    {
        for (int i = 0; i < 3; i++)
        {
            ss.clear();
            getline(ifs, s);

            if (s == "")
            {
                saveName[i] = space;
                continue;
            }

            ss << s;
            ss >> difficulty;
            ss.ignore();
            ss >> level;
            ss.ignore();
            getline(ss, time);

            if (difficulty == 1 && level == 9)
            {
                s = " Normal, lv:10, ";
                s += time[11];
                s += time[12];
                s += time[13];
                s += time[14];
                s += time[15];
                s += ' ';
            }
            else if (difficulty == 1)
            {
                s = " Normal, lv:0" + to_string(level + 1) + ", ";
                s += time[11];
                s += time[12];
                s += time[13];
                s += time[14];
                s += time[15];
                s += ' ';
            }
            else if (difficulty == 0 && level == 9)
            {
                s = "   Easy, lv:10, ";
                s += time[11];
                s += time[12];
                s += time[13];
                s += time[14];
                s += time[15];
                s += " ";
            }
            else if (difficulty == 0)
            {
                s = "   Easy, lv:0" + to_string(level + 1) + ", ";
                s += time[11];
                s += time[12];
                s += time[13];
                s += time[14];
                s += time[15];
                s += " ";
            }
            else if (difficulty == 2 && level == 9)
            {
                s = "   Hard, lv:10, ";
                s += time[11];
                s += time[12];
                s += time[13];
                s += time[14];
                s += time[15];
                s += " ";
            }
            else if (difficulty == 2)
            {
                s = "   Hard, lv:0" + to_string(level + 1) + ", ";
                s += time[11];
                s += time[12];
                s += time[13];
                s += time[14];
                s += time[15];
                s += " ";
            }
            
            saveName[i] = s;
        }
        ifs.close();
    }
}

void intro() {

    printBorder();
    gotoXY(40, 15, welcome);
    Sleep(2000);
    gotoXYClear(40, 15, welcome);
    gotoXY(25, 15, logo);
    Sleep(2000);
    gotoXYClear(25, 15, logo);
    gotoXY(10, 15, powered_text);
    Sleep(2000);
    gotoXYClear(10, 15, powered_text);
}

void outro() {
    system("cls");
    gotoXY(40, 15, goodbye);
    Sleep(2000);
    SetColor(16, 15);
}
