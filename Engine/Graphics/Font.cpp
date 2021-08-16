#include"Font.h"
#include<cassert>
namespace henry
{
	Font::~Font()
	{
		if (font != nullptr)
		{
			TTF_CloseFont(font);
		}
	}

	bool Font::Load(const std::string& name, void* data)
	{
		assert(data);

		font = TTF_OpenFont(name.c_str(), *(static_cast<int*>(data))); //<TTF_OpenFont, use c string of name, cast data to int* then dereference for pixel size>
			if (font == nullptr)
			{
				std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
				return false;
			}

		return true;

	}

	SDL_Surface* Font::CreateSurface(const std::string& text, const henry::Color& color)
	{
		//SDL_Color color = (1,1,1);
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), SDL_Color(color));//<TTF_RenderText_Solid, use TTF fontand color for the parameters>
			if (surface == nullptr)
			{
				std::cout << "TTF_RenderText_Solid Error: " << SDL_GetError() << std::endl;
			}
		return surface;

	}

}
