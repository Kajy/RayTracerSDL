#include "RT_Window.h"



RT_Window::RT_Window(const std::string title, int x, int y)
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
}


RT_Window::~RT_Window()
{
}

void	RT_Window::waitEvent() const
{
	SDL_WaitEvent(_Event);
}
bool	RT_Window::checkEvent(SDL_WindowEventID id) const
{
	return (_Event->window.event == id);
}

SDL_Window	*RT_Window::getWindow() const
{
	return (_Window);
}