#include "RT_Window.h"



RT::Window::Window(const std::string title, int x, int y)
{
	_Done = false;
	_Event = new SDL_Event();
	_Title = title.c_str();
	_x = x;
	_y = y;

	// Initialisation de la SDL

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	// Création de la fenêtre

	this->_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (this->_Window == NULL)	{
		std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
	_Renderer = SDL_CreateRenderer(_Window, 0, SDL_RENDERER_ACCELERATED);
}


RT::Window::~Window()
{
}

void	RT::Window::waitEvent() const
{
	SDL_WaitEvent(_Event);
}
bool	RT::Window::checkEvent(SDL_WindowEventID id) const
{
	return (_Event->window.event == id);
}

SDL_Window	*RT::Window::getWindow() const
{
	return (_Window);
}

SDL_Renderer *RT::Window::getRenderer() const
{
	return (_Renderer);
}
void	RT::Window::drawPixel(uint32_t tmp_color, int x, int y) const
{
	SDL_SetRenderDrawColor(_Renderer, ((tmp_color & 0xff000000) >> 24), ((tmp_color & 0x00ff0000) >> 16), ((tmp_color & 0x0000ff00) >> 8), 0);
	SDL_RenderDrawPoint(_Renderer, x, y);
}