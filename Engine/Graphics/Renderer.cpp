#include"Renderer.h"
#include<SDL_image.h>
#include<iostream>
void henry::Renderer::Startup()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
}

void henry::Renderer::Shutdown()
{
	IMG_Quit();
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

	renderer = SDL_CreateRenderer(window, -1, 0);
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
	SDL_Rect dest{ (int)position.x, (int)position.y, static_cast<int> (size.x), static_cast<int>(size.y) };
	

	SDL_RenderCopyEx(renderer, texture->texture, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);

}

void henry::Renderer::Draw(std::shared_ptr<henry::Texture> texture, const Transform& transform)
{
	Vector2 size = texture->GetSize();
	size = size * transform.scale;

	SDL_Rect dest{ static_cast<int>(transform.position.x), static_cast<int> (transform.position.y), static_cast<int> (size.x), static_cast<int>(size.y) };


	SDL_RenderCopyEx(renderer, texture->texture, nullptr, &dest, transform.rotation, nullptr, SDL_FLIP_NONE);

}

