#pragma once
//<smasson>
#include <SFML\Graphics.hpp>
#include "StaticSubject.h"
#include "Spaceship.h"
#include <vector>

using namespace sf;
using namespace spaceShooter;
using namespace std;

namespace spaceShooter
{
    class Projectile
    {
    public:
        Projectile(const float x, const float y, const Color color, const float speed, Spaceship* owner);
		Projectile();
        ~Projectile();
        static enum ProjectileType
        {
            UNDEFINED,
            LAZER_PROJ,
            BULLET,
            BASIC,
            ETOILE,
            BOMB,
            BOMB_PROJ
        };
        void Start(const Vector2f dir, Vector2f position, Spaceship& owner);
        void SetTexture(const Texture& texture);
        virtual void Draw(RenderWindow& mainWin);
        void SetOwner(Spaceship& newOwner);
        Color GetColor();
        Spaceship& GetOwner();
        void Update();
        bool IsEnable();
        void SetEnable(bool enable);
        Vector2f GetPosition();
		static void SubscribeToCollisions(Spaceship* subscriber);
		static void CleanUp();
        int GetDamage() const;
        //<sberube>
        void SetRotation(float angle);
        //</sberube>
    private:
        Spaceship* owner;
		static vector<Spaceship*> observersCollisions;
	protected:
        Shape* shape;
        float speed;
        Vector2f dir;
        bool isEnable;
        int damage;
    };
}
//</smasson>