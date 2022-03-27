#include "game.h"

Game::Game() {
    this->running = true;

    this->videoMode.width = 800;
    this->videoMode.height = 600;
    this->window = new sf::RenderWindow(this->videoMode, "rpg filler", sf::Style::Titlebar | sf::Style::Close);
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
