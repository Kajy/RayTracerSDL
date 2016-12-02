#include "RT_Pixel.h"

RT::Pixel::Pixel(RT::Window *window)
{
	_Renderer = SDL_CreateRenderer(window->getWindow(), 0, SDL_RENDERER_ACCELERATED);
	//_Renderer = SDL_GetRenderer(window->getWindow());
	_Window = window;
	_color = 0;
	_x = 0;
	_y = 0;
}

RT::Pixel::~Pixel()
{
}

void	RT::Pixel::setColor(uint32_t tmp_color)
{
	SDL_SetRenderDrawColor(_Renderer, ((tmp_color & 0xff000000) >> 24), ((tmp_color & 0x00ff0000) >> 16), ((tmp_color & 0x0000ff00) >> 8), 0);
	_color = tmp_color;
}

SDL_Renderer	*RT::Pixel::getRenderer() const
{
	return (_Renderer);
}

void	RT::Pixel::drawPixel(int x, int y) const
{
	SDL_RenderDrawPoint(_Renderer, x, y);
}