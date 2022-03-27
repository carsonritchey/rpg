#include "conf.h"
#include "game.h"

Game::Game() {
    this->running = true;

    this->videoMode.width = WINDOW_WIDTH;
    this->videoMode.height = WINDOW_HEIGHT;
    this->window = new sf::RenderWindow(this->videoMode, "rpg filler", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(FRAMES_PER_SECOND);
    this->window->setVerticalSyncEnabled(VSYNC_CHOICE);
}

Game::~Game() {
   delete this->window;
}

void Game::close() {
    this->running = false;

    this->window->close();
}

void Game::update() {

}

void Game::render() {
    
}
