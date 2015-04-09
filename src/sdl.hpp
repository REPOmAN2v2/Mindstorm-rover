#ifndef SDL_HPP_INCLUDED
#define SDL_HPP_INCLUDED

#include <SDL2/SDL.h>
#include <stdint.h>
#include <string>

namespace SDL
{
	bool init();
	void exit();

	class Color {
	public:
		explicit Color();
		explicit Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		uint8_t r() {return red;};
		uint8_t g() {return green;};
		uint8_t b() {return blue;};
		uint8_t a() {return alpha;};
	private:
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t alpha;
	};

	class Window {
	public:
		explicit Window(unsigned int width, unsigned int height, std::string title);
		void destroy();
		void refresh();
		void fill(Color color);
		void clear();
		void drawRect(SDL_Rect rect, Color color);
	private:
		SDL_Window *window;
		SDL_Surface *surface;
		SDL_Renderer *renderer;
		unsigned int width, height;
		std::string title;
		Color background;
	};
}

#endif