#pragma once
#include "../engine/Vector2.h"
#include "../engine/Renderer.h"
#include <list>
#include <vector>

class ExplosionManager
{
	class Object
	{
	public:
		class Prim
		{
		public:
			Prim(const Vector2& centre, const Vector2& a, const Vector2& b, int col)
			{
				v0 = a;
				v1 = b;

				Vector2 midpoint = v0 + ((v1 - v0) / 2.0f);
				position = midpoint;

				v0 -= midpoint;
				v1 -= midpoint;

				velocity = position - centre;
				velocity.Normalize();
				velocity *= 1.5f;
				lifespan = 20 +rand()%60;
				tick = 0;

			}
			Vector2 v0,v1;
			int tick;
			int lifespan;
			Vector2 position;
			Vector2 velocity;

			bool Update()
			{
				position += velocity;
				tick++;

				return tick < lifespan;
			}

			void Draw()
			{			
				unsigned char a = 255 - ((tick *255)/lifespan);

				Renderer::Get()->DrawLine(Vector2(v0 + position), RGBATOCOLOR(255, 255, 255, a)
										 ,Vector2(v1 + position), RGBATOCOLOR(255, 255, 255, a));
			}

			typedef std::list<Prim*> List;
		};

	public:
		typedef std::list<Object*> List;
		Prim::List primList;

		bool Update();
		void Draw();
	};

public:

	Object::List ObjectList;

	void Clear();
	void Add(const Vector2& centre, const std::vector<Vector2>& vertList);
	void Update();
	void Draw();

	int ActiveCount() {return ObjectList.size();}
};