#include "RT_Plane.h"

float	RT::Plane::checkCollision(RT::Vector3df const &camera, RT::Vector3df const &vect) const
{
	if (vect._z != 0) {
		float k = - ((_X * camera._x) + (_Y * camera._y) + (_Z * camera._z) - _hight) / (_X * vect._x + _Y * vect._y + _Z * vect._z);

		if (k >= 0)
			return (k);
	}

	return (-1);
}

void	RT::Plane::calcNormale(RT::Vector3df *vect, float k, RT::Vector3df const &camera, RT::Intersec *inter) const
{
	inter->setInter((camera._x + (k * vect->_x)), (camera._y + (k * vect->_y)), (camera._z + (k * vect->_z)));
	RT::Vector3df tmp(_X, _Y, _Z);
	inter->setNormale(tmp._x, tmp._y, tmp._z);
	float	scal = vect->_x * inter->getNormale()._x + vect->_y * inter->getNormale()._y + vect->_z * inter->getNormale()._z;
	inter->setReflect(vect->_x - ((2 * scal) * inter->getNormale()._x), vect->_y - ((2 * scal) * inter->getNormale()._y), vect->_z - ((2 * scal) * inter->getNormale()._z));
	tmp = inter->getReflect();
	inter->setReflect(tmp._x, tmp._y, tmp._z);
}