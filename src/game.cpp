#include "conf.h"
#include "game.h"

#include <string>

Game::Game() {
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Titlebar | sf::Style::Close);
    this->view   = new sf::View(sf::FloatRect(0.f, 0.f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));

    this->window->setFramerateLimit(FRAMES_PER_SECOND);
    this->window->setVerticalSyncEnabled(VSYNC_CHOICE);

    // initial scene
    //this->scenes.push(new TitleScene(this->window));
    this->scenes.push(new GameScene(this->window, this->view));
    //this->scenes.push(new BattleScene(this->window));
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
	sf::Event event;
	while(this->window->pollEvent(event)) {
		if(event.type == sf::Event::Closed) {
			this->close();
			return;
		}

        // most classes only need a single keypress, so a single event is passed to their update(),
        // but Player requires high fidelity input so it's handled here 
        if(event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
            GameScene* gamescene_ref = dynamic_cast<GameScene*>(this->scenes.top());
            BattleScene* battlescene_ref = dynamic_cast<BattleScene*>(this->scenes.top());

            if(gamescene_ref != nullptr) { // if top scene is a GameScene
                gamescene_ref->player.processEvent(&event);

                need_view = true;
            }
            else if(battlescene_ref != nullptr) { // if top scene is a BattleScene
                battlescene_ref->processEvent(&event); 

                need_view = false;
            }

            if(event.key.code == sf::Keyboard::B && gamescene_ref != nullptr)
                this->scenes.push(new BattleScene(this->window, this->view, gamescene_ref->player.party));

            if(event.key.code == sf::Keyboard::P && this->scenes.size() != 1)
                this->scenes.pop();
        }
	}

    // calls update() of top scene
    if(!this->scenes.empty()) {
        // uses last event detected 
        int code = this->scenes.top()->update(this->dt, &event);

        if(code == RETURN_CODE_EXIT) this->close(); 
        else if(code == RETURN_CODE_START) this->scenes.push(new GameScene(this->window, this->view));
    }

    global_tick++;
}

void Game::render() {
    this->window->clear();

    if(!this->scenes.empty())
        this->scenes.top()->render();

    if(need_view) // if the screen needs to scroll then set the view (i.e. a gamescene)
        this->window->setView(*this->view);

    this->window->display();
}
