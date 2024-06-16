#include <ncurses.h>

// 후에 팔레트 편히 쓰기 위한 enum
enum Color {
    WHITE = 1,
    CYAN,
    BLUE,
    RED,
    YELLOW,
    MAGENTA,
    GREEN,
    BLACK
};


static void initColor() {
    // curses 모드 시작
    initscr();
    // Color 사용 선언
    start_color();

    // 1번 팔레트, 폰트색, 폰트배경색
    init_pair(Color::WHITE,COLOR_BLACK,COLOR_WHITE);
    init_pair(Color::CYAN,COLOR_BLACK,COLOR_CYAN);
    init_pair(Color::BLUE,COLOR_BLACK,COLOR_BLUE);
    init_pair(Color::RED,COLOR_BLACK,COLOR_RED);
    init_pair(Color::YELLOW,COLOR_BLACK,COLOR_YELLOW);
    init_pair(Color::MAGENTA,COLOR_BLACK,COLOR_MAGENTA);
    init_pair(Color::GREEN,COLOR_BLACK,COLOR_GREEN);
    init_pair(Color::BLACK,COLOR_WHITE,COLOR_BLACK);

    // Attribute 적용
    attron(COLOR_PAIR(Color::WHITE));

    // 한 Attribute로 윈도우 전체 적용
    wbkgd(stdscr, COLOR_PAIR(Color::WHITE));

    // Attribute 해제
    attroff(COLOR_PAIR(Color::WHITE));
}
