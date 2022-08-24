#include "GameManager.h"

void GameManager::Run() {
    canClick = true;
    ReadBoard();
    sf::RenderWindow window(sf::VideoMode(mainBoard.GetWidth()*32, mainBoard.GetHeight()*32+88), "Dont hit the Mines!");
    mainBoard.CreateGameBoard();



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left) {
                    auto mousePos = sf::Mouse::getPosition(window);
                    if (mainBoard.specialButtons[2].inside.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        mainBoard.CreateTest1Board();
                        canClick = true;
                    }
                    else if (mainBoard.specialButtons[3].inside.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        mainBoard.CreateTest2Board();
                        canClick = true;
                    }
                    else if (mainBoard.specialButtons[4].inside.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        mainBoard.CreateTest3Board();
                        canClick = true;
                    }
                    else if(mainBoard.specialButtons[1].inside.getGlobalBounds().contains(mousePos.x, mousePos.y) && canClick)
                        mainBoard.ToggleDebugBoard();
                    else if(mainBoard.specialButtons[0].inside.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        mainBoard.Restart();
                        canClick = true;
                    }
                    else if(mainBoard.TileExists(mousePos.x/32,mousePos.y/32) && !mainBoard.TileAt(mousePos.x/32, mousePos.y/32).isFlagged && canClick) {
                        Tile test = mainBoard.TileAt(mousePos.x/32, mousePos.y/32);
                        mainBoard.RecursiveReveal(mousePos.x/32, mousePos.y/32);
                        if(mainBoard.TileAt(mousePos.x/32, mousePos.y/32).isMine){
                            Lose(mainBoard);
                        }
                        if(mainBoard.WinCheck()){
                            Win(mainBoard);
                        }
                    }


                }
                if(event.mouseButton.button == sf::Mouse::Right){
                    auto mousePos = sf::Mouse::getPosition(window);
                    mainBoard.FlagToggle(mousePos.x/32, mousePos.y/32);
                    if(mainBoard.WinCheck()){
                        Win(mainBoard);
                    }
                    mainBoard.UpdateFlagCounter();
                }
            }
        }

        window.clear();
        mainBoard.DrawGameBoard(window);
        window.display();

    }
    TextureManager::Clear();
}
void GameManager::Lose(Board& board){
    board.Lose();
    canClick = false;
}
void GameManager::Win(Board& board){
    board.Win();
    canClick = false;
}
void GameManager::ReadBoard() {
    ifstream inFile("boards/config.cfg");
    string lineFromFile;

    getline(inFile, lineFromFile);
    int width = stoi(lineFromFile);

    getline(inFile, lineFromFile);
    int height = stoi(lineFromFile);

    getline(inFile, lineFromFile);
    int mineCount = stoi(lineFromFile);

    mainBoard = Board(width,height,mineCount);
}
