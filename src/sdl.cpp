#include "sdl.hpp"
#include <iostream>

using namespace std;

bool SDL::init()
{
	if (SDL_Init(SDL_INIT_EVENTS) < 0) {
		cout << "SDL_Init: Couldn't start SDL" << SDL_GetError() << endl;
		throw "SDL_Init failed";
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		cout << "Failed to initialise linear texture rendering" << SDL_GetError() << endl;
		throw "SDL_SetHint failed";
	}

	return true;
}

void SDL::exit()
{
	SDL_Quit();
}

SDL::Window::Window(unsigned int width, unsigned int height, std::string title):
	window(NULL),
	surface(NULL),
	renderer(NULL),
	width(width),
	height(height),
	title(title),
	background(0,0,0)
{
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
									 		 SDL_WINDOWPOS_UNDEFINED,
											 width,
											 height,
											 SDL_WINDOW_SHOWN);

	if (window == NULL) {
		cout << "Failed to create window" << SDL_GetError() << endl;
		throw "SDL_CreateWindow failed";
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL) {
		cout << "Failed to create renderer" << SDL_GetError() << endl;
		throw "SDL_CreateRenderer failed";
	}

	SDL_RenderSetLogicalSize(renderer, width, height);

	surface = SDL_GetWindowSurface(window);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);

	refresh();
}

void SDL::Window::destroy()
{
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}

	if (window) {
		SDL_DestroyWindow(window);
		window = NULL;
	}
}

void SDL::Window::refresh()
{
	SDL_RenderPresent(renderer);
}

void SDL::Window::clear()
{
	fill(background);
}

void SDL::Window::fill(Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r(), color.g(), color.b(), color.a());
	SDL_RenderClear(renderer);
}

void SDL::Window::drawShape(Shape shape, Color color)
{
	//TODO
}

SDL::Color::Color() : red(0), green(0), blue(0), alpha(255) {}

SDL::Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : red(r), green(g), blue(b), alpha(a) {}