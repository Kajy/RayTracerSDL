#include "RT.h"

#ifndef RT_VECTOR_H_
#define RT_VECTOR_H_


namespace RT {

	class Vector3df
	{
	public:
		Vector3df() :
			_x(0),
			_y(0),
			_z(0)
		{};
		Vector3df(float x, float y, float z) :
			_x(x),
			_y(y),
			_z(z)
		{};
		~Vector3df() {};

		void	setValue(float x, float y, float z)
		{
			_x = x;
			_y = y;
			_z = z;
		}

		void	normalize() {
			float norm = sqrtf((_x * _x) + (_y * _y) + (_z * _z));
			_x /= norm;
			_y /= norm;
			_z /= norm;
		}

		float	prodScalaire(RT::Vector3df v2) {
			return ((_x * v2._x) + (_y * v2._y) + (_z * v2._z));
		}

	public:
		float	_x;
		float	_y;
		float	_z;
	};
}

#endif // !RT_VECTOR_H_