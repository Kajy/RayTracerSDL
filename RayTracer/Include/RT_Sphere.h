#ifndef RT_SPHERE_H_
#define RT_SPHERE_H_

#include "RT_Vector3df.h"
#include "RT_Object.h"
#include "RT_Intersec.h"
#include "RT_Light.h"

namespace RT {

	class Sphere : public Object
	{
	public:
		Sphere(float x, float y, float z, float radius, uint32_t color);
		~Sphere();

		float		checkCollision(RT::Vector3df const &camera, RT::Vector3df const &vect) const;
		void		calcNormale(RT::Vector3df *vect, float k, RT::Vector3df const &camera, RT::Intersec *inter) const;

	private:
		float _radius;
	};
}

#endif // !RT_SPHERE_H_