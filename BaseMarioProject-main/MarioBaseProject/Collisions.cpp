#include "Collisions.h"
#include "Character.h"

//Initialise instance to nullptr
Collisions* Collisions::m_instance = nullptr;

Collisions::Collisions()
{

}

Collisions::~Collisions()
{
	m_instance = nullptr;
}

Collisions* Collisions::Instance()
{
	if (!m_instance)
	{
		m_instance = new Collisions;
	}
	
	return m_instance;
}

bool Collisions::Circle(Character* characterOne, Character* characterTwo)
{
	Vector2D vec = Vector2D((characterOne->GetPosition().x - characterTwo->GetPosition().x), (characterOne->GetPosition().y - characterTwo->GetPosition().y));
	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	double combined_distance = (characterOne->GetCollisionRadius() + characterTwo->GetCollisionRadius());
	return distance < combined_distance;
}

bool Collisions::Box(Rect2D rectOne, Rect2D rectTwo)
{
	if (rectOne.x + (rectOne.width / 2) > rectTwo.x &&
		rectOne.x + (rectOne.width / 2) < rectTwo.x + rectTwo.width &&
		rectOne.y + (rectOne.height / 2) > rectTwo.y &&
		rectOne.y + (rectOne.height / 2) < rectTwo.y + rectTwo.height)
	{
		return true;
	}
	return false;
}