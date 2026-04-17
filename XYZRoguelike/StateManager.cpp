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

            switch (state)
            {
            case GameState::Enter_Menu:
                CreateMenuUI();
                state = GameState::Fade;
                break;
            
            case GameState::Fade:
                FadeIn(logo->logo_shape, logo->fadeAlpha, 200.f, deltaTime);
                for (auto& btn : buttons) FadeIn(btn->button_shape, btn->fadeAlpha, 200.f, deltaTime);
                break;
            
            case GameState::Menu:
                MouseCheck(window, event);
                break;

            case GameState::Playing:
                developer->Start();
                HopEngine::Engine::Instance()->Run();
                developer->Stop();
                for (auto& btn : buttons) btn->ResetFade();
                logo->ResetFade();
                state = GameState::Enter_Menu;
                break;

            case GameState::Close:
                window.close();
                break;

            }

            Render(window);
        }
	}

    GameManager::GameManager()
    {
    }

    void GameManager::MouseCheck(sf::RenderWindow& window, sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

            for (auto& btn : buttons)
            {
                if (btn->button_shape.getGlobalBounds().contains(mousePos))
                {
                    btn->isPressedInside = true;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

            for (auto& btn : buttons)
            {
                bool hovered = btn->button_shape.getGlobalBounds().contains(mousePos);

                if (btn->isPressedInside && hovered)
                {
                    btn->Action();
                }

                btn->isPressedInside = false;
            }
        }
    }

    void GameManager::Render(sf::RenderWindow& window) {
        
        window.clear(sf::Color::White);

        window.setView(window.getDefaultView());

        window.draw(logo->logo_shape);

        for (auto& btn : buttons) {
            window.draw(btn->button_shape);
        }
        
        window.display();
    }

    void GameManager::FadeIn(sf::RectangleShape& shape, float& alpha, float speed, float deltaTime)
    {
        if (alpha < 255.f)
        {
            alpha += speed * deltaTime;
            if (alpha > 255.f) {
                state = GameState::Menu;
                alpha = 255.f;
            }

            auto color = shape.getFillColor();
            color.a = static_cast<sf::Uint8>(alpha);
            shape.setFillColor(color);
        }
    }

    void GameManager::CreateMenuUI()
    {
        buttons.clear();

        logo = std::make_unique<Logo>();
        buttons.push_back(std::make_unique<Start_Button>());
        buttons.push_back(std::make_unique<Exit_Button>());
    }

}