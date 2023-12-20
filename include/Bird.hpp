#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "DEFINITIONS.hpp"

namespace omi
{
    class Bird{
        public:
            Bird(GameDataRef data);
            sf::Sprite bird_sprite;
            void DrawBird();
            bool IsWithinBounds();
            bool IntersectsWith(sf::FloatRect float_rect);
            void Jump();
            void MoveBird( float dt );

        private:
            GameDataRef data;
            bool jump;
            float y_velocity;
    };
}
