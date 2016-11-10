#include "RT.h"

class RT_Object
{
public:
	virtual ~RT_Object() {};

	virtual	float	checkCollision(RT_Vector3df *, RT_Vector3df *) = 0;

protected:
	RT_Vector3df	*_pos;
	float			_shine;
};