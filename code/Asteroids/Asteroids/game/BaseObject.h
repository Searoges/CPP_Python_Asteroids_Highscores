#pragma once
#include "Collider.h"
#include "../engine/Vector2.h"
#include <vector>


class BaseObject
{
public:
	BaseObject()
	{
		Reset();
	}

	virtual ~BaseObject()
	{
		Release();
	}

	bool IsInUse()	{return bInUse;}
	void SetInUse(bool active)	{bInUse = active;}
	void SetPosition(const Vector2& pos)
	{
		Position = pos;
	}

	static bool debugDraw;
	virtual void Update();
	virtual void Draw();

	virtual bool CollidesWith(const BaseObject* obj);

	virtual void SetCollided(bool bCollide)
	{
		bCollided = bCollide;
	}

	virtual bool GetCollided()
	{
		return bCollided;
	}

	CircularCollider collider;

	const Vector2& GetPosition() const {return Position;}

	virtual std::vector<Vector2> GetLineList() = 0;

	virtual void Release() 
	{
		Reset();
	}

protected:
	bool bInUse;
	bool bCollided;
	Vector2 Position;
	Vector2 Velocity;
	float angle;

	virtual void Reset() 
	{
		memset(this, 0, sizeof(BaseObject));
	}
};

template <class T>class BaseObjectArray
{
public:
	void Init(int maxObjects)
	{
		objectCount = maxObjects;
		pObjectArray = new T[maxObjects];
	}

	T& operator[](int i)
	{
		return pObjectArray[i];
	}
	int Length()
	{
		return objectCount;
	}

	T* GetFree()
	{
		for(int i=0;i<Length();i++)
		{
			if(pObjectArray[i].IsInUse() == false)
			{
				return &pObjectArray[i];
			}
		}

		return NULL;
	}

	void Update()
	{
		for(int i=0;i<Length();i++)
		{
			if(pObjectArray[i].IsInUse() == true)
			{
				pObjectArray[i].Update();
			}
		}
	}
	void Draw()
	{
		for(int i=0;i<Length();i++)
		{
			if(pObjectArray[i].IsInUse() == true)
			{
				pObjectArray[i].Draw();
			}
		}
	}

	void Clear()
	{
		for(int i=0;i<Length();i++)
		{
			pObjectArray[i].SetInUse(false);
		}
	}

	int GetActiveCount()
	{
		int inUse= 0;
		for(int i=0;i<Length();i++)
		{
			if(pObjectArray[i].IsInUse() == true)
			{
				inUse++;
			}
		}

		return inUse;
	}

private:
	T* pObjectArray;
	int objectCount;
};

