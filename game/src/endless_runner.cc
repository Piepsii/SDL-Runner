#include "endless_runner.hpp"

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