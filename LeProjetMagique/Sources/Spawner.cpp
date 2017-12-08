#include "Spawner.h"
#include "BasicEnemy.h"
#include "Kamikaze.h"
using namespace spaceShooter;
static float posX;
static float posY;
Enemy * Spawner::SpawnMob(Enemy::EnemyType type)
{
	Enemy* retVal = nullptr;
	if (type == Enemy::EnemyType::BASIC)
	{
		retVal = new BasicEnemy();
	}
	else if (type == Enemy::EnemyType::KAMIKAZE)
	{
		retVal = new Kamikaze();
	}
	else if (type == Enemy::EnemyType::REFLECTOR)
	{

	}
	else if (type == Enemy::EnemyType::QUEEN)
	{

	}
	else if (type == Enemy::EnemyType::BOSS_CANNON)
	{

	}
	return retVal;
}