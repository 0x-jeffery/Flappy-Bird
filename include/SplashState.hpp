#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "State.hpp"
#include "Game.hpp"

namespace omi
{
    class SplashState : public State{
        public:
            SplashState(GameDataRef data);

            void Init();

            void HandleInput();
            void Update(float dt);
            void Draw(float dt);

        private:
            GameDataRef data;
            bool skipped = false;
            sf::Clock clock;
            sf::Sprite background;
            sf::Texture background_texture;
    };
}
