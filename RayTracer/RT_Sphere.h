#include "RT.h"

class RT_Sphere
{
public:
	RT_Sphere(float x, float y, float z, float radius) {
		_origin = new RT_Vector3df(x, y, z);
	};
	~RT_Sphere() {};

private:
	float		_radius;
	RT_Vector3df	*_origin;
	
};