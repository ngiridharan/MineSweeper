#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "TextureManager.h"
using namespace std;

struct Tile{
    bool isMine, isHidden, isFlagged, hasInside;
    vector<Tile*> neighbors; // 1-top left, 2- top middle, 3- top right, 4- left, 5- right, 6- bottom left, 7- bottom middle, 8- bottom right
    sf::Sprite background, cover, inside, flag;
    int neighborMines, xPos, yPos;
    Tile();
    void SetHiddenStatus(bool status);

};


