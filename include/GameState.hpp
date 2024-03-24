#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Pipe.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Land.hpp"
#include "Bird.hpp"

namespace flappy
{
    class GameState : public State {
        public:
            GameState(GameDataRef data);

            void Init();
            void HandleInput();
            void Update(float dt);
            void Draw(float dt);
            void Pause();
            void Mute();
            void Quit();

        private:
            sf::Clock clock;
            GameDataRef data;
            Bird *bird;
            Land *land;
            Pipe *pipe;
            sf::Sprite background;
            sf::Sound hit_sound, flap_sound, score_sound;
            sf::Text score_text;
            float speed;
            bool paused, muted = false;

            bool ExistsEndingCollision();
            bool ExistsScoringCollision();
            void SettleHighScores(int score);
    };
}
