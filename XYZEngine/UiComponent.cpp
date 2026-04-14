#include "pch.h"
#include "UiComponent.h"

HopEngine::HealthBarComponent::HealthBarComponent(GameObject* gameObject) : Component(gameObject)
{
	pve = gameObject->GetComponent<PVEComponent>();
    transform = gameObject->GetComponent<TransformComponent>();

    bar.setFillColor(sf::Color::White);
    static sf::Texture dummy;
    dummy.create(1, 1);
    bar.setTexture(&dummy);
    shader.loadFromMemory(R"(
    uniform float health;
    uniform float radius; 

void main()
{
    vec2 uv = gl_TexCoord[0].xy;

    vec4 color;
    if (uv.x <= health)
        color = vec4(0.2, 0.8, 0.2, 1.0);
    else
        color = vec4(0.4, 0.0, 0.0, 1.0);

    float dx = min(uv.x, 1.0 - uv.x);
    float dy = min(uv.y, 1.0 - uv.y);

    float dist = min(dx, dy);

    float alpha = smoothstep(0.0, radius, dist);

    gl_FragColor = vec4(color.rgb, color.a * alpha);
}
)", sf::Shader::Fragment);

}

sf::RectangleShape& HopEngine::HealthBarComponent::getBar()
{
	return bar;
}

void HopEngine::HealthBarComponent::Update(float deltaTime)
{
    bar.setPosition({ transform->GetWorldPosition().x - 90, transform->GetWorldPosition().y + 475.f});
}

void HopEngine::HealthBarComponent::Render()
{
    if (pve->getDeath()) return;
	auto& window = RenderSystem::Instance()->GetMainWindow();
	float percent = (float)pve->getHp() / pve->getMaxHp();
	shader.setUniform("health", percent);
    shader.setUniform("radius", 0.05f);
	window.draw(bar, &shader);

}
