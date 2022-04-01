#include "conf.h"
#include "game.h"

Game::Game() {
    this->running = true;
    this->dt = 0.f;

    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Titlebar | sf::Style::Close);
    this->view   = new sf::View(sf::FloatRect(0.f, 0.f, (float)WINDOW_WIDTH / ZOOM_FACTOR, (float)WINDOW_HEIGHT / ZOOM_FACTOR));

    this->window->setFramerateLimit(FRAMES_PER_SECOND);
    this->window->setVerticalSyncEnabled(VSYNC_CHOICE);

    // initial scene
    this->scenes.push(new TitleScene(this->window));
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

// how long the previous frame took
void Game::tick_dt() {
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::update() {
    if(!this->scenes.empty())
        this->scenes.top()->update(this->dt);

	
	// temp scene moving 
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->view->move(-TILE_SIZE, 0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->view->move(TILE_SIZE, 0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->view->move(0, -TILE_SIZE);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->view->move(0, TILE_SIZE);
}

void Game::render() {
    this->window->clear();
    this->window->setView(*this->view);

    if(!this->scenes.empty())
        this->scenes.top()->render();

    this->window->display();
}
