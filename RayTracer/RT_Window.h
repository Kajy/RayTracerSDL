#include <SDL.h>
#include <string>
#include <iostream>

class RT_Window
{
private:
	SDL_Window	*_Window;
	SDL_Event	*_Event;
	bool		_Done;
	int			_x;
	int			_y;
	const char	*_Title;

public:
	RT_Window(const std::string title, int x, int y);
	~RT_Window();
	void	waitEvent();
	bool	checkEvent(SDL_WindowEventID id);
};

