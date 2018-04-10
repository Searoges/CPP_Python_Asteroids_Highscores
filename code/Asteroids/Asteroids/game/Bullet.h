#pragma once
#include "BaseObject.h"

class Bullet : public BaseObject
{
public:
	void Init(const Vector2&  startPosition, float direction);
	void Update();
	void Draw();

	std::vector<Vector2> GetLineList();
};
