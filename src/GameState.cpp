#include "GameOverState.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

namespace flappy
{
    GameState::GameState(GameDataRef data) : data(data){ }

    void GameState::Init(){
        this->data->game_score = 0;
        this->paused = 0;
        this->speed = 0;

        this->data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);
        this->data->assets.LoadFont("Marker Font", MARKER_FONT_FILEPATH);
        this->data->assets.LoadTexture("Game State Background", GAME_BACKGROUND_FILEPATH);
        this->data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
        this->data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
        this->data->assets.LoadTexture("Land", LAND_FILEPATH);
        this->data->assets.LoadTexture("Bird Frame 1", BIRD_1_FILEPATH);
        this->data->assets.LoadTexture("Bird Frame 2", BIRD_2_FILEPATH);
        this->data->assets.LoadTexture("Bird Frame 3", BIRD_3_FILEPATH);
        this->data->assets.LoadSoundBuffer("Hit Sound", HIT_SOUND_FILEPATH);
        this->data->assets.LoadSoundBuffer("Flap Sound", FLAP_SOUND_FILEPATH);
        this->data->assets.LoadSoundBuffer("Score Sound", POINT_SOUND_FILEPATH);

        this->bird = new Bird(this->data);
        this->land = new Land(this->data);
        this->pipe = new Pipe(this->data);

        this->background.setTexture(this->data->assets.GetTexture("Game State Background"));
        this->hit_sound.setBuffer(this->data->assets.GetSoundBuffer("Hit Sound"));
        this->flap_sound.setBuffer(this->data->assets.GetSoundBuffer("Flap Sound"));
        this->score_sound.setBuffer(this->data->assets.GetSoundBuffer("Score Sound"));

        this->score_text.setFont(this->data->assets.GetFont("Flappy Font"));
        this->score_text.setCharacterSize(SCORE_FONT_SIZE);
        this->score_text.setOrigin(this->score_text.getGlobalBounds().width/2, this->score_text.getGlobalBounds().height/2);
        this->score_text.setPosition(int(SCREEN_WIDTH/2), 10);

        this->keybinds.setFont(this->data->assets.GetFont("Marker Font"));
        this->keybinds.setString("SPACE = Jump \nP = Toggle Pause \nM = Toggle Mute\nQ = Quit");
        this->keybinds.setPosition(10, int(SCREEN_HEIGHT/2)+300);
        this->keybinds.setFillColor(sf::Color::Black);

        this->speed_text.setFont(this->data->assets.GetFont("Marker Font"));
        this->speed_text.setPosition(int(SCREEN_WIDTH)-150, int(SCREEN_HEIGHT/2)+300);
        this->speed_text.setFillColor(sf::Color::Black);
    }

    void GameState::HandleInput(){
        sf::Event event;

        while(this->data->window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    this->data->window.close();
                    break;
                
                case sf::Event::KeyPressed:
                    switch(event.key.code){
                        case sf::Keyboard::Space:{
                            if(!muted) this->flap_sound.play();
                            this->bird->Jump();
                            break;
                        }
                        case sf::Keyboard::Q:           // Quit
                            this->data->window.close();
                            break;
                        case sf::Keyboard::P:           // Pause
                            Pause();
                            break;
                        case sf::Keyboard::M:           // Mute
                            Mute();
                            break;
                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
    }

    void GameState::Update(float dt){
        if(!this->paused) {

            if(ExistsScoringCollision()){
                if(!muted) this->score_sound.play();
                this->data->game_score++;
                this->speed += 0.05;
            }

            if(ExistsEndingCollision()){
                if(!muted) this->hit_sound.play();
                SettleHighScores(this->data->game_score);
                this->data->machine.AddState(StateRef(new GameOverState(this->data)));
            }

            this->pipe->MovePipes(dt, this->speed);
            this->bird->MoveBird(dt);
            this->land->MoveLand(dt, this->speed);

            if(this->clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY - this->speed){
                this->pipe->SpawnPipes();
                this->clock.restart();
            }

            this->score_text.setString(std::to_string(this->data->game_score));
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(2) << std::round(this->speed*100.0)/100.0;
            std::string roundedString = ss.str();
            this->speed_text.setString("Speed: " + roundedString);
        }
    }

    void GameState::Draw(float dt){
        this->data->window.clear();
        this->data->window.draw(background);
        this->pipe->DrawPipes();
        this->land->DrawLand();
        this->bird->DrawBird();
        this->data->window.draw(this->score_text);
        this->data->window.draw(this->keybinds);
        this->data->window.draw(this->speed_text);
        this->data->window.display();
    }

    bool GameState::ExistsEndingCollision(){
        for(unsigned short int i=0; i < this->pipe->pipe_sprites.size(); i++){
            if(this->bird->IntersectsWith(this->pipe->pipe_sprites.at(i).getGlobalBounds())) return true;
        }
        for(unsigned short int i=0; i < this->land->Sprites().size(); i++){
            if(this->bird->IntersectsWith(this->land->Sprites().at(i).getGlobalBounds())) return true;
        }
        return false;
    }

    bool GameState::ExistsScoringCollision(){
        for(unsigned short int i=0; i < this->pipe->score_boxes.size(); i++){
            if(this->bird->IntersectsWith(this->pipe->score_boxes.at(i).getGlobalBounds())){
                this->pipe->score_boxes.erase(this->pipe->score_boxes.begin() + i);
                return true;
            }
        }
        return false;
    }

    void GameState::SettleHighScores(int score){
        for (int i=0; i<3; i++) {
            if(score > this->data->scores[i]){
                int temp = this->data->scores[i];
                this->data->scores[i] = score;
                score = temp;
            }
        }
    }

    void GameState::Pause(){
      this->paused = !this->paused;  
    }

    void GameState::Mute(){
        muted = !muted;
    }
}
