// endless_runner.hpp

#pragma once

#include <papaya.hpp>

#include <components/animation_component.hpp>
#include <components/collision_component.hpp>
#include <components/jump_component.hpp>
#include <components/scrollable_component.hpp>
#include <components/text_component.hpp>

#include "states/menu_state.hpp"
#include "states/play_state.hpp"
#include "states/game_over_state.hpp"

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
		GameOverState game_over_;

	};
} // !runner
