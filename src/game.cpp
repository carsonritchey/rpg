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

// not pretty code because it shouldn't be running anyways
void Game::drawDebugInfo() {
    for(int i = 0; i < WINDOW_WIDTH; i += TILE_SIZE * ZOOM_FACTOR) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(i, 0)),
            sf::Vertex(sf::Vector2f(i, WINDOW_HEIGHT))
        };
        this->window->draw(line, 2, sf::Lines);
    }

    for(int j = 0; j < WINDOW_HEIGHT; j += TILE_SIZE * ZOOM_FACTOR) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, j)),
            sf::Vertex(sf::Vector2f(WINDOW_WIDTH, j))
        };
        this->window->draw(line, 2, sf::Lines);
    }

    sf::Font font;
    font.loadFromFile("art/PressStart2P.ttf");
    sf::Text text;
    text.setFont(font);
    std::string s("fps:");
    char fps[64];
    sprintf(fps, "%.2f\n", 1 / this->dt);
    s += fps;

    text.setString(s);
    text.setFillColor(sf::Color(0, 0, 0, 255 / 2));
    text.setCharacterSize(TILE_SIZE * ZOOM_FACTOR / 4);

    this->window->draw(text);
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

            if(event.key.code == sf::Keyboard::B)
                this->scenes.push(new BattleScene(this->window));
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

    if(this->debug)
        this->drawDebugInfo();

    if(need_view) // if the screen needs to scroll then set the view (i.e. a gamescene)
        this->window->setView(*this->view);

    this->window->display();
}
