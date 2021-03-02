#include "menu_state.hpp"
#include "play_state.hpp"

#include <platform/time.hpp>
#include <platform/debug.hpp>
#include <game/runtime.hpp>
#include <input/input.hpp>
#include <scene/renderer.hpp>

namespace runner
{
	MenuState::MenuState(papaya::Runtime &runtime, PlayState *play)
		: runtime_(runtime)
		, keyboard_(runtime.input().keyboard())
		, next_(nullptr)
		, play_(play)
	{

	}

	papaya::State *MenuState::next() const
	{
		return next_;
	}

	bool MenuState::update(const papaya::Time &deltaTime)
	{
		using namespace papaya;

		static bool once = false;
		if( !once )
		{
			once = true;
			Debug::log("MenuState");
		}

		if( keyboard_.released(Key::Escape) )
		{
			next_ = nullptr;
			return false;
		}
		else if( keyboard_.released(Key::Space) )
		{
			next_ = play_;
			return false;
		}

		return true;
	}

	void MenuState::render(papaya::Renderer &renderer)
	{

	}
} // !runner