#pragma once
#include "BaseObject.h"
#include "Bullet.h"
#include <list>

class Ship : public BaseObject
{
public:
	Ship();

	void Init();
	void Update();
	void UpdateBullets();

	void Draw();
	void DrawBullets();

	void OnCollided();

	std::vector<Vector2> GetLineList();
	
	bool canCollide();
	void SetInvincible();

private:
	bool bDisplayThrust;
	int lastShotTime;	
	int invincibleTicker;
};
