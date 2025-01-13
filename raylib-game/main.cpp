// raylib-game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "game.h"
#include "colors.h"
#include<string.h>

double lastupdate = 0;

bool checkInterval(double interval) {
    double currTime = GetTime();
    if (currTime - lastupdate >= interval) {
        lastupdate = currTime;
        return true;
    }
    return false;
}

int main(void)
{
    InitWindow(500, 620, "Tetris");
    SetTargetFPS(60);
    Font font = LoadFontEx("Jersey_15/font.ttf", 64, 0, 0);
    char displayScore[100];

    Game game = Game();
    
    while (WindowShouldClose() == false) {
        game.handleInput();

        if (checkInterval(0.3)) {
            game.moveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkblue);
        DrawTextEx(font, "Score", { 365,15 }, 38, 2, WHITE);
        DrawRectangleRounded({ 320,55,170,60 }, 0.3, 6,lightblue );
    
        sprintf_s(displayScore, "%d", game.score);
        Vector2 textsize = MeasureTextEx(font, displayScore, 38, 2);

        DrawTextEx(font, displayScore, {320+(170-textsize.x)/2,65}, 38, 2, WHITE);

        DrawTextEx(font, "Next", { 370,175 }, 38, 2, WHITE);
        DrawRectangleRounded({ 320,215,170,180 }, 0.3, 6, lightblue);

        if (game.gameover) {
            DrawTextEx(font, "Game Over", { 320,450 }, 38, 2, WHITE);
        }
        
        game.draw();
        EndDrawing();
    }
    return 0;
}


