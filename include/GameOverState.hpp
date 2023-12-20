#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "State.hpp"
#include "Game.hpp"

namespace omi
{
    class GameOverState : public State{
        public:
            GameOverState(GameDataRef data);

            void Init();

            void HandleInput();
            void Update(float dt);
            void Draw(float dt);

        private:
            sf::Sprite background;
            sf::Sprite title;
            sf::Sprite body;
            sf::Text game_score;
            sf::Text best_score;
            GameDataRef data;
    };
}
