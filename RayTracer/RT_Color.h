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

	void		tranformColorWithLightsCoef(uint32_t colorBase, uint32_t colorLight, float LightCoef) {
		_Rf = ((colorBase & 0xff000000) >> 24) * LightCoef + (((colorLight & 0xff000000) >> 24) * pow(LightCoef, 50));
		_Bf = ((colorBase & 0x00ff0000) >> 16) * LightCoef + (((colorLight & 0x00ff0000) >> 16) * pow(LightCoef, 50));
		_Gf = ((colorBase & 0x0000ff00) >> 8) * LightCoef + (((colorLight & 0x0000ff00) >> 8) * pow(LightCoef, 50));
		_Rf = _Rf > 255 ? 255 : _Rf;
		_Gf = _Gf > 255 ? 255 : _Gf;
		_Bf = _Bf > 255 ? 255 : _Bf;
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