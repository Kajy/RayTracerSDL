#ifndef RT_WINDOW_H_
#define RT_WINDOW_H_

#include "RT.h"

namespace RT {

	class Window
	{
	private:
		SDL_Window		*_Window;
		SDL_Event		*_Event;
		SDL_GLContext	_OpenGLContext;
		SDL_Renderer	*_Renderer;
		bool			_Done;
		int				_x;
		int				_y;
		const char		*_Title;

	public:
		Window(const std::string title, int x, int y);
		~Window();
		SDL_Window		*getWindow() const;
		SDL_Renderer	*getRenderer() const;
		void			waitEvent() const;
		bool			checkEvent(SDL_WindowEventID id) const;
		void			drawPixel(uint32_t tmp_color, int x, int y) const;
	};

}
#endif // !RT_WINDOW_H_