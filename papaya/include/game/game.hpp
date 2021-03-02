#pragma once

namespace papaya
{
	class Time;
	class Runtime;

	class Game
	{
	public:
		Game(Runtime &runtime);
		virtual ~Game() = default;

		virtual bool init();
		virtual void shut();
		virtual bool tick(const Time &deltaTime);

	protected:
		Runtime &runtime_;

	};
}