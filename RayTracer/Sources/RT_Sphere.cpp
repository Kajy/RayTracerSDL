#include "RT_Sphere.h"

RT::Sphere::Sphere(float x, float y, float z, float radius, uint32_t color)
{
	_color = color;
	_shine = 0;
	_radius = radius;
	_pos.setValue(x, y, z);
}

RT::Sphere::~Sphere()
{
}

float	RT::Sphere::checkCollision(RT::Vector3df const &camera, RT::Vector3df const &vect) const
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

void	RT::Sphere::calcNormale(RT::Vector3df *vect, float k, RT::Vector3df const &camera, RT::Intersec *inter) const
{
	inter->setInter((camera._x + (k * vect->_x)), (camera._y + (k * vect->_y)), (camera._z + (k * vect->_z)));
	RT::Vector3df tmp(inter->getInter()._x - _pos._x, inter->getInter()._y - _pos._y, inter->getInter()._z - _pos._z);
	inter->setNormale(tmp._x, tmp._y, tmp._z);
	vect->normalize();
	float scal = vect->prodScalaire(inter->getNormale());

	float x = vect->_x - (2 * scal * inter->getNormale()._x);
	float y = vect->_y - (2 * scal * inter->getNormale()._y);
	float z = vect->_z - (2 * scal * inter->getNormale()._z);

	inter->setReflect(x, y, z);
}

