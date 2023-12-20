#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "DEFINITIONS.hpp"

namespace omi{
    class Pipe{
        public:
            std::vector<sf::Sprite> pipe_sprites;
            std::vector<sf::RectangleShape> score_boxes;
            
            Pipe(GameDataRef data);
            
            void SpawnPipes();
            void MovePipes( float dt );
            void DrawPipes();
            void RandomizeOffset();

        private:
            GameDataRef data;
            unsigned short int offset;

            void SpawnBottomPipe();
            void SpawnTopPipe();
            void SpawnScorePipe();
    };
}
