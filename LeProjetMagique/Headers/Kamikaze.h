//<sberube>
#pragma once
#include "Enemy.h"
#include "Bombe.h"
namespace spaceShooter
{
	class Kamikaze : public Enemy, public Bombe
	{
	public:
		Kamikaze();
        ~Kamikaze();
        //<smasson>
        static bool Init(char path[]);
        void AdjustVisual();
        bool IsEnable();
        void Start(Vector2f startPos, default_random_engine & engine);
        //</smasson>
		bool Update(Vector2f target);
		void Draw(RenderWindow &win);
	private:
		const float startSpeed = 0.01f;
		float curSpeed = startSpeed;
		float maxSpeed = 6;
        //<smasson>
        static Texture texture;
        //</smasson>
	};
}
//</sberube>