#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "State.hpp"
#include "Game.hpp"

namespace omi
{
    class MainMenuState : public State{
        public:
            MainMenuState(GameDataRef data);
            void Init();
            void HandleInput();
            void Update(float dt);
            void Draw(float dt);
            void Pause();
            void Resume();

        private:
            GameDataRef data;
            sf::Sprite background;
            sf::Sprite title;
            sf::Sprite play_button;
    };
}
