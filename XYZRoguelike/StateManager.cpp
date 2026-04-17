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

        while (RenderSystem::Instance()->GetMainWindow().isOpen())
        {
            float deltaTime = clock.restart().asSeconds();

            while (RenderSystem::Instance()->GetMainWindow().pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    RenderSystem::Instance()->GetMainWindow().close();
                }
            }

            if (!RenderSystem::Instance()->GetMainWindow().isOpen())
            {
                break;
            }

            switch (state)
            {
            case GameState::Enter_Menu:
                developer->Start();
                CreateMenuUI();
                switch (HopEngine::GameWorld::Instance()->get_world_end())
                {
                case HopEngine::world_end::player_death:
                    HopEngine::SoundSystem::Instance()->Play_Sound("Sound: death");
                    HopEngine::TimerSystem::Instance()->addTimer("end_sound_menu", 6.f);
                    break;
                case HopEngine::world_end::player_win:
                    HopEngine::SoundSystem::Instance()->Play_Sound("Sound: win");
                    HopEngine::TimerSystem::Instance()->addTimer("end_sound_menu", 4.f);
                    HopEngine::TimerSystem::Instance()->addTimer("blue_screen", 4.f);
                    break;
                default:
                    break;
                }
                state = GameState::End_Screen;
                break;

            case GameState::End_Screen:
                HopEngine::TimerSystem::Instance()->Update(deltaTime);
                if (HopEngine::TimerSystem::Instance()->checkTimer("end_sound_menu") != TimerState::In_Process) state = GameState::Fade;
                break;

            case GameState::Fade:
                FadeIn(logo->logo_shape, logo->fadeAlpha, logo->fadeSpeed, deltaTime);
                for (auto& btn : buttons) FadeIn(btn->button_shape, btn->fadeAlpha, btn->fadeSpeed, deltaTime);
                break;
            
            case GameState::Menu:
                MouseCheck(window, event);
                break;

            case GameState::Playing:
                HopEngine::Engine::Instance()->Run();
                for (auto& btn : buttons) btn->ResetFade();
                logo->ResetFade();
                developer->Stop();
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
        
        if(HopEngine::TimerSystem::Instance()->checkTimer("blue_screen") != TimerState::In_Process) window.clear(sf::Color::White);
        else window.clear(sf::Color::Blue);

        window.setView(window.getDefaultView());

        if (HopEngine::TimerSystem::Instance()->checkTimer("end_sound_menu") != TimerState::In_Process) {
            window.draw(logo->logo_shape);

            for (auto& btn : buttons) {
                window.draw(btn->button_shape);
            }
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