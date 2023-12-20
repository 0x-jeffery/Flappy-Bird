#pragma once

#include "Game.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace flappy {
    class Land {
        public:
            Land (GameDataRef data);
            void MoveLand( float dt );
            void DrawLand();
            std::vector<sf::Sprite> Sprites();

        private:
            GameDataRef data;
            std::vector<sf::Sprite> land_sprites;
    };
}
