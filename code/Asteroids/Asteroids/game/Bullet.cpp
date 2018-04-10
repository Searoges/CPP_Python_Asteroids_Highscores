#include "Bullet.h"
#include "../engine/Matrix.h"
#include "../engine/Renderer.h"

void Bullet::Init(const Vector2&  startPosition, float direction)
{
	bInUse = true;
	Position = startPosition;
	angle = direction;
	Velocity = Vector2::Transform(Vector2(0,7),Matrix::CreateRotationZ(direction));

	collider.Set(startPosition,3);
}

void Bullet::Update()
{
	if(IsInUse() == false) return;

	Renderer::Viewport vp;
	Renderer::Get()->GetViewport(vp);

	if( ((Position.x + Velocity.x) < 0)
		||((Position.x + Velocity.x) > vp.Width)
		)
	{
		SetInUse(false);
		return;
	}

	if( ((Position.y + Velocity.y) < 0)
		||((Position.y + Velocity.y) > vp.Height)
		)
	{
		SetInUse(false);
		return;
	}

	Position += Velocity;


	BaseObject::Update();
}

void Bullet::Draw()
{
	if(IsInUse() == false)	return;
	Renderer::Get()->DrawRect(Position.x-2,Position.y-2,4,4,RGBTOCOLOR(255,255,255));
	BaseObject::Draw();
}

std::vector<Vector2> Bullet::GetLineList()
{
	std::vector<Vector2> vertList;

	return vertList;
}
