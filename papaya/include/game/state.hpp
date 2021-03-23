// state.hpp

#pragma once

#include "game/gameobject.hpp"

namespace papaya
{
	class Time;
	class Renderer;
	class Input;

	class State
	{
	public:
		virtual ~State() = default;

		virtual State *next() const = 0;
		virtual bool update(const Time &delta_time) = 0;
		virtual void render(Renderer &renderer) = 0;
		virtual bool init() = 0;

		int count_ = 0;
		GameObject *game_objects_ = nullptr;

		void push(GameObject &game_object);
		void delete_game_objects();
		void update_game_objects(const Time &delta_time);
		void render_game_objects(Renderer &renderer);
		void handle_input_game_objects(Input &input);

		//virtual void shut() = 0;
		//virtual void enter() = 0;
		//virtual void exit() = 0;
	};
} // !papaya
