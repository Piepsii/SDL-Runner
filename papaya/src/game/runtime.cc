#include "game/runtime.hpp"

namespace papaya
{
	Runtime::Runtime(Dispatcher &dispatcher,
						  Input &input,
						  FileSystem &filesystem,
						  TextureStorage &textures,
						  Renderer &renderer)
		: dispatcher_(dispatcher)
		, input_(input)
		, filesystem_(filesystem)
		, textures_(textures)
		, renderer_(renderer)
	{

	}

	Time Runtime::deltaTime()
	{
		static Time previous;
		Time current = Time::now();
		Time dt = current - previous;
		previous = current;

		return dt;
	}

	Dispatcher &Runtime::dispatcher()
	{
		return dispatcher_;
	}

	Input &Runtime::input()
	{
		return input_;
	}

	FileSystem &Runtime::filesystem()
	{
		return filesystem_;
	}

	TextureStorage &Runtime::textures()
	{
		return textures_;
	}

	Renderer &Runtime::renderer()
	{
		return renderer_;
	}

} // ! papaya