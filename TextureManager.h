#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class TextureManager{
    //static means only one of these in memory ever
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string name); //LoadTexture("space")
    static void LoadPartOfTexture(string name, int startingPos);
public:

    static sf::Texture& GetTexture(string textureName);
    static sf::Texture& GetPartOfTexture(string textureName, int &startingPos);
    static void Clear();
};