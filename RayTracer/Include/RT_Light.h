#ifndef RT_LIGHT_H_
#define RT_LIGHT_H_

namespace RT {

	class Light
	{
	public:
		Light(float x, float y, float z, uint32_t color) {
			_pos.setValue(x, y, z);
			_color = color;
			_diffuseCoef = 1;
		};

		Light(float x, float y, float z, uint32_t color, float intensity) {
			_pos.setValue(x, y, z);
			_color = color;
			_diffuseCoef = intensity;
		};
		~Light() {};

		RT::Vector3df	getPos() const { return _pos; }
		uint32_t		getColor() const { return _color; }
		float			getDiffuseCoef() const { return _diffuseCoef; }

	private:
		RT::Vector3df	_pos;
		uint32_t		_color;
		float			_diffuseCoef;
	};
}

#endif // !RT_LIGHT_H_