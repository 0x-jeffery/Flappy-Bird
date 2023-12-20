#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

namespace omi {
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
