#include "conf.h"
#include "game.h"

Game::Game() {
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Titlebar | sf::Style::Close);
    this->view   = new sf::View(sf::FloatRect(0.f, 0.f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));

    this->window->setFramerateLimit(FRAMES_PER_SECOND);
    this->window->setVerticalSyncEnabled(VSYNC_CHOICE);

    // initial scene
    //this->scenes.push(new TitleScene(this->window));
    this->scenes.push((this->gamescene = new GameScene(this->window, this->view)));
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
        // but classes like Player requires high fidelity input so it's handled here 
        if(event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
            if(scenes.top() == gamescene && gamescene != nullptr) {
                gamescene->player.processEvent(&event);
            }
            else if(scenes.top() == battlescene && battlescene != nullptr) {
                battlescene->processEvent(&event); 
            }

            if(event.key.code == sf::Keyboard::B && gamescene != nullptr)
                this->scenes.push((this->battlescene = new BattleScene(this->window, this->view, gamescene->player.party)));

            if(event.key.code == sf::Keyboard::P && this->scenes.size() != 1)
                this->scenes.pop();
        }
	}

    // calls update() of top scene
    if(!this->scenes.empty()) {
        // uses last event detected 
        int code = this->scenes.top()->update(this->dt, &event);

        if(code == RETURN_CODE_EXIT) this->close(); 
        else if(code == RETURN_CODE_START) this->scenes.push((this->gamescene = new GameScene(this->window, this->view)));
        else if(code == RETURN_CODE_BATTLESCENE) this->scenes.push((this->battlescene = new BattleScene(this->window, this->view, this->gamescene->player.party)));
        else if(code == RETURN_CODE_BATTLESCENE_RUN && battlescene != nullptr) this->scenes.pop();
    }

    global_tick++;
}

void Game::render() {
    this->window->clear();

    this->window->setView(*this->view);

    if(!this->scenes.empty())
        this->scenes.top()->render();

    this->window->display();
}
