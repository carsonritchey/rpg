#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "scene.h"
#include "map.h"

class TitleScene : public Scene {
    private:
		sf::Font font;
		sf::Text text;
		sf::Text text_backdrop;
        sf::Text version_text;

        std::string start_string = "start game!";
        sf::Text start_text;
        std::string exit_string = "exit";
        sf::Text exit_text;

        int text_select = 0;

    public:
		// functions 
        TitleScene(sf::RenderWindow* window);
        virtual ~TitleScene();

        int update(const float& dt, const sf::Event* event);
        void render();
        void close_scene();

		// variables 
        Map map;

        std::string texture_path = "art/tiles/overworld.png";
        std::string map_path = "lvledit/title_map.dat";
};

#endif
