#include "tile.h"
Tile::Tile() {
    isHidden = true;
    isFlagged = false;
    isMine = false;
    hasInside = false;

    cover.setTexture(TextureManager::GetTexture("tile_hidden"));
    background.setTexture(TextureManager::GetTexture("tile_revealed"));
    flag.setTexture(TextureManager::GetTexture("flag"));

    for(int i = 0; i < 8; i++){
        neighbors.push_back(nullptr);
    }
    neighborMines = 0;
    xPos = 0;
    yPos = 0;
}
