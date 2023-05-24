#pragma once

#include "Common.h"
#include "GameState.h"
#include "Assets.h"

#include <memory>

class GameEngine
{

protected:

    std::vector<std::shared_ptr<GameState>> m_states;
    std::vector<std::shared_ptr<GameState>> m_statesToPush;
    sf::RenderWindow                        m_window;
    Assets                                  m_assets;
    size_t                                  m_popStates = 0;
    bool                                    m_running = true;

    
    void update();

    

public:
    
    GameEngine();

    void init(sf::VideoMode resolution, const std::string& title, const int fps, std::shared_ptr<GameState> state);

    void pushState(std::shared_ptr<GameState> state);
    void popState();

    void quit();
    void run();

    sf::RenderWindow & window();
    bool isRunning();

    void addAssets(const std::string& path);
    const Assets & getAssets() const;
};