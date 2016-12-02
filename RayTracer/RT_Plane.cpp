#include "RT_Plane.h"

float	RT_Plane::checkCollision(RT_Vector3df const &camera, RT_Vector3df const &vect) const
{
	if (vect._z != 0) {
		float k = - ((_X * camera._x) + (_Y * camera._y) + (_Z * camera._z)) / (_X * vect._x + _Y * vect._y + _Z * vect._z);

		if (k >= 0)
			return (k);
	}

	return (-1);
}

void	RT_Plane::calcNormale(RT_Vector3df *vect, float k, RT_Vector3df const &camera, RT_Intersec *inter) const
{
	inter->setInter((camera._x + (k * vect->_x)), (camera._y + (k * vect->_y)), (camera._z + (k * vect->_z)));
	RT_Vector3df tmp(_X, _Y, _Z);
	inter->setNormale(tmp._x, tmp._y, tmp._z);
	float	scal = vect->_x * inter->getNormale()._x + vect->_y * inter->getNormale()._y + vect->_z * inter->getNormale()._z;
	inter->setReflect(vect->_x - ((2 * scal) * inter->getNormale()._x), vect->_y - ((2 * scal) * inter->getNormale()._y), vect->_z - ((2 * scal) * inter->getNormale()._z));
	tmp = inter->getReflect();
	inter->setReflect(tmp._x, tmp._y, tmp._z);
}