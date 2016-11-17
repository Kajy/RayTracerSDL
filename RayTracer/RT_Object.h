#include "RT.h"

class RT_Object
{
public:
	virtual ~RT_Object() {};

	virtual	float		checkCollision(int, int, RT_Vector3df *, RT_Vector3df *) = 0;
	virtual void		calcNormale(RT_Vector3df *vect, float k, RT_Vector3df *camera, RT_Intersec *inter) = 0;
	uint32_t			getColor() { return _color; }
	RT_Vector3df		*getPos() { return _pos; }

protected:
	RT_Vector3df	*_pos;
	uint32_t		_color;
	float			_shine;
};