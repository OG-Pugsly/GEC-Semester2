#pragma once
#ifndef _COLLISIONS_H
#define _COLLISIONS_H

#include "Commons.h"

class Character;

class Collisions
{
public:

	~Collisions();

	static Collisions* Instance();

	bool Circle(Character* characterOne, Character* characterTwo);
	bool Box(Rect2D rectOne, Rect2D rectTwo);


private:
	Collisions();
	static Collisions* m_instance;


protected:



};

#endif // _COLLISIONS_H