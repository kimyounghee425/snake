#include <ncurses.h>
#include <string>
#include <fstream>
#include <iostream>
#include "snakeMove.h"

//random
#include <cstdlib>
//time sleep
#include <unistd.h>
#define EMPTY '0'
#define WALL '1'
#define IMMUNEWALL '2'

#define ROW 23
#define COL 23

class Render {
    char initMapDataArray [ROW][COL];
    char mapDataArray[ROW][COL];
    WINDOW *snakeWindow;
    WINDOW *scoreWindow;
    int dir = KEY_RIGHT;
    bool gameClear = false;

public:
    Render(char stage='1');
    void initUI();
    void updateUI(int time = 0);
    void endWindow();
    void setMap(int stage);
    char getMapData(int row, int col);
    void updateMapData(int time);
    bool keyInput();
    bool getGameClear();
};
