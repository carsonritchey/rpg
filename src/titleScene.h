#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include "map.h"

class TitleScene : public Scene {
    private:
		sf::Font font;
		sf::Text text;
		sf::Text text_backdrop;
        sf::Text version_text;

    public:
		// functions 
        TitleScene(sf::RenderWindow* window);
        virtual ~TitleScene();

        void update(const float& dt, const sf::Event* event);
        void render();
        void close_scene();

		// variables 
        Map map;

        std::string texture_path = "art/tiles/overworld.png";
        std::string map_path = "lvledit/title_map.dat";
};

#endif
