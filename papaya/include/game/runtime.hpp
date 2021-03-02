#pragma once

#include <platform/time.hpp>

namespace papaya
{
	class Dispatcher;
	class Input;
	class FileSystem;
	class TextureStorage;
	class Renderer;

	class Runtime
	{
	public:
		Runtime(Dispatcher &dispatcher,
				  Input &input,
				  FileSystem &filesystem,
				  TextureStorage &textures,
				  Renderer &renderer);

		Time deltaTime();
		Dispatcher &dispatcher();
		Input &input();
		FileSystem &filesystem();
		TextureStorage &textures();
		Renderer &renderer();

	private:
		Dispatcher &dispatcher_;
		Input &input_;
		FileSystem &filesystem_;
		TextureStorage &textures_;
		Renderer &renderer_;
	};
} // !papaya