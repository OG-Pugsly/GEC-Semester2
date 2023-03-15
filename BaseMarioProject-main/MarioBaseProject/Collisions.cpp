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

bool Collisions::Circle(Vector2D unitOnePosition, float unitOneCollisionRadius, Vector2D unitTwoPosition, float unitTwoCollisionRadius)
{
	Vector2D vec = Vector2D((unitOnePosition.x - unitTwoPosition.x), (unitOnePosition.y - unitTwoPosition.y));
	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	double combined_distance = (unitOneCollisionRadius + unitTwoCollisionRadius);
	return distance < combined_distance;
}

bool Collisions::Box(Rect2D rectOne, Rect2D rectTwo)
{
	if (rectOne.x + rectOne.width > rectTwo.x &&
		rectOne.x < rectTwo.x + rectTwo.width &&
		rectOne.y + rectOne.height > rectTwo.y &&
		rectOne.y < rectTwo.y + rectTwo.height)
	{
		return true;
	}
	return false;
}