#include "gs_menu.h"
#include "renderer.h"
#include "con_vars.h"

void MenuState::init()
{
	//TODO(Xwing); Start main menu music
}

void MenuState::shutdown()
{
}

void MenuState::update()
{
}

void MenuState::draw()
{
	g_renderer->draw_text("Play", 50/*g_cvars->resolution_x*/, 250, 17, SDL_Color{ 255, 255, 255, 255});
	g_renderer->draw_text("Options", 50/*g_cvars->resolution_x*/, 300, 17, SDL_Color{ 255, 255, 255, 255 });
	g_renderer->draw_text("Credits", 50/*g_cvars->resolution_x*/, 350, 17, SDL_Color{ 255, 255, 255, 255 });
	g_renderer->draw_text("Quit", 50/*g_cvars->resolution_x*/, 400, 17, SDL_Color{ 255, 255, 255, 255 });

}
