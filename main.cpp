#include <cstdlib>
#include <ctime>
#include "SnakeGame.h"
//#include "Color.h"

using namespace std;

int main()
{
    // Curses 모드 시작
    initscr();
    cbreak();//입력을 즉시 프로그램에서 사용
    noecho();//입력을 출력하지 않음
    scrollok(stdscr, TRUE); //창의 커서가 창 영역을 벗어났을때, 한 줄 위로 스크롤
    nodelay(stdscr, TRUE); // getch 비 블로킹 (getch-> 입력이 없으면 -1 반환, 그렇지 않으면 키가 눌릴 때까지 기다림


    keypad(stdscr, TRUE);// 특수 키 입력 가능하게끔 설정
	srand(time(NULL));
	initColor();

	SnakeGame game;
	game.gameStart();
}
