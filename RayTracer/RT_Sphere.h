#include "RT.h"

class RT_Sphere : public RT_Object
{
public:
	RT_Sphere(float radius);
	~RT_Sphere();

	float	checkCollision(RT_Vector3df *vect, RT_Vector3df *camera);
private:
	float _radius;
};