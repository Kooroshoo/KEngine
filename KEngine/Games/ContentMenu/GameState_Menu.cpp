#include "GameState_Menu.h"

#include "../../Games/Zelda/GameState_Play.h"
#include "../EmptyLevel/GameState_Empty.h"
#include "../../Engine/Common.h"
#include "../../Engine/Assets.h"
#include "../../Engine/GameEngine.h"
#include "../../Engine/Components.h"

GameState_Menu::GameState_Menu(GameEngine & game)
    : GameState(game)
{
    init("");
}

void GameState_Menu::init(const std::string & menuConfig)
{
    m_title = "Content Examples";
    m_menuStrings.push_back("Empty Level");
    m_menuStrings.push_back("Zelda");
    m_menuStrings.push_back("Mario");

    m_levelPaths.push_back("");
    m_levelPaths.push_back("Games/Zelda/level1.txt");
    m_levelPaths.push_back("");

    m_menuText.setFont(m_game.getAssets().getFont("Hylia"));
    m_menuText.setCharacterSize(64);
}

void GameState_Menu::update()
{
    m_entityManager.update();

    sUserInput();
    sRender();
}

void GameState_Menu::sUserInput()
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
                case sf::Keyboard::Escape: 
                { 
                    m_game.quit(); 
                    break; 
                }
                case sf::Keyboard::W: 
                {
                    if (m_selectedMenuIndex > 0) { m_selectedMenuIndex--; }
                    else { m_selectedMenuIndex = m_menuStrings.size() - 1; }
                    break;
                }
                case sf::Keyboard::S: 
                { 
                    m_selectedMenuIndex = (m_selectedMenuIndex + 1) % m_menuStrings.size(); 
                    break; 
                }
                case sf::Keyboard::D: 
                { 
                    if (m_selectedMenuIndex == 0)
                    {
                        m_game.pushState(std::make_shared<GameState_Empty>(m_game));
                    }
                    else
                    {
                        m_game.pushState(std::make_shared<GameState_Play>(m_game, m_levelPaths[m_selectedMenuIndex]));
                    }
                    break; 
                }
            }
        }
    }

}

void GameState_Menu::sRender()
{
    // clear the window to a White
    m_game.window().setView(m_game.window().getDefaultView());
    m_game.window().clear(sf::Color(253, 255, 224));

    // draw the game title in the top-left of the screen
    m_menuText.setCharacterSize(48);
    m_menuText.setString(m_title);
    m_menuText.setFillColor(sf::Color::Black);
    m_menuText.setPosition(sf::Vector2f(10, 10));
    m_game.window().draw(m_menuText);
    
    // draw all of the menu options
    for (size_t i = 0; i < m_menuStrings.size(); i++)
    {
        m_menuText.setString(m_menuStrings[i]);
        m_menuText.setFillColor(i == m_selectedMenuIndex ? sf::Color::Black : sf::Color(100, 100, 100));
        m_menuText.setPosition(sf::Vector2f(10, 110 + i * 72));
        m_game.window().draw(m_menuText);
    }

    // draw the controls in the bottom-left
    m_menuText.setCharacterSize(20);
    m_menuText.setFillColor(sf::Color(100, 100, 100));
    m_menuText.setString("up: w     down: s    play: d      back: esc");
    m_menuText.setPosition(sf::Vector2f(10, 730));
    m_game.window().draw(m_menuText);

    m_game.window().display();
}