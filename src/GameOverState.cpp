#include "Game.hpp"
#include "GameState.hpp"
#include "GameOverState.hpp"
#include "DEFINITIONS.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <string>

namespace omi
{
    GameOverState::GameOverState(GameDataRef data) : data(data){
        
    }

    void GameOverState::Init(){
        this->data->assets.LoadTexture("Game Over State Background", GAME_OVER_BACKGROUND_FILEPATH);
        this->data->assets.LoadTexture("Game Over Title", GAME_TITLE_FILEPATH);
        this->data->assets.LoadTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);
        this->background.setTexture(this->data->assets.GetTexture("Game Over State Background"));
        this->title.setTexture(this->data->assets.GetTexture("Game Over Title"));
        this->title.setOrigin(
                this->title.getGlobalBounds().width/2,
                this->title.getGlobalBounds().height/2
                );
        this->title.setPosition(
                int(SCREEN_WIDTH/2),
                int(SCREEN_HEIGHT/5)
                );
        this->body.setTexture(this->data->assets.GetTexture("Game Over Body"));
        this->body.setOrigin(
                this->body.getGlobalBounds().width/2,
                this->body.getGlobalBounds().height/2
                );
        this->body.setPosition(
                int(SCREEN_WIDTH/2),
                int(SCREEN_HEIGHT/2)
                );

        this->best_score.setFont(this->data->assets.GetFont("Flappy Font"));
        this->best_score.setCharacterSize(SCORE_FONT_SIZE);
        this->best_score.setString(std::to_string(this->data->high_score));
        this->best_score.setOrigin(this->best_score.getGlobalBounds().width, this->best_score.getGlobalBounds().height);
        this->best_score.setPosition(int(3*SCREEN_WIDTH/4), int(SCREEN_HEIGHT/2)+85);

        this->game_score.setFont(this->data->assets.GetFont("Flappy Font"));
        this->game_score.setCharacterSize(SCORE_FONT_SIZE);
        this->game_score.setString(std::to_string(this->data->game_score));
        this->game_score.setOrigin(this->game_score.getGlobalBounds().width, this->game_score.getGlobalBounds().height);
        this->game_score.setPosition(int(3*SCREEN_WIDTH/4), int(SCREEN_HEIGHT/2)-15);
    }

    void GameOverState::HandleInput(){
        sf::Event event;

        while(this->data->window.pollEvent(event)){
            switch (event.type){
                case sf::Event::Closed:
                    this->data->window.close();
                    break;
                case sf::Event::KeyReleased:
                    switch(event.key.code){
                        case sf::Keyboard::Q:
                            this->data->window.close();
                            break;
                        case sf::Keyboard::R:
                            this->data->machine.AddState(StateRef(new GameState(data)));
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }
    }

    void GameOverState::Update(float dt){

    }

    void GameOverState::Draw(float dt){
        this->data->window.clear();
        this->data->window.draw(background);
        this->data->window.draw(title);
        this->data->window.draw(body);
        this->data->window.draw(this->best_score);
        this->data->window.draw(this->game_score);
        this->data->window.display();
    }
}
