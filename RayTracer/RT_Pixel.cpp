#include "RT_Pixel.h"

RT_Pixel::RT_Pixel(RT_Window *window)
{
	_Renderer = SDL_CreateRenderer(window->getWindow(), 0, SDL_RENDERER_ACCELERATED);
	_Window = window;
	_color = 0;
	_x = 0;
	_y = 0;
}

RT_Pixel::~RT_Pixel()
{
}

void	RT_Pixel::setColor(uint32_t tmp_color)
{
	SDL_SetRenderDrawColor(_Renderer, ((tmp_color & 0xff000000) >> 24), ((tmp_color & 0x00ff0000) >> 16), ((tmp_color & 0x0000ff00) >> 8), 0);
	_color = tmp_color;
}

SDL_Renderer	*RT_Pixel::getRenderer() const
{
	return (_Renderer);
}

void	RT_Pixel::drawPixel(int x, int y) const
{
	SDL_RenderDrawPoint(_Renderer, x, y);
}