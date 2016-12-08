#ifndef RT_OBJECT_H_
#define RT_OBJECT_H_

#include "RT_Vector3df.h"
#include "RT_Intersec.h"
#include "RT_Light.h"

namespace RT {

	class Object
	{
	public:
		virtual ~Object() {};

		virtual	float		checkCollision(RT::Vector3df const &camera, RT::Vector3df const &vect) const = 0;
		virtual void		calcNormale(RT::Vector3df *vect, float k, RT::Vector3df const &camera, RT::Intersec *inter) const = 0;
		uint32_t			getColor() const { return _color; }
		RT::Vector3df const	&getPos() const { return _pos; }

	protected:
		RT::Vector3df		_pos;
		uint32_t			_color;
		float				_shine;
	};
}

#endif // !RT_OBJECT_H_