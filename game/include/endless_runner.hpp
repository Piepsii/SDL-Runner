#pragma once

#include <papaya.hpp>
#include "menu_state.hpp"
#include "play_state.hpp"

namespace runner
{
	class EndlessRunner : public papaya::Game
	{
	public:
		EndlessRunner(papaya::Runtime &runtime);
		~EndlessRunner();

		virtual bool init();
		virtual void shut();
		virtual bool tick(const papaya::Time &deltaTime);

	private:
		MenuState menu_;
		PlayState play_;
	};
} // !runner