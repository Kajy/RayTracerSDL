#include "RT.h"

class RT_Pixel
{
public:
	RT_Pixel(RT_Window *window);
	~RT_Pixel();
	SDL_Renderer	*getRenderer();
	void	setColor(int R, int G, int B);
	void	drawPixel(int x, int y);
	void	setDist(float dist);

private:
	SDL_Renderer	*_Renderer;
	RT_Window		*_Window;
	uint32_t		_R;
	uint32_t		_G;
	uint32_t		_B;
	uint32_t		_prevR;
	uint32_t		_prevG;
	uint32_t		_prevB;
	uint32_t		_x;
	uint32_t		_y;
	float			_distInter;
};
