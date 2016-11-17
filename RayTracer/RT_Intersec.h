#include "RT.h"

class RT_Intersec
{
public:
	RT_Intersec() { 
		_k = -1;
		_color = 0;
		_inter = new RT_Vector3df(0, 0, 0);
		_normale = new RT_Vector3df(0, 0, 0);
	};
	~RT_Intersec() {};

	void	setColor(uint32_t color) { _color = color; }
	void	setDist(float k) { _k = k; }
	void	setInter(float x, float y, float z) { _inter->setValue(x, y, z); }
	void	setNormale(float x, float y, float z) { _normale->setValue(x, y, z); }

	float			getDist() { return _k; }
	uint32_t		getColor() { return _color; }
	RT_Vector3df	*getNormale() { return _normale; }
	RT_Vector3df	*getInter() { return _inter; }
	

private:
	float			_k;
	uint32_t		_color;
	RT_Vector3df	*_inter;
	RT_Vector3df	*_normale;

};