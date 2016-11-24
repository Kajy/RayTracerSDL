#ifndef RT_PLANE_H_
#define RT_PLANE_H_

#include "RT_Vector3df.h"
#include "RT_Object.h"
#include "RT_Intersec.h"
#include "RT_Light.h"

class RT_Plane : public RT_Object
{
public:
	RT_Plane(float X, float Y, float Z, float h, uint32_t color) :
		_X(X),
		_Y(Y),
		_Z(Z),
		_hight(h)
	{
		_color = color;
	}
	~RT_Plane() {};

	float		checkCollision(RT_Vector3df const &camera, RT_Vector3df const &vect) const;
	void		calcNormale(RT_Vector3df *vect, float k, RT_Vector3df const &camera, RT_Intersec *inter) const;

private:
	float	_X;
	float	_Y;
	float	_Z;
	float	_hight;
};

#endif // !RT_PLANE_H_