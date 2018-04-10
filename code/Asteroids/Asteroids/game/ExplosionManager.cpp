#include "ExplosionManager.h"

void ExplosionManager::Clear()
{

}

void ExplosionManager::Add(const Vector2& centre,const std::vector<Vector2>& vertList)
{
	Object* obj = new Object;

	for(int i=0;i<(int)vertList.size()/2;i++)
	{
		Object::Prim* p = new Object::Prim(centre,vertList[(i*2)+0],vertList[(i*2)+1],RGBTOCOLOR(255,255,255));
		obj->primList.push_back(p);
	}

	ObjectList.push_back(obj);

}

void ExplosionManager::Update()
{
	Object::List::iterator it = ObjectList.begin();

	while(it != ObjectList.end())
	{
		if((*it)->Update() == false)
		{
			delete (*it);
			it = ObjectList.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void ExplosionManager::Draw()
{
	for(Object::List::iterator it = ObjectList.begin();it != ObjectList.end();it++)
	{
		(*it)->Draw();		
	}
}


bool ExplosionManager::Object::Update()
{
	Prim::List::iterator it = primList.begin();
	
	while(it != primList.end())
	{
		if((*it)->Update() == false)
		{
			delete (*it);
			it = primList.erase(it);
		}
		else
		{
			it++;
		}
	}

	return primList.size() > 0;
}

void ExplosionManager::Object::Draw()
{
	for(Prim::List::iterator it = primList.begin();it != primList.end();it++)
	{
		(*it)->Draw();
	}
}