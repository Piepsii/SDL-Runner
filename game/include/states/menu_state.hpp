// menu_state.hpp

#pragma once

#include <components/sprite_component.hpp>
#include <game/gameobject.hpp>
#include <game/state.hpp>
#include <game/runtime.hpp>
#include <graphics/texture.hpp>
#include <graphics/texture_storage.hpp>
#include <input/input.hpp>
#include <input/keyboard.hpp>
#include <platform/time.hpp>
#include <platform/debug.hpp>
#include <platform/window.hpp>
#include <scene/renderer.hpp>
#include <scene/sprite.hpp>
#include <states/play_state.hpp>

namespace papaya
{
	class Runtime;
} // !papaya

namespace runner
{
	class PlayState;

	class MenuState : public papaya::State
	{
	public:
		MenuState(papaya::Runtime &runtime, PlayState *play);
		~MenuState();

		virtual papaya::State *next() const;
		virtual bool update(const papaya::Time &deltaTime);
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