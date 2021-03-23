#pragma once

#include <game/state.hpp>
#include <game/gameobject.hpp>
#include <input/keyboard.hpp>

namespace papaya
{
	class Runtime;
} // !papaya

namespace runner
{
	class MenuState;

	class PlayState : public papaya::State
	{
	public:
		PlayState(papaya::Runtime &runtime, MenuState *menu);
		~PlayState();

		virtual papaya::State *next() const;
		virtual bool update(const papaya::Time &deltaTime);
		virtual void render(papaya::Renderer &renderer);
		virtual bool init();

	private:
		papaya::Runtime &runtime_;
		const papaya::Keyboard &keyboard_;
		papaya::State *next_;
		MenuState *menu_;
		papaya::GameObject *high_score_;
		unsigned int score_;

	};
} // !runner
