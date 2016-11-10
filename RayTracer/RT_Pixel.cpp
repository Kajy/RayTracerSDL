#include "RT_Pixel.h"

RT_Pixel::RT_Pixel(RT_Window *window)
{
	_Renderer = SDL_CreateRenderer(window->getWindow(), 0, SDL_RENDERER_ACCELERATED);
	_Window = window;
	_R = 0;
	_G = 0;
	_B = 0;
	_prevR = 0;
	_prevG = 0;
	_prevB = 0;
	_x = 0;
	_y = 0;
}

RT_Pixel::~RT_Pixel()
{
}

void	RT_Pixel::setColor(int R, int G, int B)
{
	SDL_SetRenderDrawColor(_Renderer, R, G, B, 0);
	_prevR = _R;
	_prevG = _G;
	_prevB = _B;
	_R = R;
	_G = G;
	_B = B;
}

SDL_Renderer	*RT_Pixel::getRenderer()
{
	return (_Renderer);
}

void	RT_Pixel::drawPixel(int x, int y)
{
	SDL_RenderDrawPoint(_Renderer, x, y);
}