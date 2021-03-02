#include "play_state.hpp"
#include "menu_state.hpp"

#include <platform/time.hpp>
#include <platform/debug.hpp>
#include <input/input.hpp>
#include <scene/renderer.hpp>
#include <game/runtime.hpp>

namespace runner
{
	PlayState::PlayState(papaya::Runtime &runtime, MenuState *menu)
		: runtime_(runtime)
		, keyboard_(runtime.input().keyboard())
		, next_(nullptr)
		, menu_(menu)
	{

	}

	bool PlayState::init()
	{
		return false;
	}

	void PlayState::shut()
	{
	}

	papaya::State *PlayState::next() const
	{
		return nullptr;
	}

	bool PlayState::update(const papaya::Time &deltaTime)
	{
		using namespace papaya;

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
