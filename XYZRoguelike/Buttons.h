#pragma once
#include "StateManager.h"

namespace Roguelike {

    class Menu_Button {
    protected:
        virtual void Action() = 0;

        sf::RectangleShape button_shape;
    };

}
