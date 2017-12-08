#pragma once
#include "Enemy.h"
//<sberube>
namespace spaceShooter
{
	static class Spawner
	{
	public:
		static Enemy * SpawnMob(Enemy::EnemyType type);
	private:
	};
}
//</sberube>