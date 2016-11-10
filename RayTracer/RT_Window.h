#include "RT.h"

class RT_Window
{
private:
	SDL_Window		*_Window;
	SDL_Event		*_Event;
	SDL_GLContext	_OpenGLContext;
	bool			_Done;
	int				_x;
	int				_y;
	const char		*_Title;

public:
	RT_Window(const std::string title, int x, int y);
	~RT_Window();
	SDL_Window	*getWindow();
	void	waitEvent();
	bool	checkEvent(SDL_WindowEventID id);
};

