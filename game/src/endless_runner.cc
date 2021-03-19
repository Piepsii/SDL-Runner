#include "endless_runner.hpp"
#include "components/scrollable_component.hpp"

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
		runtime_.textures().load("assets/welcome_message.png");
		runtime_.textures().load("assets/parallax_1.png");
		runtime_.textures().load("assets/parallax_2.png");
		runtime_.textures().load("assets/octopus_1.png");
		runtime_.textures().load("assets/octopus_2.png");
		runtime_.textures().load("assets/coral_1.png");
		runtime_.textures().load("assets/coral_2.png");
		runtime_.textures().load("assets/transparent.png");
		runtime_.textures().load("assets/0.png");
		runtime_.textures().load("assets/1.png");
		runtime_.textures().load("assets/2.png");
		runtime_.textures().load("assets/3.png");
		runtime_.textures().load("assets/4.png");
		runtime_.textures().load("assets/5.png");
		runtime_.textures().load("assets/6.png");
		runtime_.textures().load("assets/7.png");
		runtime_.textures().load("assets/8.png");
		runtime_.textures().load("assets/9.png");

		ScrollableComponent::transparent_texture_ = runtime_.textures().find("assets/transparent.png");

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

		menu_.init();
		play_.init();

		set_active_state(&menu_);

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
