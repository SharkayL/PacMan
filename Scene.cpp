#include "Scene.h"

Scene::Scene(PacmanApp &app)
{
	play = false;
}


Scene::~Scene()
{
}
void Scene::Update(sf::Time timeDelta) {
}
void Scene::Draw(sf::RenderWindow &window) {
	bgd.Draw(window);
	//window.draw();
}
void Scene::HandleEvent(sf::Event event) {
	
}
