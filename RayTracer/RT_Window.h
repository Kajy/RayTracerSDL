#include "RT.h"

#ifndef RT_WINDOW_H_
#define RT_WINDOW_H_

namespace RT {

	class Window
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
		Window(const std::string title, int x, int y);
		~Window();
		SDL_Window	*getWindow() const;
		void	waitEvent() const;
		bool	checkEvent(SDL_WindowEventID id) const;
	};

}
#endif // !RT_WINDOW_H_