// state.hpp

#pragma once

namespace papaya
{
	class Time;
	class Renderer;

	class State
	{
	public:
		virtual ~State() = default;

		virtual State *next() const = 0;
		virtual bool update(const Time &deltaTime) = 0;
		virtual void render(Renderer &renderer) = 0;
		virtual bool init() = 0;

		//virtual void shut() = 0;
		//virtual void enter() = 0;
		//virtual void exit() = 0;
	};
} // !papaya
