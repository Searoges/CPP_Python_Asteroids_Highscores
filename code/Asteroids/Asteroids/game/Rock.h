#pragma once
#include "BaseObject.h"

class Rock : public BaseObject
{
public:

	enum Size
	{
		Size_big,
		Size_medium,
		Size_small,
	};

	void Init();
	void Init(const Rock & rock);		
	void Init(const Vector2& pos, Size s,const Vector2& vel = Vector2(0,0));


	void Update();
	void Draw();

	void Explode(const BaseObject& obj);

	virtual std::vector<Vector2> GetLineList();
	Size size;
};
