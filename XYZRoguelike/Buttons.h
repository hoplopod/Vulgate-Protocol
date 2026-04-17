#pragma once
#include "StateManager.h"

namespace Roguelike {

    class Menu_Buttons {
    public:
        sf::RectangleShape button_shape;

        virtual void Action() = 0;

        bool wasPressed = false;
        bool isPressedInside = false;

        float fadeAlpha = 0.f;
        float fadeSpeed = 200.f;
        bool fadingIn = true;

        void ResetFade();

    };

    class Start_Button : public Menu_Buttons {
    public:
        Start_Button();

        void Action() override;
    };

    class Exit_Button : public Menu_Buttons {
    public:
        Exit_Button();

        void Action() override;
    };

}
