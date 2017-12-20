#include "Reflector.h"
using namespace spaceShooter;

Reflector::Reflector() : BasicEnemy()
{
	objectif = idlePosition;
}
bool Reflector::Update(Vector2f target)
{
	BasicEnemy::Update(target);
	// Si l'objectif est atteint
	if (sprite->getPosition().x == objectif)
	{
		// On en trouve un nouveau
		objectif = rand() % ((int)sprite->getPosition().x + 200) + sprite->getPosition().x - 100;
	}
	// On bouge vers l'objectif
	if (objectif > 0)
	{
		Move(0, 1);
	}
	else
	{
		Move(0, -1);
	}
}