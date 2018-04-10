#include "Rock.h"
#include <assert.h>
#include "../engine/Renderer.h"
#include "../engine/matrix.h"

void Rock::Init()
{

	Renderer::Viewport vp;
	Renderer::Get()->GetViewport(vp);

	Position = Vector2(vp.Width/2.0f,vp.Height/2.0f);

	Init(Position,Size_big);

	static int randCount=0;
	srand(randCount);

	randCount++;

	do 
	{
		Velocity = Vector2(0,((rand()%60) - 30)/10.0f);
	} while (Velocity.Length() < 1);

	float angle = (DEG_TO_RAD((float)(rand() % 360)));
	Velocity = Vector2::Transform(Velocity, Matrix::CreateRotationZ(angle));
	angle =  0;
}

void Rock::Init(const Rock & rock)
{
	if(rock.size == Size_big)
	{
		size = Size_medium;
	}
	else
	{
		size = Size_small;
	}

	static int randCount=0;
	srand(randCount);

	randCount++;

	do 
	{
		Velocity = Vector2(0,((rand()%60) - 30)/10.0f);
	} while (Velocity.Length() < 1);


	float angle = (DEG_TO_RAD((float)(rand() % 360)));
	Velocity = Vector2::Transform(Velocity, Matrix::CreateRotationZ(angle));

	angle =  0;

	Init(rock.Position,size,Velocity);
}
void Rock::Init(const Vector2& pos, Size s,const Vector2& vel)
{
	bInUse = true;
	size = s;
	Position = pos;
	Velocity = vel;

	switch(size)
	{
	case Size_big:
		collider.Set(Position,40);
		break;

	case Size_medium:
		collider.Set(Position,15);
		break;

	case Size_small:
		collider.Set(Position,8);
		break;

	default:
		assert(0);
		break;
	}
}

void Rock::Update()
{
	if(bInUse == false) return;
	angle += 0.01f;

	Renderer::Viewport vp;
	Renderer::Get()->GetViewport(vp);

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

	BaseObject::Update();
}

void Rock::Draw()
{
	if(bInUse == false) return;

	std::vector<Vector2> verts = GetLineList();
		
	for (u32 i = 0; i < (u32)verts.size(); i += 2)
	{
		Renderer::Get()->DrawLine(verts[i], RGBTOCOLOR(255, 255, 255)
			, verts[i + 1], RGBTOCOLOR(255, 255, 255));
	}


	BaseObject::Draw();

}

std::vector<Vector2> Rock::GetLineList()
{
	std::vector<Vector2> vertList;

	Vector2 Points[40];

	float rockAngle=0;

	srand(0);

	for(int i=0;i<ARRAY_LENGTH(Points);i++)
	{
		switch(size)
		{
		case Size_big:
			Points[i] = Vector2::Transform(Vector2(0,(float)(30 + rand()%10)), Matrix::CreateRotationZ(DEG_TO_RAD((float)((i*360)/ARRAY_LENGTH(Points)))));
			break;

		case Size_medium:
			Points[i] = Vector2::Transform(Vector2(0, (float)(10 + rand()%5)), Matrix::CreateRotationZ(DEG_TO_RAD((float)((i * 360) / ARRAY_LENGTH(Points)))));
			break;

		case Size_small:
			Points[i] = Vector2::Transform(Vector2(0, (float)(5 + rand()%3)), Matrix::CreateRotationZ(DEG_TO_RAD((float)((i * 360) / ARRAY_LENGTH(Points)))));
			break;
		default:
			assert(0);
			break;
		}
	}

	Matrix transform = Matrix::CreateRotationZ(angle) * Matrix::CreateTranslation(Position.x,Position.y,0);

	for (unsigned int i = 0; i < ARRAY_LENGTH(Points); i++)
	{		
		Points[i] = Vector2::Transform(Points[i],transform);
	}	

	int index=0;

	for(unsigned int i=0;i < ARRAY_LENGTH(Points);i++)
	{
		vertList.push_back(Vector2(Points[i+0]));
		vertList.push_back(Vector2(Points[(i+1)%ARRAY_LENGTH(Points)]));		
	}

	return vertList;
}

