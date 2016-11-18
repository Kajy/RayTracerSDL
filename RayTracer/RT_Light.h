#include "RT.h"

#ifndef RT_LIGHT_H_
#define RT_LIGHT_H_

class RT_Light
{
public:
	RT_Light(float x, float y, float z, uint32_t color) {
		_pos = new RT_Vector3df(x, y, z);
		_color = color;
	};
	~RT_Light() {};

	RT_Vector3df	*getPos() const { return _pos; }
	uint32_t		getColor() const { return _color; }

private:
	RT_Vector3df	*_pos;
	uint32_t		_color;
};

#endif // !RT_LIGHT_H_