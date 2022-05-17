#include "render.h"

Render::Render(char stage){
    //game window
    setMap(stage);
    initUI();
}

void Render::setMap(int stage){
    std::string mapFile = "/home/younghee/map/map" + std::to_string(stage-48) + ".txt";
    //"../map/map" + stage + ".txt"
    std::ifstream fin(mapFile);
    try{
        if(!fin) throw;
    }
    catch(...){
        std::cout << "file read failed." << std::endl;
    }

    int row = 0;
    int col = 0;
    int c;
    
    while((c = fin.get()) != EOF){
        if (c == '\n'){
            row += 1;
            col = 0;
            continue;
        }
        else if (c != '0' && c != '1' && c!= '2'){
            continue;
        }

        initMapDataArray[row][col] = (char)c;
        col += 1;
    }
    fin.close();
}

void Render::initUI(){
    snakeWindow = newwin(23, 46, 5, 10);
    start_color();
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    wbkgd(snakeWindow, COLOR_PAIR(2));

    updateUI();
    wrefresh(snakeWindow);
    time_t start = time(NULL);
    time_t end;
    int duration;

    while(true) {
        int in = dir;
        // key input
        if(keyInput()) {
            in = getch();
            if(in==dir)
            continue;
        }
    }
    delwin(snakeWindow);

}

void Render::updateUI(int time) {
    updateMapData(time);
    for(int i=0; i<ROW; i++) {
        for(int j=0; j<COL*2; j++) {
            mvwprintw(snakeWindow, i, j, " ");
        }
    }
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++){
            char c = mapDataArray[i][j];
            if (c == WALL) {
                mvwprintw(snakeWindow, i, j*2, "\u25A1");
            }
            else if (c == IMMUNEWALL) {
                mvwprintw(snakeWindow, i, j*2, "\u2B1B");
            }
            else if (c == EMPTY) {
                mvwprintw(snakeWindow, i, j*2, "\u0020");
            }
        }
    }
    wrefresh(snakeWindow);
}

void Render::updateMapData(int time) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++){
            char c = initMapDataArray[i][j];
            mapDataArray[i][j] = c;
        }
    }
}

bool Render::getGameClear() {
    return gameClear;
}

bool Render::keyInput() {
    int ch;
    bool ret;

    nodelay(stdscr, TRUE);

    ch = getch();
    if(ch==ERR)
        ret = false;
    else {
        ret = true;
        ungetch(ch);
    }

    nodelay(stdscr, FALSE);
    return ret;
}
