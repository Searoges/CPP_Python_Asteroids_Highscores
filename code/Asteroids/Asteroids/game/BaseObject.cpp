#include "BaseObject.h"

bool BaseObject::debugDraw = false;

void BaseObject::Update()
{
	collider.SetPosition(Position);
}

bool BaseObject::CollidesWith(const BaseObject* obj)
{	
	return this->collider.Collide(obj->collider);
}

void BaseObject::Draw()
{
	if (debugDraw == false)
	{
		return;
	}

	if(bCollided == true)
	{
		collider.Draw(RGBTOCOLOR(255,0,0));
	}
	else
	{
		collider.Draw(RGBTOCOLOR(255,255,0));
	}
}