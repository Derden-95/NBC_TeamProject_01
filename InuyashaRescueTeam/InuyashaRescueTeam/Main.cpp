#include "Player.hpp"

int main()
{
    Player player("Hero", 1, 100, 50, 10, 5);
    hideCursor(); // 시작 전 커서 숨기기

    while (true) {
        // 커서 위치 갱신 
        setCursorPosition(0, 0);

        std::cout << "***** 플레이어 이동 테스트 *****" << std::endl;
        std::cout << "방향키로 이동하세요. (Q 혹은 q 를 누르면 종료)" << std::endl;
        std::cout << "E 혹은 e 를 누를 시 경험치 증가 (레벨 업 테스트)" << std::endl;
        player.PrintStatus();
        setCursorPosition(0, 13);

        // _getch()는 키를 누르는 즉시 문자를 반환 (Enter 키 불필요)
        int keyInput = _getch();

        if (keyInput == 'q' || keyInput == 'Q') {
            std::cout << "게임을 종료합니다." << std::endl;
            break;
        }

        // * 참고 : 방향키 입력은 224라는 특수 값과 함께 입력됨
        if (keyInput == 224) {
            keyInput = _getch(); // 실제 방향키 값을 얻기 위해 한 번 더 호출
            switch (keyInput) {
            case 72: // 위쪽 방향키
                player.Move(Direction::UP);
                break;
            case 80: // 아래쪽 방향키
                player.Move(Direction::DOWN);
                break;
            case 75: // 왼쪽 방향키
                player.Move(Direction::LEFT);
                break;
            case 77: // 오른쪽 방향키
                player.Move(Direction::RIGHT);
                break;
            }
        }

        if (keyInput == 'e' || keyInput == 'E')
        {
            player.AddEXP(50);
        }
    }

    return 0;
}