#pragma once

#include "Pipe.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Land.hpp"
#include "Bird.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace flappy
{
    class GameState : public State{
        public:
            GameState(GameDataRef data);

            void Init();
            void HandleInput();
            void Update(float dt);
            void Draw(float dt);
            void Pause();
            void Mute();

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
            bool muted = false;

            bool ExistsEndingCollision();
            bool ExistsScoringCollision();
            void SettleHighScores(int score);
    };
}
