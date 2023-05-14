#include <SFML/Graphics.hpp>

#include "GameEngine.h"

int main()
{
    GameEngine g("Games/ContentMenu/assets.txt");
    g.run();
}