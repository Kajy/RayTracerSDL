#ifndef RT_PLANE_H_
#define RT_PLANE_H_

#include "RT_Vector3df.h"
#include "RT_Object.h"
#include "RT_Intersec.h"
#include "RT_Light.h"

namespace RT {

	class Plane : public Object
	{
	public:
		Plane(float X, float Y, float Z, float h, uint32_t color) :
			_X(X),
			_Y(Y),
			_Z(Z),
			_hight(h)
		{
			_color = color;
		}
		~Plane() {};

		float		checkCollision(RT::Vector3df const &camera, RT::Vector3df const &vect) const;
		void		calcNormale(RT::Vector3df *vect, float k, RT::Vector3df const &camera, RT::Intersec *inter) const;

	private:
		float	_X;
		float	_Y;
		float	_Z;
		float	_hight;
	};
}

#endif // !RT_PLANE_H_