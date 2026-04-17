#pragma once
#include "DeveloperLevel.h"
#include "Engine.h"
#include "Buttons.h"
#include "Logo.h"

namespace Roguelike {

    enum class GameState
    {
        Playing,
        Death,
        Win,
        Menu,
        Close,
        Fade,
        Enter_Menu
    };

    class Menu_Buttons;

    class GameManager
    {
    public:
        GameManager(const GameManager& app) = delete;
        GameManager& operator= (const GameManager&) = delete;

        static GameManager* Instance();

        void Run();

        void MouseCheck(sf::RenderWindow& window, sf::Event& event);
        void Render(sf::RenderWindow& window);
        void FadeIn(sf::RectangleShape& shape, float& alpha, float speed, float deltaTime);
        void CreateMenuUI();

        void setState(GameState new_state) {
            state = new_state;
        }
    private:
        GameManager();
        ~GameManager() = default;

        GameState state = GameState::Enter_Menu;
        std::vector<std::unique_ptr<Menu_Buttons>> buttons;
        std::unique_ptr<Logo> logo;
    };

    
}

