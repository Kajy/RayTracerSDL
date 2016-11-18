#include "RT.h"

#ifndef RT_INTERSEC_H_
#define RT_INTERSEC_H_

class RT_Intersec
{
public:
	RT_Intersec() { 
		_k = -1;
		_color = 0;
		_inter = new RT_Vector3df(0, 0, 0);
		_normale = new RT_Vector3df(0, 0, 0);
		_reflect = new RT_Vector3df(0, 0, 0);
	};
	~RT_Intersec() {};

	void	setColor(uint32_t color) { _color = color; }
	void	setDist(float k) { _k = k; }
	void	setInter(float x, float y, float z) { _inter->setValue(x, y, z); }
	void	setNormale(float x, float y, float z) { _normale->setValue(x, y, z); }
	void	setReflect(float x, float y, float z) { _reflect->setValue(x, y, z); }

	float			getDist() const { return _k; }
	uint32_t		getColor() const { return _color; }
	RT_Vector3df	*getNormale() const { return _normale; }
	RT_Vector3df	*getInter() const { return _inter; }
	RT_Vector3df	*getReflect() const { return _reflect; }
	

private:
	float			_k;
	uint32_t		_color;
	RT_Vector3df	*_inter;
	RT_Vector3df	*_normale;
	RT_Vector3df	*_reflect;

};

#endif // !RT_INTERSEC_H_