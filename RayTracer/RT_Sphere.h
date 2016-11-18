#include "RT.h"

#ifndef RT_SPHERE_H_
#define RT_SPHERE_H_

class RT_Sphere : public RT_Object
{
public:
	RT_Sphere(float x, float y, float z, float radius, uint32_t color);
	~RT_Sphere();

	float	checkCollision(int x, int y, RT_Vector3df const &camera, RT_Vector3df const &vect) const;
	void	calcNormale(RT_Vector3df *vect, float k, RT_Vector3df const &camera, RT_Intersec *inter) const;
private:
	float _radius;
};

#endif // !RT_SPHERE_H_