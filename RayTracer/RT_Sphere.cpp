#include "RT.h"

RT_Sphere::RT_Sphere(float radius)
{
	_radius = radius;
}

RT_Sphere::~RT_Sphere()
{
}

float	RT_Sphere::checkCollision(RT_Vector3df *vect, RT_Vector3df *camera)
{
	float a, b, c, d, k1, k2;

	a = (vect->_x * vect->_x) + (vect->_y * vect->_y) + (vect->_z * vect->_z);
	b = 2 * ((camera->_x * vect->_x) + (camera->_y * vect->_y) + (camera->_z * vect->_z));
	c = (camera->_x * camera->_x) + (camera->_y * camera->_y) + (camera->_z * camera->_z) - (_radius * _radius);
	d = (b * b) - (4 * a * c);

	k1 = (-b + sqrt(d)) / (2 * a);
	k2 = (-b - sqrt(d)) / (2 * a);
	if (k1 > 0 || k2 > 0) {
		return (k1 < k2 ? (k1 < 0 ? k2 : k1) : (k2 < 0 ? k1 : k2));
	}
	return (-1);
}