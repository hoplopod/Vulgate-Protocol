#pragma once
#include "DeveloperLevel.h"
#include "Engine.h"
#include "Buttons.h"

namespace Roguelike {

    enum class GameState
    {
        Menu,
        Playing,
        Death
    };

    class Menu_Button;

    class GameManager
    {
    public:
        GameManager(const GameManager& app) = delete;
        GameManager& operator= (const GameManager&) = delete;

        static GameManager* Instance();

        void Run();

        void Render(sf::RenderWindow& window);

    private:
        GameManager();
        ~GameManager() = default;

        GameState state = GameState::Menu;
        std::vector<Menu_Button> buttons;
    };

    
}

