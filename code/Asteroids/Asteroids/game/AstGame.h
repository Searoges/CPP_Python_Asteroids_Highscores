#pragma once
#include "Rock.h"
#include "Ship.h"
#include "ExplosionManager.h"
#include "../engine/StateMachine.h"
#include "../engine/Singleton.h"

#include <list>

class AstGame : public Singleton<AstGame>
{
public:	
	std::list<Rock*> rockList;
	std::list<Bullet*> bulletList;

	Ship TheShip;
	bool bShipActive;
	int Score;
	int Ships;
	

	ExplosionManager explosionManager;

	void CreateRocks();
	void ExplodeRock(Rock& rock);

	bool IsShipActive();
	void PlaceShip();
	void SetInvincible();

	void ResetScore();

	void Init();

	bool OnOneTimeInit();
	void Update();
	void Draw();

	void GUIPrint(int x, int y,char* fmt);

	StateMachine stateMachine;
private:
};