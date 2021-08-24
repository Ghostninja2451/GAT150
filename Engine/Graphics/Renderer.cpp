#include"Renderer.h"
#include"Math/MathUtils.h"
#include<SDL_ttf.h>
#include<SDL_image.h>
#include<iostream>
void henry::Renderer::Startup()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	TTF_Init();
}

void henry::Renderer::Shutdown()
{
	IMG_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void henry::Renderer::Update(float dt)
{

}

void henry::Renderer::Create(const std::string& name, int width, int height)
{
	window = SDL_CreateWindow(name.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
}

void henry::Renderer::BeginFrame()
{
	SDL_RenderClear(renderer);
}

void henry::Renderer::EndFrame()
{
	SDL_RenderPresent(renderer);

}

void henry::Renderer::Draw(std::shared_ptr<henry::Texture> texture, const Vector2& position, float angle, const Vector2& scale)
{
	Vector2 size = texture->GetSize();
	size = size * scale;
	Vector2 newPosition = position - (size * 0.5f);

	SDL_Rect rect;

	rect.x = static_cast<int>(newPosition.x);
	rect.y = static_cast<int>(newPosition.y);
	rect.w = static_cast<int>(size.x);
	rect.h = static_cast<int>(size.y);

	SDL_RenderCopyEx(renderer, texture->texture, nullptr, &rect, henry::RadToDeg(angle), nullptr, SDL_FLIP_NONE);

}

void henry::Renderer::Draw(std::shared_ptr<henry::Texture> texture, const Transform& transform)
{
	Vector2 size = texture->GetSize();
	size = size * transform.scale;

	Vector2 newPosition = transform.position - (size * 0.5f);

	SDL_Rect dest;
	dest.x = static_cast<int>(newPosition.x);
	dest.y = static_cast<int>(newPosition.y);
	dest.w = static_cast<int>(size.x);
	dest.h = static_cast<int>(size.y);

	SDL_RenderCopyEx(renderer, texture->texture, nullptr, &dest,henry::RadToDeg(transform.rotation), nullptr, SDL_FLIP_NONE);

}

void henry::Renderer::Draw(std::shared_ptr<henry::Texture> texture, const SDL_Rect& source, const Transform& transform)
{
	Vector2 size = Vector2{ source.w, source.h };
	size = size * transform.scale;

	Vector2 newPosition = transform.position - (size * 0.5f);

	SDL_Rect dest;
	dest.x = static_cast<int>(newPosition.x);
	dest.y = static_cast<int>(newPosition.y);
	dest.w = static_cast<int>(size.x);
	dest.h = static_cast<int>(size.y);

	SDL_RenderCopyEx(renderer, texture->texture, &source, &dest, henry::RadToDeg(transform.rotation), nullptr, SDL_FLIP_NONE);
}



