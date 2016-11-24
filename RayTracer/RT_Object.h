#ifndef RT_OBJECT_H_
#define RT_OBJECT_H_

#include "RT_Vector3df.h"
#include "RT_Intersec.h"
#include "RT_Light.h"

class RT_Object
{
public:
	virtual ~RT_Object() {};

	virtual	float		checkCollision(RT_Vector3df const &camera, RT_Vector3df const &vect) const = 0;
	virtual void		calcNormale(RT_Vector3df *vect, float k, RT_Vector3df const &camera, RT_Intersec *inter) const = 0;
	uint32_t			getColor() const { return _color; }
	RT_Vector3df const	&getPos() const { return _pos; }

protected:
	RT_Vector3df		_pos;
	uint32_t			_color;
	float				_shine;
};

#endif // !RT_OBJECT_H_