#include "StateManager.h"

namespace Roguelike {

	GameManager* GameManager::Instance()
	{
		static GameManager manager;
		return &manager;
	}

	void GameManager::Run() {

        auto& window = HopEngine::RenderSystem::Instance()->GetMainWindow();

        sf::Clock clock;
        sf::Event event;
        
        auto developer = std::make_shared<DeveloperLevel>();


        while (window.isOpen())
        {
            float deltaTime = clock.restart().asSeconds();

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1) state = GameState::Playing;

            Render(window);

            switch (state)
            {
            case GameState::Menu:
                break;

            case GameState::Playing:
                developer->Start();
                HopEngine::Engine::Instance()->Run();
                developer->Stop();
                state = GameState::Menu;
                break;

            case GameState::Death:
                developer->Stop();
                break;
            }

            
        }


	}

    GameManager::GameManager()
    {
    }

    void GameManager::Render(sf::RenderWindow& window) {


        window.clear();
        window.display();
    }

}