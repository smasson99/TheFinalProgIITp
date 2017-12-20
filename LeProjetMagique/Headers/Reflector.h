#pragma once
#include "BasicEnemy.h"
namespace spaceShooter
{
	class Reflector : BasicEnemy
	{
	public:
		Reflector();
		bool Update(Vector2f target);
		void Reflect(Projectile &proj);
	private:
		const float DeflectRadius = 100;
		const int maxDeflexion = 5;
		int nbDeflected = 0;

		float objectif;
	};
}