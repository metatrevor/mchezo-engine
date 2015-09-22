#include "Game.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GameOverState.h"


Game::Game()
{
}

bool Game::init()
{
    m_level = new Level();

    m_level->parseLevel("assets/textures/map1.tmx");

    TextureManager::instance().loadTexture("animate", "assets/textures/player.png");
    TextureManager::instance().loadTexture("enemy", "assets/textures/enemy.png");
    m_objects.push_back(new Player(500, 100, 128, 55, "animate"));
    m_objects.push_back(new Enemy(100, 100, 128, 55, "enemy"));
    m_stateName = "GAME";
    Log::Info("Entering Gamestate...");
    return true;
}

void Game::run()
{
    State::run();
}

void Game::handleEvents()
{
    State::handleEvents();
    if (InputManager::instance().isKeyDown(SDL_SCANCODE_ESCAPE)) {
        gameToPause();
    }

}

void Game::render()
{
    TextureManager::instance().getWindow()->clearRenderer();
    m_level->render();
    std::vector<Object *>::size_type i;
    for (i = 0; i < m_objects.size(); i++) {
        m_objects[i]->draw();
    }
    TextureManager::instance().getWindow()->updateWindow();
}

void Game::update()
{
    //State::update();
    if (testCollision(dynamic_cast<Object *>(m_objects[0]), dynamic_cast<Object *>(m_objects[1]))) {
        StateMachine::instance().pop();
        StateMachine::instance().push(new GameOverState());
    }
    m_level->update();
}

void Game::exit()
{
    Log::Info("Exiting Gamestate...");
}

void Game::gameToPause()
{
    StateMachine::instance().push(new PauseState());
}

bool Game::testCollision(Object *obj1, Object *obj2)
{
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    //Get the sides of the first object

    left1 = (int) obj1->getPosition().getX();
    right1 = left1 + obj1->getWidth();
    top1 = (int) obj1->getPosition().getY();
    bottom1 = top1 + obj1->getHeight();

    //Get the sides of the second object
    left2 = (int) obj2->getPosition().getX();
    right2 = left2 + obj2->getWidth();
    top2 = (int) obj2->getPosition().getY();
    bottom2 = top2 + obj2->getHeight();

    if (bottom1 <= top2) { return false; }
    if (top1 >= bottom2) { return false; }
    if (right1 <= left1) { return false; }
    if (left1 >= right2) { return false; }
    return true;
}


int Game::getGameWidth() const
{
    return m_gameWidth;
}

int Game::getGameHeight() const
{
    return m_gameHeight;
}
