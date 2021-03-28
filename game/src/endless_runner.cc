// endless_runner.cc

#include "endless_runner.hpp"
#include "components/scrollable_component.hpp"

using namespace papaya;

namespace runner
{
	EndlessRunner::EndlessRunner(papaya::Runtime &runtime)
		: Game(runtime)
		, menu_(runtime, &play_)
		, play_(runtime, &menu_, &game_over_)
		, game_over_(runtime, &play_)
	{

	}

	EndlessRunner::~EndlessRunner()
	{

	}

	bool EndlessRunner::init()
	{
		runtime_.textures().load("assets/welcome_message.png");
		runtime_.textures().load("assets/game_over_message.png");
		runtime_.textures().load("assets/high_score_message.png");
		runtime_.textures().load("assets/score_message.png");
		runtime_.textures().load("assets/parallax_1.png");
		runtime_.textures().load("assets/fish.png");
		runtime_.textures().load("assets/shark.png");
		runtime_.textures().load("assets/octopus.png");
		runtime_.textures().load("assets/coral_1.png");
		runtime_.textures().load("assets/coral_2.png");
		runtime_.textures().load("assets/transparent.png");
		runtime_.textures().load("assets/digits.png");

		ScrollableComponent::transparent_texture_ = runtime_.textures().find("assets/transparent.png");


		menu_.init();
		play_.init();
		game_over_.init();

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
