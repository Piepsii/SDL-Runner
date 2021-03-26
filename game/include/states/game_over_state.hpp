// game_over_state.hpp

#pragma once

#include <components/sprite_component.hpp>
#include <game/runtime.hpp>
#include <game/state.hpp>
#include <graphics/texture.hpp>
#include <graphics/texture_storage.hpp>
#include <input/input.hpp>
#include <input/keyboard.hpp>
#include <platform/window.hpp>
#include <platform/debug.hpp>
#include <states/play_state.hpp>

namespace papaya
{
	class Runtime;
} // !papaya

namespace runner
{
	class PlayState;

	class GameOverState : public papaya::State
	{
	public:
		GameOverState(papaya::Runtime &runtime, PlayState *play);
		~GameOverState();

		virtual papaya::State *next() const;
		virtual bool update(const papaya::Time &delta_time);
		virtual void render(papaya::Renderer &renderer);
		virtual bool init();
		virtual void exit();

	private:
		papaya::Runtime &runtime_;
		const papaya::Keyboard &keyboard_;
		papaya::State *next_;
		PlayState *play_;
		int blink_frequency;

	};
} // !runner
