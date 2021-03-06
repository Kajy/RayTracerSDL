#ifndef RT_INTERSEC_H_
#define RT_INTERSEC_H_

#include "RT_Vector3df.h"

namespace RT {

	class Intersec
	{
	public:
		Intersec() {
			_k = -1;
			_color = 0;
		};
		~Intersec() {};

		void	setColor(uint32_t color) { _color = color; }
		void	setDist(float k) { _k = k; }
		void	setInter(float x, float y, float z) { _inter.setValue(x, y, z); }
		void	setNormale(float x, float y, float z) { _normale.setValue(x, y, z); _normale.normalize(); }
		void	setReflect(float x, float y, float z) { _reflect.setValue(x, y, z); _reflect.normalize(); }

		float			getDist() const { return _k; }
		uint32_t		getColor() const { return _color; }
		RT::Vector3df	getNormale() const { return _normale; }
		RT::Vector3df	getInter() const { return _inter; }
		RT::Vector3df	getReflect() const { return _reflect; }


	private:
		float			_k;
		uint32_t		_color;
		RT::Vector3df	_inter;
		RT::Vector3df	_normale;
		RT::Vector3df	_reflect;

	};
}

#endif // !RT_INTERSEC_H_