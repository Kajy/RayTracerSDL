#include "RT.h"

class RT_Vector3df
{
public:
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
		float norm = sqrt((_x * _x) + (_y * _y) + (_z * _z));
		_x /= norm;
		_y /= norm;
		_z /= norm;
	}

public:
	float	_x;
	float	_y;
	float	_z;
};