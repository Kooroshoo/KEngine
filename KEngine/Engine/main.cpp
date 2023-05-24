#include <SFML/Graphics.hpp>

#include "GameEngine.h"
#include "../Games/ContentMenu/GameState_Menu.h"


int main()
{
    GameEngine game;

    // add assets before loading the GameState(Map)
    game.addAssets("Games/ContentMenu/assets.txt"); 

    game.init(sf::VideoMode(1280, 780), "Game", 60, std::make_shared<GameState_Menu>(game));

    game.run();
}