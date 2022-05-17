#include "snake.h"
#define COL 23
#define ROW 23

Snake::Snake(){
    initUI();
}

void Snake::initUI(){
    //unicode
    setlocale(LC_ALL,"");
    //start Curses mode
    initscr();
    //color use declare
    start_color();
    //start menu font color, bg color
    init_pair(1, COLOR_RED, COLOR_WHITE);
    //set bg colorbreak;
    bkgd(COLOR_PAIR(1));
    //no curse
    curs_set(0);
    //border
    border('*','*','*','*','*','*','*','*');
    //key input
    keypad(stdscr, TRUE);
    //no write in window
    noecho();


    //text
    mvprintw(5, 10, "Snake Game!");
    for(int i=0; i<4; i++){             //
        mvprintw(i+6, 10, "%d.Stage %d", i+1, i+1);
    }

    //choose stage
    char stage = '1';
    while(true){
        stage = getch();
        if(stage=='1' || stage=='2' || stage=='3' || stage=='4')
        break;
    }

    while(true){
        Render render(stage);
        if(!render.getGameClear()){
            break;
        }
        stage = (stage+1) % 53;
        if(stage==0){
            stage = 49;
        }
    }


    //refresh window
    refresh();
    endwin();
}
