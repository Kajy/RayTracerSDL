#include "RT.h"

class RT_Sphere : public RT_Object
{
public:
	RT_Sphere(int x, int y, int z, float radius, uint32_t color);
	~RT_Sphere();

	float	checkCollision(int x, int y, RT_Vector3df *camera, RT_Vector3df *vect);
	void	calcNormale(RT_Vector3df *vect, float k, RT_Vector3df *camera, RT_Intersec *inter);
private:
	float _radius;
};