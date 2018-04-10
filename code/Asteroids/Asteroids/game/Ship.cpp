#include "Ship.h"
#include "AstGame.h"
#include "../engine/Matrix.h"
#include "../engine/Renderer.h"
#include "../engine/Input.h"

Ship::Ship()
{	
}

void Ship::Init()
{
	Renderer::Viewport vp;
	Renderer::Get()->GetViewport(vp);

	Position = Vector2(vp.Width/2.0f,vp.Height/2.0f);

	Velocity = Vector2(0,5);

	Velocity = Vector2(0,0);
	angle =  0;

	collider.Set(Position,15);
	
	lastShotTime = 0;	
}

void Ship::OnCollided()
{
}

void Ship::Update()
{
	Renderer::Viewport vp;
	Renderer::Get()->GetViewport(vp);

	if(Input::Get()->GetKeyState(VK_LEFT) != KeyState_NotPressed)
	{
		angle += 0.1f;
	}

	if (Input::Get()->GetKeyState(VK_RIGHT) != KeyState_NotPressed)
	{
		angle -= 0.1f;
	}

	if (Input::Get()->GetKeyState(VK_LCONTROL) != KeyState_NotPressed)
	{
		if(Renderer::Get()->GetFrameCount() - lastShotTime > 10)
		{
			Bullet* b = new Bullet();

			AstGame::Get()->bulletList.push_back(b);
			
			Vector2 bulletPos = Position + Vector2::Transform(Vector2(0,20),Matrix::CreateRotationZ(angle));
			b->Init(bulletPos, angle);

			lastShotTime = Renderer::Get()->GetFrameCount();
		}
	}


	Vector2 Thrust = Vector2(0,0);
	bool bThrusting = false;



	if (Input::Get()->GetKeyState(VK_UP) != KeyState_NotPressed)
	{
		Thrust += Vector2::Transform(Vector2(0,0.25f), Matrix::CreateRotationZ(angle));

		bThrusting = true;
	}
	else
	{
		bThrusting = false;
	}
	
	Velocity += Thrust;

	Vector2 Drag = (Velocity / -100.0f);

	Velocity += Drag;

	if(Velocity.Length() > 3)
	{
		Velocity.Normalize();
		Velocity *= 3;
	}

	if(Velocity.Length() < 0.2f)
	{
		Velocity *= 0;
	}

	if((Position.x + Velocity.x) < 0)
	{
		Position.x += vp.Width;
	}

	if((Position.x + Velocity.x) > vp.Width)
	{
		Position.x -= vp.Width;
	}

	if((Position.y + Velocity.y) < 0)
	{
		Position.y += vp.Height;
	}

	if((Position.y + Velocity.y) > vp.Height)
	{
		Position.y -= vp.Height;
	}

	Position += Velocity;

	bDisplayThrust = ((bThrusting == true) && (Renderer::Get()->GetFrameCount()%5) == 1);

	if (invincibleTicker > 0)
	{
		invincibleTicker--;
	}

	BaseObject::Update();
}

void Ship::UpdateBullets()
{
	//bulletList.Update();

	
}

void Ship::Draw()
{
	{
		Vector2 Points[4];

		Points[0] = Vector2(0, 20);
		Points[1] = Vector2(10,-10);
		Points[2] = Vector2(0, -5);
		Points[3] = Vector2(-10, -10);


		Matrix transform = Matrix::CreateRotationZ(angle) * Matrix::CreateTranslation(Position.x,Position.y,0);

		for (unsigned int i = 0; i < 4; i++)
		{		
			Points[i] = Vector2::Transform(Points[i],transform);
		}
		
		unsigned int index[] = {0,1 ,1,2 ,2,3 ,3,0};

		bool drawShip = true;

		if (canCollide() == false)
		{
			drawShip = (Renderer::Get()->GetFrameCount() % 10) >=5;
		}

		if (drawShip == true)
		{
			for (unsigned int iIndex = 0; iIndex < ARRAY_LENGTH(index); iIndex += 2)
			{
				Renderer::Get()->DrawLine(Points[index[iIndex]], RGBTOCOLOR(255, 255, 255)
					, Points[index[iIndex + 1]], RGBTOCOLOR(255, 255, 255));
			}
		}		
	}

	if(bDisplayThrust == true)
	{
		Vector2 Points[4];

		Points[0] = Vector2(0, -7);
		Points[1] = Vector2(5, -11);
		Points[2] = Vector2(0, -20);
		Points[3] = Vector2(-5, -11);


		Matrix transform = Matrix::CreateRotationZ(angle) * Matrix::CreateTranslation(Position.x,Position.y,0);

		for (unsigned int i = 0; i < 4; i++)
		{		
			Points[i] = Vector2::Transform(Points[i],transform);
		}
		
		unsigned int index[] = {0,1 ,1,2 ,2,3 ,3,0};

		for (unsigned int iIndex = 0; iIndex < ARRAY_LENGTH(index); iIndex += 2)
		{
			Renderer::Get()->DrawLine(Points[index[iIndex]], RGBTOCOLOR(255, 255, 255)
				, Points[index[iIndex + 1]], RGBTOCOLOR(255, 255, 255));
		}

	}

	BaseObject::Draw();
}

std::vector<Vector2> Ship::GetLineList()
{
	std::vector<Vector2> vertList;

	Vector2 Points[4];

	Points[0] = Vector2(0, 20);
	Points[1] = Vector2(10,-10);
	Points[2] = Vector2(0, -5);
	Points[3] = Vector2(-10, -10);


	Matrix transform = Matrix::CreateRotationZ(angle) * Matrix::CreateTranslation(Position.x,Position.y,0);

	for (unsigned int i = 0; i < 4; i++)
	{		
		Points[i] = Vector2::Transform(Points[i],transform);
	}

	unsigned int index[] = {0,1 ,1,2 ,2,3 ,3,0};


	for(unsigned int iIndex=0;iIndex < ARRAY_LENGTH(index);iIndex++)
	{
		vertList.push_back(Points[index[iIndex]]);
	}

	return vertList;
}

bool Ship::canCollide()
{
	return (invincibleTicker == 0);
}

void Ship::SetInvincible()
{
	invincibleTicker = 120;
}
