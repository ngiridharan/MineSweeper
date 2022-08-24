#pragma once
#include "board.h"
class GameManager{
Board mainBoard;
bool canClick;
void Lose(Board& board);
void Win(Board& board);
void ReadBoard();

public:
    void Run();
};