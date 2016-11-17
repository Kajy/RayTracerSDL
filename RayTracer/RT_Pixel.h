#include "RT.h"

class RT_Pixel
{
public:
	RT_Pixel(RT_Window *window);
	~RT_Pixel();
	SDL_Renderer	*getRenderer();
	void	setColor(uint32_t tmp_color);
	void	drawPixel(int x, int y);

	uint32_t	getcolor() { return _color; }

private:
	SDL_Renderer	*_Renderer;
	RT_Window		*_Window;
	uint32_t		_color;
	uint32_t		_x;
	uint32_t		_y;
};
