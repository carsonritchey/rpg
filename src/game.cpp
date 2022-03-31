#include "conf.h"
#include "game.h"

Game::Game() {
    this->running = true;
    this->dt = 0.f;

    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "rpg filler", sf::Style::Titlebar | sf::Style::Close);
    this->view   = new sf::View(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), sf::Vector2f(WINDOW_WIDTH / ZOOM_FACTOR, WINDOW_HEIGHT / ZOOM_FACTOR));

    this->window->setFramerateLimit(FRAMES_PER_SECOND);
    this->window->setVerticalSyncEnabled(VSYNC_CHOICE);

    // initial scene
    this->scenes.push(new GameScene(this->window));
}

// frees memory
Game::~Game() {
   delete this->window;
   delete this->view;
}

void Game::close() {
    this->running = false;

    this->window->close();

    while(!this->scenes.empty()) {
        delete this->scenes.top();
        this->scenes.pop();
    }
}

// how long the previous fram took
void Game::tick_dt() {
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::update() {
    if(!this->scenes.empty())
        this->scenes.top()->update(this->dt);
}

void Game::render() {
    this->window->clear();
    this->window->setView(*this->view);

    if(!this->scenes.empty())
        this->scenes.top()->render();

    this->window->display();
}
