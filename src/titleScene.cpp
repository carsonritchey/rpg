#include "titleScene.h"
#include "conf.h"
#include "map.h"

sf::Color selected_color(0xff, 0x66, 0xff, 255);

TitleScene::TitleScene(sf::RenderWindow* window) : Scene(window) {
    this->map.init(this->map_path, this->texture_path);

    int font_size = TILE_SIZE * ZOOM_FACTOR;

	this->font.loadFromFile("art/PressStart2P.ttf");
    // disable anti-aliasing hack 
    const_cast<sf::Texture&>(font.getTexture(font_size)).setSmooth(false);
    
	this->text.setFont(font);
    this->text_backdrop.setFont(font);
    this->version_text.setFont(font);
    this->start_text.setFont(font);
    this->exit_text.setFont(font);

	this->text.setString(WINDOW_NAME);
	this->text_backdrop.setString(WINDOW_NAME);
    this->version_text.setString(VERSION);
    this->start_text.setString(this->start_string);
    this->exit_text.setString(this->exit_string);

	this->text.setCharacterSize(font_size);
	this->text_backdrop.setCharacterSize(font_size);
    this->version_text.setCharacterSize(TILE_SIZE * ZOOM_FACTOR / 4);
    this->start_text.setCharacterSize(TILE_SIZE * ZOOM_FACTOR / 2);
    this->exit_text.setCharacterSize(TILE_SIZE * ZOOM_FACTOR / 2);

	this->text.setStyle(sf::Text::Bold);
	this->text_backdrop.setStyle(sf::Text::Bold);

    this->text_backdrop.setFillColor(sf::Color::Black);

	this->text.setPosition(2 * TILE_SIZE * ZOOM_FACTOR, 1 * TILE_SIZE * ZOOM_FACTOR);
	this->text_backdrop.setPosition(2 * TILE_SIZE * ZOOM_FACTOR + 5, 1 * TILE_SIZE * ZOOM_FACTOR - 5);
    this->version_text.setPosition(((WINDOW_WIDTH / (TILE_SIZE * ZOOM_FACTOR)) - 3) * TILE_SIZE * ZOOM_FACTOR, 0);
    this->start_text.setPosition(4 * TILE_SIZE * ZOOM_FACTOR, 3 * TILE_SIZE * ZOOM_FACTOR);
    this->exit_text.setPosition(4 * TILE_SIZE * ZOOM_FACTOR, 4 * TILE_SIZE * ZOOM_FACTOR);
}

TitleScene::~TitleScene() {

}

int TitleScene::update(const float& dt, const sf::Event* event) {
    if(text_select == 0) {
        this->start_text.setFillColor(selected_color);
        this->exit_text.setFillColor(sf::Color::White);
    } else {
        this->exit_text.setFillColor(selected_color);
        this->start_text.setFillColor(sf::Color::White);
    }

    if(event->type == sf::Event::KeyPressed) {
        if(event->key.code == sf::Keyboard::Up) text_select = (text_select - 1) % 2;
        else if(event->key.code == sf::Keyboard::Down) text_select = (text_select + 1) % 2;
         if(event->key.code == sf::Keyboard::Right) {
            if(text_select == 0) return RETURN_CODE_START;
            else if(text_select == 1) return RETURN_CODE_EXIT;
        }
    }


    return RETURN_CODE_NOTHING;
}

void TitleScene::render() {
    this->map.drawMap(window, 0, 0);

    window->draw(this->text_backdrop);
	window->draw(this->text);
    window->draw(this->version_text);
    window->draw(this->start_text);
    window->draw(this->exit_text);
}

void TitleScene::close_scene() {
    
}
