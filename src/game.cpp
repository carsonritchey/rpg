#include "conf.h"
#include "game.h"

Game::Game() {
    this->running = true;
    this->dt = 0.f;

    this->videoMode.width = WINDOW_WIDTH;
    this->videoMode.height = WINDOW_HEIGHT;
    this->window = new sf::RenderWindow(this->videoMode, "rpg filler", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(FRAMES_PER_SECOND);
    this->window->setVerticalSyncEnabled(VSYNC_CHOICE);
}

// frees memory
Game::~Game() {
   delete this->window;
}

void Game::close() {
    this->running = false;

    this->window->close();

    while(!this->scenes.empty())
        this->scenes.pop();
}

// how long the previous fram took
void Game::tick_dt() {
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::update() {

}

void Game::render() {
    // clears screen
    this->window->clear();

    // calls render() for current scene
    if(!this->scenes.empty())
        this->scenes.top()->render();

    // displays render to screen
    this->window->display();
}
