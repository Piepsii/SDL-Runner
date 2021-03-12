#include "endless_runner.hpp"

using namespace papaya;

namespace runner
{
	EndlessRunner::EndlessRunner(papaya::Runtime &runtime)
		: Game(runtime)
		, menu_(runtime, &play_)
		, play_(runtime, &menu_)
	{

	}

	EndlessRunner::~EndlessRunner()
	{

	}

	bool EndlessRunner::init()
	{
		set_active_state(&menu_);

		GameObject go{};

		FileStream stream = runtime_.filesystem().open("assets/test.zip");
		if( !stream.is_valid() )
		{
			return false;
		}

		FileArchive archive(stream);
		if( !archive.open() )
		{
			return false;
		}

		std::vector<char> atlas;
		if( archive.extract("atlas.txt", atlas) )
		{
			const char *text = atlas.data();

			int asd = 0;
		}
		std::string data(atlas.data(), atlas.size());
		return true;
	}

	void EndlessRunner::shut()
	{

	}

	bool EndlessRunner::tick(const papaya::Time &deltaTime)
	{
		return Game::tick(deltaTime);
	}
} // !runner
