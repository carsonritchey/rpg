#include "titleScene.h"
#include "conf.h"
#include "map.h"
#include "player.h"

Player player("art/sprites/among.png");

TitleScene::TitleScene(sf::RenderWindow* window) : Scene(window) {
    this->map.init(this->map_path, this->texture_path);

    int font_size = TILE_SIZE * ZOOM_FACTOR;

	this->font.loadFromFile("art/PressStart2P.ttf");
    // disable anti-aliasing hack 
    const_cast<sf::Texture&>(font.getTexture(font_size)).setSmooth(false);
    
	this->text.setFont(font);
    this->text_backdrop.setFont(font);
    this->version_text.setFont(font);

	this->text.setString(WINDOW_NAME);
	this->text_backdrop.setString(WINDOW_NAME);
    this->version_text.setString(VERSION);

	this->text.setCharacterSize(font_size);
	this->text_backdrop.setCharacterSize(font_size);
    this->version_text.setCharacterSize(TILE_SIZE * ZOOM_FACTOR / 4);

	this->text.setStyle(sf::Text::Bold);
	this->text_backdrop.setStyle(sf::Text::Bold);

    this->text_backdrop.setFillColor(sf::Color::Black);

	this->text.setPosition(2 * TILE_SIZE * ZOOM_FACTOR, 1 * TILE_SIZE * ZOOM_FACTOR);
	this->text_backdrop.setPosition(2 * TILE_SIZE * ZOOM_FACTOR + 5, 1 * TILE_SIZE * ZOOM_FACTOR - 5);
    this->version_text.setPosition(((WINDOW_WIDTH / (TILE_SIZE * ZOOM_FACTOR)) - 3) * TILE_SIZE * ZOOM_FACTOR, 0);
}

TitleScene::~TitleScene() {

}

void TitleScene::update(const float& dt, const sf::Event* event) {
	player.update(event);
}

void TitleScene::render() {
    this->map.drawMap(window, 0, 0);

    window->draw(this->text_backdrop);
	window->draw(this->text);
    window->draw(this->version_text);

	window->draw(player.sprite);
}

void TitleScene::close_scene() {
    
}
