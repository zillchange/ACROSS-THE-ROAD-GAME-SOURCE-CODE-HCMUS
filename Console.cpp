#include "Console.h"
#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);


int WIDTH = 120;        //Độ rộng màn hình
int HEIGHT = 40;        //Độ dài màn hình
bool CUR_SHOW = false;

void SetWindowSize(SHORT width, SHORT height)
{
 SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Bottom = height - 1;
    WindowSize.Right = width - 1;

    SetConsoleWindowInfo(console, 1, &WindowSize);
}

void SetScreenBufferSize(SHORT width, SHORT height)
{
    COORD NewSize;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleScreenBufferSize(console, NewSize);
}

void FixConsoleWindow() {
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void ShowCur(bool CursorVisibility)
{
    CONSOLE_CURSOR_INFO ConCurInf;

    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;

    SetConsoleCursorInfo(console, &ConCurInf);
}

void SetFont(int size, const wchar_t* font)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof cfi;
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = size;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, font);
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    /*SetCurrentConsoleFontEx(console, FALSE, &cfi);*/
}

int whereX()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(console, &csbi))
        return csbi.dwCursorPosition.X;
    return -1;
}

int whereY()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(console, &csbi))
        return csbi.dwCursorPosition.Y;
    return -1;
}

void gotoXY(SHORT posX, SHORT posY)
{
    COORD CursorPosition;
    CursorPosition.X = posX;
    CursorPosition.Y = posY;

    SetConsoleCursorPosition(console, CursorPosition);
}

void gotoXY(int x, int y, string text)
{
    COORD CursorPosition;
    CursorPosition.X = x;
    CursorPosition.Y = y;

    SetConsoleCursorPosition(console, CursorPosition);
    cout << text;
}

void gotoXY(int x, int y, string text, int backgound_color, int text_color)
{
    SetColor(backgound_color, text_color);
    COORD CursorPosition;
    CursorPosition.X = x;
    CursorPosition.Y = y;

    SetConsoleCursorPosition(console, CursorPosition);
    cout << text;
}

void gotoXY(int x, int y, vector<string> text)
{
    int lineCount = text.size();
    int textLength = text[0].size();
    int lBorder = 4;
    int rBorder = 115;
    int printSize;
    COORD CursorPosition;

    if (x <= lBorder)
    {
        printSize = lBorder - x + 1;
        if (printSize > textLength)
            return;
        for (int i = 0; i < lineCount; i++)
        {
            text[i] = text[i].substr(printSize, textLength);
        }
        x = lBorder + 1;
    }

    if (textLength + x > rBorder)
    {
        printSize = rBorder - x;
        if (printSize < 1)
            return;
        for (int i = 0; i < lineCount; i++)
        {
            text[i] = text[i].substr(0, printSize);
        }
    }

    CursorPosition.X = x;
    CursorPosition.Y = y;

    SetConsoleCursorPosition(console, CursorPosition);
    for (int i = 0; i < lineCount; i++)
    {
        cout << text[i];
        gotoXY(x, ++y);
    }
}

void gotoXYClear(int x, int y, vector <string> text)
{
    for (int i = 0; i < text.size(); i++)
    {
        fill(text[i].begin(), text[i].end(), ' ');
    }
    gotoXY(x, y, text);
}

void SetColor(int backgound_color, int text_color)
{
    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(console, color_code);
}

void printBorder(int posX, int posY)
{
    std::string border(WIDTH - 2 - 8, '\xCD');
    gotoXY(posX, posY++);
    std::cout << "\xC9" << border << "\xBB" << '\n';
    for (int x = 0; x < HEIGHT - 8; x++)
    {
        gotoXY(posX, posY++);
        std::cout << "\xBA                                                                                                              \xBA" << '\n';
    }
    gotoXY(posX, posY++);
    std::cout << "\xC8" << border << "\xBC" << '\n';
}

//--------------------- Hàm cài đặt màn hình console ---------------------
//Ở trong này ông có thể cài đặt cái hàm cho lúc mới chạy chương trình

void initWindow()
{
    SetFont(20, L"Poppins");                 //Set size chữ và font chữ
    SetColor(16, 11);
    SetWindowSize(WIDTH, HEIGHT);           //Set chiều dài với chiều cao cửa sổ console (đơn vị là ký tự KHÔNG PHẢI PIXEL nên là chỉnh khá khó chịu)
    SetScreenBufferSize(WIDTH, HEIGHT);            //Set screen buffer size mục đích ở đây giúp cho thanh cuộn dọc biến mất
    FixConsoleWindow();                             //Cái này trong file pdf của thầy, giúp cho cố định cửa sổ
    SetConsoleTitle(L"Crossing game");     //Cái này đổi tiêu đề của cái cửa sổ
    ShowCur(CUR_SHOW);                              //Ẩn hiện con trỏ màn hình
};