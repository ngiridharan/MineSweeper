#include "board.h"
Board::Board() {
    width = 0;
    height = 0;
    tileCount = 0;
    mineCount = 0;
    flagCounter = 0;
    debug = false;
    lose = false;
    win = false;
    flag0.setTexture(TextureManager::GetTexture("digits"));
    flag0.setTextureRect(sf::IntRect(0,0,21,32));
    flag1.setTexture(TextureManager::GetTexture("digits"));
    flag1.setTextureRect(sf::IntRect(21,0,21,32));
    flag2.setTexture(TextureManager::GetTexture("digits"));
    flag2.setTextureRect(sf::IntRect(42,0,21,32));
    flag3.setTexture(TextureManager::GetTexture("digits"));
    flag3.setTextureRect(sf::IntRect(63,0,21,32));flag0.setTexture(TextureManager::GetTexture("digits"));
    flag4.setTexture(TextureManager::GetTexture("digits"));
    flag4.setTextureRect(sf::IntRect(84,0,21,32));
    flag5.setTexture(TextureManager::GetTexture("digits"));
    flag5.setTextureRect(sf::IntRect(105,0,21,32));
    flag6.setTexture(TextureManager::GetTexture("digits"));
    flag6.setTextureRect(sf::IntRect(126,0,21,32));
    flag7.setTexture(TextureManager::GetTexture("digits"));
    flag7.setTextureRect(sf::IntRect(147,0,21,32));
    flag8.setTexture(TextureManager::GetTexture("digits"));
    flag8.setTextureRect(sf::IntRect(168,0,21,32));
    flag9.setTexture(TextureManager::GetTexture("digits"));
    flag9.setTextureRect(sf::IntRect(189,0,21,32));
    flagNeg.setTexture(TextureManager::GetTexture("digits"));
    flagNeg.setTextureRect(sf::IntRect(210,0,21,32));

}
Board::Board(int width, int height, int mineCount) {
    flag0.setTexture(TextureManager::GetTexture("digits"));
    this->width = width;
    this->height = height;
    this->mineCount = mineCount;
    this->tileCount = width*height;
    originalMineCount = mineCount;
    flagCounter = mineCount;
    debug = false;
    lose = false;
    win = false;
    flag0.setTexture(TextureManager::GetTexture("digits"));
    flag0.setTextureRect(sf::IntRect(0,0,21,32));
    flag1.setTexture(TextureManager::GetTexture("digits"));
    flag1.setTextureRect(sf::IntRect(21,0,21,32));
    flag2.setTexture(TextureManager::GetTexture("digits"));
    flag2.setTextureRect(sf::IntRect(42,0,21,32));
    flag3.setTexture(TextureManager::GetTexture("digits"));
    flag3.setTextureRect(sf::IntRect(63,0,21,32));
    flag4.setTexture(TextureManager::GetTexture("digits"));
    flag4.setTextureRect(sf::IntRect(84,0,21,32));
    flag5.setTexture(TextureManager::GetTexture("digits"));
    flag5.setTextureRect(sf::IntRect(105,0,21,32));
    flag6.setTexture(TextureManager::GetTexture("digits"));
    flag6.setTextureRect(sf::IntRect(126,0,21,32));
    flag7.setTexture(TextureManager::GetTexture("digits"));
    flag7.setTextureRect(sf::IntRect(147,0,21,32));
    flag8.setTexture(TextureManager::GetTexture("digits"));
    flag8.setTextureRect(sf::IntRect(168,0,21,32));
    flag9.setTexture(TextureManager::GetTexture("digits"));
    flag9.setTextureRect(sf::IntRect(189,0,21,32));
    flagNeg.setTexture(TextureManager::GetTexture("digits"));
    flagNeg.setTextureRect(sf::IntRect(210,0,21,32));

}
void Board::Restart() {
    tiles.clear();
    CreateGameBoard();
    flagCounter = originalMineCount;
    win = false;
    lose = false;

}
void Board::CreateGameBoard(){
    bool randomPlacement[tileCount];
    for(int i = 0; i < tileCount; i++){
        if(i<originalMineCount)
            randomPlacement[i] = true;
        else {
            randomPlacement[i] = false;
        }
    }
    for(int i = 0 ; i < this->originalMineCount; i++){
        int pos = Random::Int(0, this->tileCount-1);
        bool temp = randomPlacement[i];
        randomPlacement[i] = randomPlacement[pos];
        randomPlacement[pos] = temp;
    }
    for(int i = 0; i < tileCount; i++){
        Tile temp;
        if(randomPlacement[i] == true){
            temp.isMine = true;
            temp.hasInside = true;
            temp.inside.setTexture(TextureManager::GetTexture("mine"));
            temp.xPos = i % width;
            temp.yPos = i/width;
        }
        tiles.push_back(temp);

    }
    //create all tile objects and put them into the tile vector
    ConnectTiles();  //connect all tiles

    for(int i = 0; i < tiles.size(); i++){
        for(int j = 0; j < 8; j++){
            if(tiles[i].neighbors[j]!=nullptr && tiles[i].neighbors[j]->isMine){
                tiles[i].neighborMines++;
                tiles[i].hasInside = true;
            }
        }
        if(tiles[i].neighborMines != 0&&!tiles[i].isMine)
        tiles[i].inside.setTexture(TextureManager::GetTexture("number_" + to_string(tiles[i].neighborMines)));
    }
}
void Board::CreateTestBoard(string fileName) {
    vector<int> fileData;
    string lineFromFile;
    string temp;
    ifstream inFile(fileName);
    while (!inFile.eof()) {
        getline(inFile, lineFromFile);
        for (int i = 0; i < lineFromFile.length(); i++) {
            int mine = int(lineFromFile[i])-48;     //digits start at 48
            fileData.push_back(mine);
        }
    }
    tiles.clear();
    mineCount = 0;
    for (int i = 0; i < tileCount; i++) {
        Tile temp;
        if (fileData[i] == 1) {
            temp.isMine = true;
            temp.hasInside = true;
            temp.inside.setTexture(TextureManager::GetTexture("mine"));
            mineCount++;
        }
        tiles.push_back(temp);
    }
    flagCounter = mineCount;
    ConnectTiles();  //connect all tiles

    for (int i = 0; i < tiles.size(); i++) {
        for (int j = 0; j < 8; j++) {
            if (tiles[i].neighbors[j] != nullptr && tiles[i].neighbors[j]->isMine) {
                tiles[i].neighborMines++;
                tiles[i].hasInside = true;
            }
        }
        if (tiles[i].neighborMines != 0 && !tiles[i].isMine)
            tiles[i].inside.setTexture(TextureManager::GetTexture("number_" + to_string(tiles[i].neighborMines)));
    }
    win = false;
    lose = false;
}
void Board::CreateTest1Board() {
    CreateTestBoard("boards/testboard1.brd");
}
void Board::CreateTest2Board() {
    CreateTestBoard("boards/testboard2.brd");
}
void Board::CreateTest3Board() {
   CreateTestBoard("boards/testboard3.brd");
}
void Board::DrawGameBoard(sf::RenderWindow &window) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            tiles[i * width + j].background.setPosition(j * 32, i * 32);
            window.draw(tiles[i * width + j].background);
            if (tiles[i * width + j].hasInside) {
                tiles[i * width + j].inside.setPosition(j * 32, i * 32);
                window.draw(tiles[i * width + j].inside);
            }

            if (tiles[i * width + j].isHidden) {
                tiles[i * width + j].cover.setPosition(j * 32, i * 32);
                window.draw(tiles[i * width + j].cover);
            }
            if(debug){
                if(tiles[i * width + j].isMine){
                    tiles[i * width + j].inside.setPosition(j * 32, i * 32);
                    window.draw(tiles[i * width + j].inside);
                }
            }
            if(tiles[i*width + j].isFlagged&&tiles[i*width + j].isHidden){
                tiles[i * width + j].flag.setPosition(j * 32, i * 32);
                window.draw(tiles[i * width + j].flag);
            }

            tiles[i * width + j].xPos = j;
            tiles[i * width + j].yPos = i;
        }
    }
    Tile smiley, debug, test1, test2, test3;
    if(!lose && !win)
    smiley.inside.setTexture(TextureManager::GetTexture("face_happy"));
    else if(win)
        smiley.inside.setTexture(TextureManager::GetTexture("face_win"));
    else if(lose)
        smiley.inside.setTexture(TextureManager::GetTexture("face_lose"));
    smiley.inside.setPosition((width / 2) * 32, height * 32);
    window.draw(smiley.inside);

    debug.inside.setTexture(TextureManager::GetTexture("debug"));
    debug.inside.setPosition((width - 8) * 32, height * 32);
    window.draw(debug.inside);

    test1.inside.setTexture(TextureManager::GetTexture("test_1"));
    test1.inside.setPosition((width - 6) * 32, height * 32);
    window.draw(test1.inside);

    test2.inside.setTexture(TextureManager::GetTexture("test_2"));
    test2.inside.setPosition((width - 4) * 32, height * 32);
    window.draw(test2.inside);

    test3.inside.setTexture(TextureManager::GetTexture("test_3"));
    test3.inside.setPosition((width - 2) * 32, height * 32);
    window.draw(test3.inside);
    specialButtons.push_back(smiley);
    specialButtons.push_back(debug);
    specialButtons.push_back(test1);
    specialButtons.push_back(test2);
    specialButtons.push_back(test3);

    UpdateFlagCounter();
    flagHundreds.setPosition(0, height*32);
    flagTens.setPosition(21, height*32);
    flagOnes.setPosition(42, height*32);
    flagSign.setPosition(63, height*32);
    window.draw(flagHundreds);
    window.draw(flagTens);
    window.draw(flagOnes);
    if(flagCounter<0)
    window.draw(flagSign);

}
bool Board::TileExists(int x, int y) const {
    if(x*y < tiles.size() && x<=width && y<=height){
        return true;
    }
    else
        return false;
}
Tile& Board::TileAt(int x, int y) {
    if(x*y<tiles.size() && x<=width && y<=height) {
        return tiles[y * width + x];
    }
    else{

    }
}
void Board::RevealTile(int xPos, int yPos) {

        if (TileExists(xPos, yPos) && TileAt(xPos, yPos).isHidden && !TileAt(xPos,yPos).isFlagged) {
            TileAt(xPos, yPos).isHidden = false;
        } else {

        }
}
void Board::RevealTile(Tile& tile) {
    RevealTile(tile.xPos, tile.yPos);
}
void Board::RecursiveReveal(int xPos, int yPos) {
    Tile tile = TileAt(xPos, yPos);
    if (!tile.hasInside && tile.isHidden && !tile.isFlagged) {
        RevealTile(tile);
        for(int i = 0; i < tile.neighbors.size(); i++){
            if(tile.neighbors[i] != nullptr){
                RecursiveReveal(tile.neighbors[i]->xPos,tile.neighbors[i]->yPos);
            }
        }
    }
    else{
        RevealTile(tile);
    }
}
void Board::ToggleDebugBoard() {
        debug = !debug;

}
void Board::FlagToggle(int xPos, int yPos) {
    if(TileExists(xPos,yPos) && TileAt(xPos,yPos).isHidden) {
        TileAt(xPos,yPos).isFlagged = !TileAt(xPos,yPos).isFlagged;
        if(TileAt(xPos,yPos).isFlagged){
            flagCounter--;
        }
        else{
            flagCounter++;
        }
    }

    else {
    }
}
void Board::Lose() {
    lose = true;
    for(int i = 0; i < tiles.size(); i++){
        if(tiles[i].isMine){
            RevealTile(tiles[i]);
        }
    }
}
void Board::Win(){
    win = true;
    for(int i = 0; i < tiles.size(); i++){
        if(tiles[i].isMine){
            tiles[i].isFlagged = true;
        }
    }
    flagCounter = 0;
    UpdateFlagCounter();
}
bool Board::WinCheck(){
    bool returnVal = true;
    for(int i = 0; i < tileCount; i++){
        if(!tiles[i].isMine){
            if(tiles[i].isHidden)
                return false;
            else{
                continue;
            }
        }

    }
    return returnVal;
}
void Board::ConnectTiles() {
    for(int i = 0; i < tileCount; i++){
        if(i == 0){
            for(int j = 0; j < 4; j++)
                tiles[i].neighbors[j] = (nullptr);
            tiles[i].neighbors[4] = (&tiles[i+1]);
            tiles[i].neighbors[5] = (nullptr);
            tiles[i].neighbors[6] = (&tiles[i+width]);
            tiles[i].neighbors[7] = (&tiles[i+1+width]);
        }
        else if(i == width-1){
            for(int j = 0; j < 3; j++)
                tiles[i].neighbors[j] = (nullptr);
            tiles[i].neighbors[3] = (&tiles[i-1]);
            tiles[i].neighbors[4] = (nullptr);
            tiles[i].neighbors[5] = (&tiles[i+width-1]);
            tiles[i].neighbors[6] = (&tiles[i+width]);
            tiles[i].neighbors[7] = (nullptr);
        }
        else if(i == (height-1) * (width)){
            tiles[i].neighbors[0] = (nullptr);
            tiles[i].neighbors[1] = (&tiles[i-width]);
            tiles[i].neighbors[2] = (&tiles[i-width+1]);
            tiles[i].neighbors[3] = (nullptr);
            tiles[i].neighbors[4] = (&tiles[i+1]);
            for(int j = 0; j < 3; j++)
                tiles[i].neighbors[j+5] = (nullptr);
        }
        else if(i == tileCount-1){
            tiles[i].neighbors[0] = (&tiles[i-width-1]);
            tiles[i].neighbors[1] = (&tiles[i-width]);
            tiles[i].neighbors[2] = (nullptr);
            tiles[i].neighbors[3] = (&tiles[i-1]);
            tiles[i].neighbors[4] = (nullptr);
            for(int j = 0; j < 3; j++)
                tiles[i].neighbors[j+5] = (nullptr);
        }
        else if(i<width){
            for(int j=0; j<3; j++)
                tiles[i].neighbors[j] = (nullptr);
            tiles[i].neighbors[3] = (&tiles[i-1]);
            tiles[i].neighbors[4] = (&tiles[i+1]);
            tiles[i].neighbors[5] = (&tiles[i+width-1]);
            tiles[i].neighbors[6] = (&tiles[i+width]);
            tiles[i].neighbors[7] = (&tiles[i + 1 + width]);
        }
        else if(i%width == 0){
            tiles[i].neighbors[0] = (nullptr);
            tiles[i].neighbors[1] = (&tiles[i-width]);
            tiles[i].neighbors[2] = (&tiles[i-width+1]);
            tiles[i].neighbors[3] = (nullptr);
            tiles[i].neighbors[4] = (&tiles[i+1]);
            tiles[i].neighbors[5] = (nullptr);
            tiles[i].neighbors[6] = (&tiles[i+width]);
            tiles[i].neighbors[7] = (&tiles[i+width+1]);
        }
        else if(i > (height-1)*width){
            tiles[i].neighbors[0] = (&tiles[i-width-1]);
            tiles[i].neighbors[1] = (&tiles[i-width]);
            tiles[i].neighbors[2] = (&tiles[i-width+1]);
            tiles[i].neighbors[3] = (&tiles[i-1]);
            tiles[i].neighbors[4] = (&tiles[i+1]);
            for(int j = 0; j < 3; j++)
                tiles[i].neighbors[j+5] = (nullptr);
        }
        else if(i%width == width-1){
            tiles[i].neighbors[0]= (&tiles[i-width-1]);
            tiles[i].neighbors[1]=(&tiles[i-width]);
            tiles[i].neighbors[2] = (nullptr);
            tiles[i].neighbors[3] = (&tiles[i-1]);
            tiles[i].neighbors[4] = (nullptr);
            tiles[i].neighbors[5] = (&tiles[i+width-1]);
            tiles[i].neighbors[6] = (&tiles[i+width]);
            tiles[i].neighbors[7] = (nullptr);
        }
        else{
            tiles[i].neighbors[0] = (&tiles[i-width-1]);
            tiles[i].neighbors[1] = (&tiles[i-width]);
            tiles[i].neighbors[2] = (&tiles[i-width+1]);
            tiles[i].neighbors[3] = (&tiles[i-1]);
            tiles[i].neighbors[4] = (&tiles[i+1]);
            tiles[i].neighbors[5] = (&tiles[i+width-1]);
            tiles[i].neighbors[6] = (&tiles[i+width]);
            tiles[i].neighbors[7] = (&tiles[i+width+1]);
        }
    }
}
int Board::GetHeight() const {
    return this->height;
}
int Board::GetWidth() const {
    return this->width;
}
sf::Sprite & Board::GetFlag(int num) {
    if(num == -1)
        return flagNeg;
    else if(num == 0)
        return flag0;
    else if(num == 1)
        return flag1;
    else if(num == 2)
        return flag2;
    else if(num == 3)
        return flag3;
    else if(num == 4)
        return flag4;
    else if(num == 5)
        return flag5;
    else if(num == 6)
        return flag6;
    else if(num == 7)
        return flag7;
    else if(num == 8)
        return flag8;
    else if(num == 9)
        return flag9;
    else{
        cout << num << endl;
    }
}
void Board::UpdateFlagCounter() {
    if(flagCounter >= 0){
        int hundreds = flagCounter/100;
        flagHundreds = GetFlag(hundreds);
        int tens = (flagCounter/10)%10;
        flagTens = GetFlag(tens);
        int ones = (flagCounter%100)%10;
        flagOnes = GetFlag(ones);
    }
    else{
        flagHundreds = GetFlag(-1);
        int tens = (flagCounter*-1)/100;
        flagTens = GetFlag(tens);
        int ones = ((flagCounter*-1)/10)%10;
        flagOnes = GetFlag(ones);
        int sign = ((flagCounter*-1)%100)%10;
        flagSign = GetFlag(sign);
    }
}
