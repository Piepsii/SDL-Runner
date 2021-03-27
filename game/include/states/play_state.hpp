// play_state.hpp

#pragma once

#include <game/state.hpp>
#include <game/gameobject.hpp>
#include <input/keyboard.hpp>
#include <states/game_over_state.hpp>

namespace papaya
{
	class Runtime;
} // !papaya

namespace runner
{
	class MenuState;
	class GameOverState;

	class PlayState : public papaya::State
	{
	public:
		PlayState(papaya::Runtime &runtime, MenuState *menu, GameOverState *game_over);
		~PlayState();

		virtual papaya::State *next() const;
		virtual bool update(const papaya::Time &delta_time);
		virtual void render(papaya::Renderer &renderer);
		virtual bool init();
		virtual void exit();

	private:
		void reset();

	private:
		papaya::Runtime &runtime_;
		const papaya::Keyboard &keyboard_;
		papaya::State *next_;
		MenuState *menu_;
		GameOverState *game_over_;
		papaya::GameObject *score_object_, *highest_score_object_;
		unsigned int score_, highest_score_;

	};
} // !runner
