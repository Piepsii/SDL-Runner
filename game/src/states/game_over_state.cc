// game_over_state.cc

#include "states\game_over_state.hpp"

using namespace papaya;

namespace runner
{
	GameOverState::GameOverState(papaya::Runtime &runtime, PlayState *play)
		: runtime_(runtime)
		, keyboard_(runtime.input().keyboard())
		, next_(nullptr)
		, play_(play)
		, blink_frequency(0)
	{
	}

	GameOverState::~GameOverState()
	{
		delete_game_objects();
	}

	papaya::State *GameOverState::next() const
	{
		return next_;
	}

	bool GameOverState::update(const papaya::Time &delta_time)
	{
		// On Start
		static bool once = false;
		if( !once )
		{
			once = true;
			Debug::log("GameOverState");
		}

		// Input
		if( game_objects_ != nullptr )
		{
			handle_input_game_objects(runtime_.input());
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


		// Update
		if( game_objects_ != nullptr )
		{
			update_game_objects(delta_time);
		}

		blink_frequency++;
		if( blink_frequency == 60 )
		{
			blink_frequency = 0;
		}
		return true;
	}

	void GameOverState::render(papaya::Renderer &renderer)
	{
		if( blink_frequency > 30 )
		{
			render_game_objects(renderer);
		}
		renderer.clear(papaya::Color::Black);
		renderer.flush();
	}

	bool GameOverState::init()
	{
		/*--------------------------------------------------------------------------------------------------------------*/
		GameObject *game_over_message = new GameObject;
		const Texture *game_over_texture = runtime_.textures().find("assets/game_over_message.png");
		SpriteComponent *sc = game_over_message->add_component<SpriteComponent>();
		sc->sprite_.set_size(Vector2{ game_over_texture->width(), game_over_texture->height() });
		sc->sprite_.set_texcoord(Vector4{ 0.0f, 0.0f, 1.0f, 1.0f });
		sc->sprite_.set_texture(game_over_texture);

		Vector2 center = { Window::width_ / 2 - game_over_texture->width() / 2, Window::height_ / 2 - game_over_texture->height() / 2 };
		game_over_message->get_component<TransformComponent>()->transform_.set_position(center);
		push(*game_over_message);
		/*--------------------------------------------------------------------------------------------------------------*/

		return true;
	}

	void GameOverState::exit()
	{
		
	}
} // !runner
