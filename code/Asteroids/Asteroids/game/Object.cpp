#include "Object.h"
#include "../engine/Renderer.h"
bool Object::IsColliding(const Object& o)
{
	if((posX + w) < o.posX) return false;
	if((posX ) > (o.posX + o.w)) return false;

	if((posY + h) < o.posY) return false;
	if((posY ) > (o.posY + o.h)) return false;

	return true;
}

void Object::Draw()
{	
	Renderer::Get()->DrawRect(posX,posY,w,h,RGBTOCOLOR(255,255,255));
}
