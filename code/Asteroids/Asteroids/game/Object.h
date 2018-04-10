#pragma once

class Object
{
public:
	void virtual init()=0;
	void virtual Update() = 0;
	void virtual Draw();

	bool virtual IsColliding(const Object& o);
//protected:
	float posX,posY;
	float w,h;
};
