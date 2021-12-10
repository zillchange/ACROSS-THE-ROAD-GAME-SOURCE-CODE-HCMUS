#include "Menu.h"
#include "CGAME.h"
#include "CBIRD.h"
#include "CDINAUSOR.h"
#include "CMOTOR.h"
#include "CTRUCK.h"
#include "Utility.h"

#include <thread>
#include <conio.h>
#include <string>
#include <iostream>

bool isInApp = true;                                //Biến để giữ chương trình luôn chạy vòng lặp giữa menu và game
bool IS_RUNNING;                                    //Biến để giữ thread luôn chạy vòng lặp
char input;                                         //Biến để lưu giữ ký tự người dùng nhập vào
CGAME cg;                                           //Biến này đại diện cho game của mình
int level;

void subThread();                                   //Một cái sub thread chạy song song với chương trình chính, đảm nhiệm việc in-game

                                                    //--------------------- main ---------------------

int main()
{
    int slot;                                       //Biến dùng để lưu vị trí người dùng muốn save, mình có 3 slot game save
    initWindow();                                   //Setup chỉnh sửa cửa sổ console
    //mo am thanh
    intro();                                        //Intro

    while (isInApp)
    {
        // mo am thanh
        menu();                                     //Menu

        if (mainMenuScreen == 0 && subMenuChoice == 2)//Khi người dùng chọn exit game trong menu thì break và thoát khỏi vòng lặp, kết thúc chương trình
            break;

        if (mainMenuScreen == 1)                    //Khi người dùng chọn load một file save nào đó thì lấy thông số của cái slot đó lên và gán vào các biến.
            cg.loadGame(fileSaveChoice + 1);
        else                                        //Còn nếu người dùng chọn new game thì thiết lập lại thông số (level = 0) (chương trình sẽ có 10 level, qua hết là phá đảo)
            cg.resetGame(subMenuChoice);

        IS_RUNNING = true;
        //dong am thanh
        cg.startGame();                             //Khỏi động trò chơi (WIP. Hiện tại chưa có thành phần nào trong game nên là hàm này chưa có gì!)

        thread t(subThread);                        //Khởi tạo một thread, nhiệm vụ là xử lý game song song với chương trình chính (chương trình chính chỉ lấy input của người chơi và xử lý những thứ bên ngoài trò chơi như tạm dừng, save game, buộc thoát game,...)
        while (IS_RUNNING)
        {
            if (!cg.getPeople().isDead())        //Nếu người dùng chưa chết thì chạy game tiếp
            {
                if (_kbhit())                           //Khi người dùng có bấm phím thì hàm trả về true
                {
                    input = _getch();                   //Lấy phím mà người dùng mới nhập
                    if (input == -32)                   //Phím điều hướng thực chất là tổ hợp 2 ký tự ascii, -32 là ký tự đầu tiên (dấu hiệu cho biết người dùng vừa nhập phím điều hướng)
                        input = _getch();
                    switch (input)
                    {
                    case 27:                        //Phím có ký tự 27 là esc
                        IS_RUNNING = false;         
                        cg.exitGame(&t);
                        terminate();
                        return 0;
                        break;
                    case 'p':
                        cg.pauseGame(t.native_handle());
                        break;
                    case 'c':
                        cg.remuseGame(t.native_handle());
                        break;
                    case 's':
                        cg.pauseGame(t.native_handle());
                        gotoXY(45, 2, "Which slot do you save in (1-3): ");
                        cin >> slot;
                        gotoXY(45, 2, "                                  ");
                        cin.ignore();
                        cg.saveGame(slot);
                        cg.remuseGame(t.native_handle());
                        break;
                    default:
                        break;
                    }
                }
                Sleep(100);
            }
            else
            {
                IS_RUNNING = false;
                cg.exitGame(&t);
                level = cg.getLevel();
                mainMenuScreen = 3;
            }
        }

    }
}

//--------------------- khác ---------------------

void subThread()
{
    int motorIdx, birdIdx, tructIdx, dinIndex, motorStopCount, birdStopCount, tructStopCount, dinStopCount;
    int max = 200;
    motorIdx = birdIdx = tructIdx = dinIndex = motorStopCount = birdStopCount = tructStopCount = dinStopCount = 0;
    float additionalSpeed = 0;
    switch (cg.getDifficulty()) // get dô khó
    {
    case 0:
        additionalSpeed = 0;
        break;
    case 1:
        additionalSpeed = 0.25;
        break;
    case 2:
        additionalSpeed = 0.75;
        break;
    default:
        break;
    }

    while (IS_RUNNING)
    {
        if (!cg.getPeople().isDead())               //Nếu người chơi chưa chết thì cập nhật thông tin vị trí mới của người chơi (nếu có)
        {
            cg.updatePosPeople(input);
        }
        input = ' ';

        if (motorIdx < cg.getMotorLimit() && !motorStopCount)
            cg.getMotor()[motorIdx].Move(static_cast<int>(1.0 * 4 * (cg.getLevel() + 1) / 10 + additionalSpeed) + 1);
        if (birdIdx < cg.getBirdLimit() && !birdStopCount)
            cg.getBird()[birdIdx].Move(static_cast<int>(1.0 * 2 * (cg.getLevel() + 1) / 10 + additionalSpeed) + 1);
        if (tructIdx < cg.getTruckLimit() && !tructStopCount)
            cg.getTruck()[tructIdx].Move(static_cast<int>(1.0 * 4 * (cg.getLevel() + 1) / 10 + additionalSpeed) + 1);
        if (dinIndex < cg.getDinLimit() && !dinStopCount)
            cg.getDinausor()[dinIndex].Move(static_cast<int>(1.0 * 1 * (cg.getLevel() + 1) / 10 + additionalSpeed) + 1);

        motorIdx++;
        birdIdx++;
        tructIdx++;
        dinIndex++;

        if (motorStopCount > 0)
            motorStopCount--;
        else
        {
            if (getRandomInt(1, max) <= 1)
                motorStopCount = cg.getMotorLimit() * getRandomInt(10, 15);
        }

        if (birdStopCount > 0)
            birdStopCount--;
        else
        {
            if (getRandomInt(1, max) <= 1)
                birdStopCount = cg.getBirdLimit() * getRandomInt(10, 25);
        }

        if (tructStopCount > 0)
            tructStopCount--;
        else
        {
            if (getRandomInt(1, max) <= 1)
                tructStopCount = cg.getTruckLimit() * getRandomInt(10, 25);
        }

        if (dinStopCount > 0)
            dinStopCount--;
        else
        {
            if (getRandomInt(1, max) <= 1)
                dinStopCount = cg.getDinLimit() * getRandomInt(10, 25);
        }


        if (motorIdx > cg.getMotorLimit())
            motorIdx = 0;
        if (birdIdx > cg.getBirdLimit())
            birdIdx = 0;
        if (tructIdx > cg.getTruckLimit())
            tructIdx = 0;
        if (dinIndex > cg.getDinLimit())
            dinIndex = 0;
        cg.getDinausor()->tell(cg.getPeople().getY());
        cg.getBird()->tell(cg.getPeople().getY());
        cg.getTruck()->tell(cg.getPeople().getY());
        cg.getMotor()->tell(cg.getPeople().getY());
       if (cg.getPeople().isImpact(static_cast<CANIMAL*> (cg.getBird()), cg.getBirdLimit()) ||
           cg.getPeople().isImpact(static_cast<CANIMAL*> (cg.getDinausor()), cg.getDinLimit()) ||
           cg.getPeople().isImpact(static_cast<CVEHICLE*> (cg.getMotor()), cg.getMotorLimit()) ||
           cg.getPeople().isImpact(static_cast<CVEHICLE*> (cg.getTruck()), cg.getTruckLimit()))
       {
          /* cout << "Game over" << endl;*/
           cg.getPeople().tell();
           cg.loseGame();
       }
        
       if (cg.getPeople().isFinish())              //Kiểm tra xem nhân vật đã đi đến cuối map chưa, nếu rồi thì lên cấp hoặc phá đảo
       {
           cg.setLevel(cg.getLevel() + 1);
           cg.getPeople().resetPos();
           gotoXY(cg.getPeople().getX(), cg.getPeople().getY(), cg.getPeople().player);
           string level = "Level : " + to_string(cg.getLevel());
          
           gotoXY(4, 1,level );
       }
        Sleep(25);
    }
}
