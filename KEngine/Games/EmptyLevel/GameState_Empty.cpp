#include "GameState_Empty.h"

#include "../../Games/Zelda/GameState_Play.h"
#include "../../Engine/Common.h"
#include "../../Engine/Assets.h"
#include "../../Engine/GameEngine.h"
#include "../../Engine/Components.h"

GameState_Empty::GameState_Empty(GameEngine & game)
    : GameState(game)
{
    init("");
}

void GameState_Empty::init(const std::string & menuConfig)
{

}

void GameState_Empty::update()
{
    m_entityManager.update();

    sUserInput();
    sRender();
}

void GameState_Empty::sUserInput()
{
    sf::Event event;
    while (m_game.window().pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_game.quit();
        }
        // this event is triggered when a key is pressed
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Escape: { m_game.popState(); break; }

            }
        }
    }

}

void GameState_Empty::sRender()
{
    // clear the window to a blue
    m_game.window().setView(m_game.window().getDefaultView());
    m_game.window().clear(sf::Color(0, 0, 224));

    m_game.window().display();
}