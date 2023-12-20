#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Pipe.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Land.hpp"
#include "Bird.hpp"
#include "GameOverState.hpp"

namespace omi
{
    class GameState : public State{
        public:
            GameState(GameDataRef data);

            void Init();
            void HandleInput();
            void Update(float dt);
            void Draw(float dt);
            void Pause();
            void Resume();

        private:
            sf::Clock clock;
            GameDataRef data;
            Bird *bird;
            Land *land;
            Pipe *pipe;
            sf::Sprite background;
            sf::Sound hit_sound;
            sf::Sound flap_sound;
            sf::Sound score_sound;
            sf::Text score_text;
            float speed;
            bool paused;

            bool ExistsEndingCollision();
            bool ExistsScoringCollision();
    };
}
