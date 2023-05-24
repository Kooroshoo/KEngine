#include "GameEngine.h"


GameEngine::GameEngine()
{
}

void GameEngine::init(sf::VideoMode resolution, const std::string& title, const int fps, std::shared_ptr<GameState> state)
{
    m_window.create(resolution, title);
    m_window.setFramerateLimit(fps);

    pushState(state);
}

bool GameEngine::isRunning()
{ 
    return m_running & m_window.isOpen();
}

sf::RenderWindow & GameEngine::window()
{
    return m_window;
}

void GameEngine::run()
{
    while (isRunning())
    {
        update();
    }
}

void GameEngine::pushState(std::shared_ptr<GameState> state)
{
    m_statesToPush.push_back(state);
}

void GameEngine::popState()
{
    m_popStates++;
}

void GameEngine::update()
{
    if (!isRunning()) { return; }
    
    // pop however many states off the state stack as we have requested
    for (size_t i = 0; i < m_popStates; i++)
    {
        if (!m_states.empty())
        {
            m_states.pop_back();
        }
    }
    // reset the state stack pop counter
    m_popStates = 0;

    // push any requested states onto the stack
    for (size_t i = 0; i < m_statesToPush.size(); i++)
    {
        m_states.push_back(m_statesToPush[i]);
    }
    m_statesToPush.clear();

    // call update on the top of the stack (current state)
    if (!m_states.empty())
    {
        m_states.back()->update();
    }
}

void GameEngine::quit()
{
    m_running = false;
}

void GameEngine::addAssets(const std::string& path) 
{
    m_assets.loadFromFile(path);
}

const Assets & GameEngine::getAssets() const
{
    return m_assets;
}