#pragma once

#include "RenderSystem.h"
#include "PVEComponent.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace HopEngine {

    class HealthBarComponent : public Component {
    public:
        HealthBarComponent(GameObject* gameObject);

        sf::RectangleShape& getBar();

        void Update(float deltaTime) override;
        void Render() override;
    
    private:
        sf::Shader shader;
        sf::RectangleShape bar;

        float currentHP;
        float maxHP;

        PVEComponent* pve;
        TransformComponent* transform;
    };

}