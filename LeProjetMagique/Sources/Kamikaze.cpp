#include "Kamikaze.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace spaceShooter;

Texture Kamikaze::texture;

Kamikaze::Kamikaze() : Bombe(0, 0, Color(), startSpeed, new Spaceship())
{
    isSlave = false;
    type = Enemy::EnemyType::BASIC;
    sprite->setScale(0.15f, 0.15f);
    sprite->setRotation(180);
    enemyWeapon = nullptr;
}

spaceShooter::Kamikaze::~Kamikaze()
{
}

bool spaceShooter::Kamikaze::Init(char path[])
{
    if (!texture.loadFromFile(path))
    {
        return false;
    }
    return true;
}

void spaceShooter::Kamikaze::AdjustVisual()
{
    sprite->setTexture(this->texture);
    sprite->setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

bool Kamikaze::Update(Vector2f target)
{
    curSpeed += 0.002;
    if (curSpeed > maxSpeed)
    {
        curSpeed = maxSpeed;
    }
    Enemy::Update(target);
    float angle = atan2(target.y - sprite->getPosition().y, target.x - sprite->getPosition().x) * 180 / M_PI;
    sprite->setRotation(angle + 90);
    dir = Vector2f(cosf(M_PI * angle / 180.0f), sinf(M_PI * angle / 180.0f));
    sprite->move(dir.x*curSpeed, dir.y*curSpeed);
    return curHealth > 0;
}

void Kamikaze::Draw(RenderWindow &win)
{
    Enemy::Draw(win);
}