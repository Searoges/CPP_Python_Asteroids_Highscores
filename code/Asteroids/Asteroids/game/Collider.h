#pragma once 
#include "../engine/Vector2.h"
#include "../engine/Renderer.h"

class CircularCollider
{
public:
	void Set(const Vector2& pos, float radius)
	{
		Position = pos;
		Radius = radius;
	}

	bool Collide(const CircularCollider& target)
	{
		return Vector2::Length(Position - target.Position) < (Radius + target.Radius);
	}

	void Draw(int c = RGBTOCOLOR(255,255,255))
	{
		Renderer::Get()->DrawCircle(Position,Radius,c);
	}

	void SetPosition(const Vector2& position)
	{
		Position = position;
	}

	Vector2 Position;
	float Radius;
};
