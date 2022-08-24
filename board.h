#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "tile.h"
#include "Random.h"
using namespace std;

class Board {

private:
    int width;
    int height;
    int mineCount;
    int tileCount;
    int flagCounter;
    int originalMineCount;

    sf::Sprite flag1, flag2, flag3, flag4, flag5, flag6, flag7, flag8, flag9, flag0, flagNeg;
    sf::Sprite flagHundreds, flagTens, flagOnes, flagSign;
    void ConnectTiles();
    bool debug, lose, win;
    void CreateTestBoard(string fileName);
    sf::Sprite& GetFlag(int num);
    void LoadFlagSprites();
public:
    vector<Tile> tiles;
    vector<Tile> specialButtons;
    Board();
    Board(int width, int height, int mineCount);
    void RevealTile(int xPos, int yPos);
    void RevealTile(Tile& tile);
    void RecursiveReveal(int xPos, int yPos);
    Tile& TileAt(int x, int y);
    bool TileExists(int x, int y) const;
    void DrawGameBoard(sf::RenderWindow& window);
    void CreateGameBoard();
    void CreateTest1Board();
    void CreateTest2Board();
    void CreateTest3Board();
    void Restart();
    int GetWidth() const;
    int GetHeight() const;
    void FlagToggle(int xPos, int yPos);
    void ToggleDebugBoard();
    void Lose();
    void Win();
    bool WinCheck();
    void UpdateFlagCounter();
};