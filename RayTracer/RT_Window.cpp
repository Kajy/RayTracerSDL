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

	// Version d'OpenGL

	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


	// Double Buffer

	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Création de la fenêtre

	this->_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (this->_Window == NULL)	{
		std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
	//_OpenGLContext = SDL_GL_CreateContext(_Window);

	/*if (this->_OpenGLContext == 0) {
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyWindow(_Window);
		SDL_Quit();
	}*/
}


RT_Window::~RT_Window()
{
}

void	RT_Window::waitEvent()
{
	SDL_WaitEvent(_Event);
}
bool	RT_Window::checkEvent(SDL_WindowEventID id)
{
	return (_Event->window.event == id);
}

SDL_Window	*RT_Window::getWindow()
{
	return (_Window);
}