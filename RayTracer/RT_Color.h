#include "RT.h"

class RT_Color
{
public:
	RT_Color() :
		_color(0),
		_Rf(0),
		_Gf(0),
		_Bf(0)
	{};
	RT_Color(uint32_t color) :
		_Rf((color & 0xff000000) >> 24),
		_Gf((color & 0x00ff0000) >> 16),
		_Bf((color & 0x0000ff00) >> 8),
		_color(color)
	{};

	~RT_Color() {};

	void	setColor(uint32_t color) {
		_Rf = (color & 0xff000000) >> 24;
		_Gf = (color & 0x00ff0000) >> 16;
		_Bf = (color & 0x0000ff00) >> 8;
		_color = color;
	}

	void	setColorf(float R, float G, float B) {
		_Rf = R;
		_Gf = G;
		_Bf = B;
	}

	void	mulColor(float coef) {
		_Rf *= coef;
		_Gf *= coef;
		_Bf *= coef;
	}

	void	mulColor(float coef, float coef2, float coef3) {
		_Rf *= coef;
		_Gf *= coef2;
		_Bf *= coef3;
	}

	void	divColor(float coef) {
		_Rf /= coef;
		_Gf /= coef;
		_Bf /= coef;
	}

	void	divColor(float coef, float coef2, float coef3) {
		_Rf /= coef;
		_Gf /= coef2;
		_Bf /= coef3;
	}

	void	addColor(float coef) {
		_Rf += coef;
		_Gf += coef;
		_Bf += coef;
	}

	void	addColor(float coef, float coef2, float coef3) {
		_Rf += coef;
		_Gf += coef2;
		_Bf += coef3;
	}

	uint32_t	getColor() {
		return (((unsigned int)(_Rf) << 24) + ((unsigned int)(_Gf)  << 16) + ((unsigned int)(_Bf) << 8));
	}

	void		tranformColorWithLightsCoef(uint32_t colorBase, RT_Light const &light, float LightCoef, float ReflectCoef) {
		_Rf = (((colorBase & 0xff000000) >> 24) * LightCoef + ((((light.getColor() & 0xff000000) - (colorBase & 0xff000000)) >> 24) * ReflectCoef))  * light.getDiffuseCoef();
		_Bf = (((colorBase & 0x00ff0000) >> 16) * LightCoef + ((((light.getColor() & 0x00ff0000) - (colorBase & 0x00ff0000)) >> 16) * ReflectCoef)) * light.getDiffuseCoef();
		_Gf = (((colorBase & 0x0000ff00) >> 8) * LightCoef + ((((light.getColor() & 0x0000ff00) - (colorBase & 0x0000ff00)) >> 8) * ReflectCoef)) * light.getDiffuseCoef();
	}

	float	getR() const { return _Rf; }
	float	getG() const { return _Gf; }
	float	getB() const { return _Bf; }
private:

	uint32_t	_color;

	float		_Rf;
	float		_Gf;
	float		_Bf;
};