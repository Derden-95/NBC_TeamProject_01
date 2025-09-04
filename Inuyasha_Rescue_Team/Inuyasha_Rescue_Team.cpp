// Inuyasha_Rescue_Team.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "BattleManager.h"
#include "Progressbar.h"
#include "Text.h"
#include "BattleGrid.h"
//#include <windows.h>

int main()
{
    ////std::cout << "Hello World!\n";

    //system("mode con: cols=1920 lines=1080");

    HWND hwnd = GetConsoleWindow();
    Sleep(10);//If you execute these code immediately after the program starts, you must wait here for a short period of time, otherwise GetWindow will fail. I speculate that it may be because the console has not been fully initialized.
    HWND owner = GetWindow(hwnd, GW_OWNER);
    if (owner == NULL) {
        // Windows 10
        SetWindowPos(hwnd, nullptr, 0, 0, 500, 500, SWP_NOZORDER | SWP_NOMOVE);
    }
    else {
        // Windows 11
        SetWindowPos(owner, nullptr, 0, 0, 1920, 1080, SWP_NOZORDER | SWP_NOMOVE);
    }
    //std::cout << "NAMENAMENAME" << std::endl;
    //std::cout << "NAMENAMENAME" << std::endl;
    //std::cout << "NAMENAMENAME" << std::endl;
    //std::cout << "DM : 050 ■■■" << std::endl;
    //std::cout << "         ■■■" << std::endl;
    //std::cout << "EN : 070 ■■■" << std::endl;


    Progressbar p1HPbar(97, 0, 0, 100, Color::YELLOW, Color::RED, true);
    Text HPTEXT(p1HPbar.GetRight() + 1, p1HPbar.GetBottom() - 1, 3, "▥HP▥", YELLOW, BLACK);
    Progressbar p2HPbar(97, HPTEXT.GetRight() + 1, HPTEXT.GetBottom() - 1, 100, Color::YELLOW, Color::RED, false);
    Progressbar p1STbar(97, p1HPbar.GetLeft(), p1HPbar.GetBottom(), 100, Color::YELLOW, Color::BROWN, true);
    Text STTEXT(p1STbar.GetRight() + 1, p1STbar.GetBottom() - 1, 3, "▥ST▥", YELLOW, BLACK);
    Progressbar p2STbar(97, STTEXT.GetRight() + 1, STTEXT.GetBottom() - 1, 100, Color::YELLOW, Color::BROWN, false);

    BattleGrid Gird(200, 50, p1STbar.GetLeft(), p1STbar.GetBottom());
    Gird.DrawGrid();
    Gird.SetCharacter(0, 1, "@", RED, BLACK);
    Gird.SetCharacter(3, 1, "#", BLUE, BLACK);
    Gird.DrawCharacter();
    bool asd[3][3] = { {0, 1, 0}, {1, 1, 1}, {0, 1, 0} };
    Gird.PaintBlocks(2, 2, asd, BLUE);

    p1HPbar.SetValue(50);
    p2HPbar.SetValue(70);
    p1STbar.SetValue(70);
    p2STbar.SetValue(50);
    p1HPbar.Draw();
    HPTEXT.Draw();
    p2HPbar.Draw();
    p1STbar.Draw();
    STTEXT.Draw();
    p2STbar.Draw();

    //Text HP(bar.GetRight() + 1, bar.GetBottom() - 1, 3, "▥HP▥", YELLOW, BLACK);
    /*BattleGrid Grid(100, 15, 0, 0);
    Grid.DrawGrid();
    Grid.SetCharacter(0, 1, "@", RED, BLACK);
    Grid.SetCharacter(3, 1, "$", BLUE, BLACK);
    Grid.DrawCharacter();*/

    //bar.Draw();
    //HP.Draw();
    //bar2.Draw();



    //Player p1;
    //Player p2;

    //Card_Move moveUp(0, 0, 1, 0);
    //Card_Move moveDown(0, 0, -1, 0);
    //Card_Move moveRight(0, 0, 0, 1);
    //Card_Move moveLeft(0, 0, 0, -1);
    //
    //bool range[3][3] = { {0, 1, 0},{1, 1, 1,},{0, 1, 0} };

    //Card_Attack attack1(50, 15, range, 2, 2);

    //Card_HP_Healing HP_Healing(30, 0);

    //Card_Stamina_Healing Stamina_Healing(30, 0);

    //Card_Guard Guard(50, 0);
    //
    //p1.AddCard(moveUp);
    //p1.AddCard(moveDown);
    //p1.AddCard(moveRight);
    //p1.AddCard(moveLeft);
    //p1.AddCard(attack1);
    //p1.AddCard(HP_Healing);
    //p1.AddCard(Stamina_Healing);
    //p1.AddCard(Guard);

    //p2.AddCard(moveUp);
    //p2.AddCard(moveDown);
    //p2.AddCard(moveRight);
    //p2.AddCard(moveLeft);
    //p2.AddCard(attack1);
    //p2.AddCard(HP_Healing);
    //p2.AddCard(Stamina_Healing);
    //p2.AddCard(Guard);

    //BattleManager bm(p1, p2);
    //bm.PrintStatus();
    //bm.PrintGrid(0, 2);
    //bm.PrintPlayerCardList(0, 11);


}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
