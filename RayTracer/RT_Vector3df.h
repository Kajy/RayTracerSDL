#include "RT.h"

#ifndef RT_VECTOR_H_
#define RT_VECTOR_H_



class RT_Vector3df
{
public:
	RT_Vector3df() :
		_x(0),
		_y(0),
		_z(0)
	{};
	RT_Vector3df(float x, float y, float z) :
		_x(x),
		_y(y),
		_z(z)
	{};
	~RT_Vector3df() {};

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

public:
	float	_x;
	float	_y;
	float	_z;
};

#endif // !RT_VECTOR_H_