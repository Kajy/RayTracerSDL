#include "RT_Sphere.h"

RT_Sphere::RT_Sphere(float x, float y, float z, float radius, uint32_t color)
{
	_color = color;
	_shine = 0;
	_radius = radius;
	_pos.setValue(x, y, z);
}

RT_Sphere::~RT_Sphere()
{
}

float	RT_Sphere::checkCollision(int x, int y, RT_Vector3df const &camera, RT_Vector3df const &vect) const
{
	float a, b, c, d, k1, k2;

	a = (vect._x * vect._x) + (vect._y * vect._y) + (vect._z * vect._z);
	b = 2 * (((camera._x - _pos._x) * vect._x) + ((camera._y - _pos._y) * vect._y) + ((camera._z - _pos._z) * vect._z));
	c = ((camera._x - _pos._x) * (camera._x - _pos._x)) + ((camera._y - _pos._y) * (camera._y - _pos._y)) + ((camera._z - _pos._z) * (camera._z - _pos._z)) - (_radius * _radius);
	d = (b * b) - (4 * a * c);

	k1 = (-b + sqrt(d)) / (2 * a);
	k2 = (-b - sqrt(d)) / (2 * a);
	if (k1 > 0 || k2 > 0) {
		return (k1 < k2 ? (k1 < 0 ? k2 : k1) : (k2 < 0 ? k1 : k2));
	}
	return (-1);
}

void	RT_Sphere::calcNormale(RT_Vector3df *vect, float k, RT_Vector3df const &camera, RT_Intersec *inter) const
{
	inter->setInter((camera._x + (k * vect->_x)), (camera._y + (k * vect->_y)), (camera._z + (k * vect->_z)));
	inter->setNormale(inter->getInter()->_x - _pos._x, inter->getInter()->_y - _pos._y, inter->getInter()->_z - _pos._z);
	inter->getNormale()->normalize();
	float	scal = vect->_x * inter->getNormale()->_x + vect->_y * inter->getNormale()->_y + vect->_z * inter->getNormale()->_z;
	inter->setReflect(vect->_x - ((2 * scal) * inter->getNormale()->_x), vect->_y - ((2 * scal) * inter->getNormale()->_y), vect->_z - ((2 * scal) * inter->getNormale()->_z));
	inter->getReflect()->normalize();
}