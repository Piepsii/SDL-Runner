#include "play_state.hpp"
#include "menu_state.hpp"

#include <platform/time.hpp>
#include <platform/debug.hpp>
#include <game/runtime.hpp>
#include <input/input.hpp>
#include <scene/renderer.hpp>

namespace runner
{
	PlayState::PlayState(papaya::Runtime &runtime, MenuState *menu)
		: runtime_(runtime)
		, keyboard_(runtime.input().keyboard())
		, next_(nullptr)
		, menu_(menu)
	{

	}

	papaya::State *PlayState::next() const
	{
		return nullptr;
	}

	bool PlayState::update(const papaya::Time &deltaTime)
	{
		using namespace papaya;

		static bool once = false;
		if( !once )
		{
			once = true;
			Debug::log("PlayState");
		}

		if( keyboard_.pressed(Key::Escape) )
		{
			next_ = menu_;
			return false;
		}

		return true;
	}

	void PlayState::render(papaya::Renderer &renderer)
	{

	}
} // !runner
