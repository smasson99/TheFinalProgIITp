#pragma once
#include "Spaceship.h"
#include "Weapon.h"

namespace spaceShooter
{
    class Player :public Spaceship
    {
    public:
        static Player* GetInstance();
        static void KillInstance();
        void SetLimits(const Vector2f point1, const Vector2f point2);
        bool Update(int commands);
        bool CanShoot();
        void Shoot();
        Vector2f GetDirection();
        Weapon::WeaponType GetWeaponType();
        int GetNbMunitions();
        int GetScoreMultiplicatorValue();
        void AddScore(int points);
        int GetScore();
        static bool Init(char path[]);
        void AdjustVisual();
        void NotifyBonusCollision(Bonus* bonus) override;
    private:
        Player();
        ~Player();
        void AddScoreMult();
        Time scoreMultTime;
        Clock scoreMultClock;
        static Player* instance;
        Vector2f limitMin;
        Vector2f limitMax;
        int curWepIndex;
        int curScorMult;
        int score;
        //temp
        vector<Weapon*> weapons;
        //
        static Texture texture;
    };
}