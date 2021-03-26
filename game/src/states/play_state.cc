// play_state.cc

#include <states/play_state.hpp>
#include <states/menu_state.hpp>
#include <components/collision_component.hpp>
#include <components/jump_component.hpp>
#include <components/sprite_component.hpp>
#include <components/scrollable_component.hpp>
#include <components/text_component.hpp>
#include <game/runtime.hpp>
#include <graphics/texture.hpp>
#include <graphics/texture_storage.hpp>
#include <input/input.hpp>
#include <platform/time.hpp>
#include <platform/debug.hpp>
#include <platform/window.hpp>
#include <scene/renderer.hpp>

using namespace papaya;

namespace runner
{
	PlayState::PlayState(papaya::Runtime &runtime, MenuState *menu, GameOverState *game_over)
		: runtime_(runtime)
		, keyboard_(runtime.input().keyboard())
		, next_(nullptr)
		, menu_(menu)
		, game_over_(game_over)
		, high_score_(nullptr)
		, score_(0)
	{
	}

	PlayState::~PlayState()
	{
		delete_game_objects();
	}

	papaya::State *PlayState::next() const
	{
		return next_;
	}

	bool PlayState::update(const papaya::Time &delta_time)
	{
		// On Start
		static bool once = false;
		if( !once )
		{
			once = true;
			Debug::log("PlayState");
			reset();
		}

		// Input
		if( game_objects_ != nullptr )
		{
			handle_input_game_objects(runtime_.input());
		}
		if( keyboard_.released(Key::Escape) )
		{
			next_ = menu_;
			exit();
			return false;
		}

		// Update
		update_game_objects(delta_time);
		ScrollableComponent::scroll_speed_ += 0.001f;
		score_++;
		high_score_->get_component<TextComponent>()->set_number(score_);
		GameObject *currentptr = game_objects_;
		while( currentptr != nullptr )
		{
			if( currentptr->has_component<CollisionComponent>())
			{
				if( currentptr->get_component<CollisionComponent>()->is_colliding() )
				{
					next_ = game_over_;
					exit();
					return false;
				}
			}
			currentptr = currentptr->next_;
		}
		return true;
	}

	void PlayState::render(papaya::Renderer &renderer)
	{
		render_game_objects(renderer);
		renderer.clear(papaya::Color::Black);
		renderer.flush();
	}
	bool PlayState::init()
	{
		Vector2 position;
		/*--------------------------------------------------------------------------------------------------------------*/
		{
			GameObject *character = new GameObject;
			const Texture *character_texture = runtime_.textures().find("assets/octopus_1.png");
			SpriteComponent *sc = character->add_component<SpriteComponent>();
			sc->sprite_.set_size(Vector2{ character_texture->width(), character_texture->height() });
			sc->sprite_.set_texcoord(Vector4{ 0.0f, 0.0f, 1.0f, 1.0f });
			sc->sprite_.set_texture(character_texture);
			position = { Window::width_ / 3 - character_texture->width() / 2, Window::height_ / 2 - character_texture->height() / 2 };
			character->get_component<TransformComponent>()->transform_.set_position(position);
			character->add_component<JumpComponent>();
			CollisionComponent* cc = character->add_component<CollisionComponent>();
			cc->set_collision_shape(Vector2(16.0f, 16.0f));
			push(*character);
		}
		/*--------------------------------------------------------------------------------------------------------------*/
		{
			const Texture *ground_texture = runtime_.textures().find("assets/parallax_1.png");
			int spawn_amount = Window::width_ / ground_texture->width();
			for( int i = 0; i < spawn_amount + 1; i++ )
			{
				GameObject *ground = new GameObject;
				SpriteComponent *sc = ground->add_component<SpriteComponent>();
				sc->sprite_.set_size(Vector2{ ground_texture->width(), ground_texture->height() });
				sc->sprite_.set_texcoord(Vector4{ 0.0f, 0.0f, 1.0f, 1.0f });
				sc->sprite_.set_texture(ground_texture);
				ground->add_component<ScrollableComponent>();
				position = { i * (ground_texture->width() - 2) , Window::height_ / 2 - ground_texture->height() / 2 + ground_texture->height() / 2 };
				ground->get_component<TransformComponent>()->transform_.set_position(position);
				push(*ground);
			}
		}
		/*--------------------------------------------------------------------------------------------------------------*/
		{
			const Texture *obstacle_1_texture = runtime_.textures().find("assets/coral_1.png");
			const Texture *obstacle_2_texture = runtime_.textures().find("assets/coral_2.png");
			int spawn_amount_obstacles = Window::width_ / obstacle_1_texture->width() / 4;
			for( int i = 0; i < spawn_amount_obstacles + 1; i++ )
			{
				GameObject *obstacle = new GameObject;
				SpriteComponent *sc = obstacle->add_component<SpriteComponent>();
				sc->sprite_.set_size(Vector2{ obstacle_1_texture->width(), obstacle_1_texture->height() });
				sc->sprite_.set_texcoord(Vector4{ 0.0f, 0.0f, 1.0f, 1.0f });
				sc->sprite_.set_texture(obstacle_1_texture);
				ScrollableComponent *scc = obstacle->add_component<ScrollableComponent>();
				scc->add_texture(obstacle_2_texture);
				scc->chance_of_spawning = 33;
				position = { i * obstacle_1_texture->width() * 4 , Window::height_ / 2 - obstacle_1_texture->height() / 2 };
				obstacle->get_component<TransformComponent>()->transform_.set_position(position);
				CollisionComponent *cc = obstacle->add_component<CollisionComponent>();
				cc->set_collision_shape(Vector2(32.0f, 32.0f));
				push(*obstacle);
			}
		}
		/*--------------------------------------------------------------------------------------------------------------*/
		{
			high_score_ = new GameObject;
			TextComponent *tc = high_score_->add_component<TextComponent>();
			tc->set_texture(runtime_.textures().find("assets/0.png"), 0);
			tc->set_texture(runtime_.textures().find("assets/1.png"), 1);
			tc->set_texture(runtime_.textures().find("assets/2.png"), 2);
			tc->set_texture(runtime_.textures().find("assets/3.png"), 3);
			tc->set_texture(runtime_.textures().find("assets/4.png"), 4);
			tc->set_texture(runtime_.textures().find("assets/5.png"), 5);
			tc->set_texture(runtime_.textures().find("assets/6.png"), 6);
			tc->set_texture(runtime_.textures().find("assets/7.png"), 7);
			tc->set_texture(runtime_.textures().find("assets/8.png"), 8);
			tc->set_texture(runtime_.textures().find("assets/9.png"), 9);
			tc->set_number(000000);
			position = { Window::width_ / 2 , 10 };
			high_score_->get_component<TransformComponent>()->transform_.set_position(position);
			push(*high_score_);
		}
		/*--------------------------------------------------------------------------------------------------------------*/

		return true;
	}

	void PlayState::exit()
	{
		reset();
	}

	void PlayState::reset()
	{
		GameObject *currentptr = game_objects_;
		while( currentptr != nullptr )
		{
			int i = 0;
			if( currentptr->has_component<ScrollableComponent>() && currentptr->has_component<CollisionComponent>() )
			{
				currentptr->get_component<ScrollableComponent>()->set_transparent();
				currentptr->get_component<TransformComponent>()->transform_.set_position({ i * 32 * 4 , Window::height_ / 2 - 32 / 2 });
				i++;
			}
			currentptr = currentptr->next_;
		}
		score_ = 0;
		ScrollableComponent::scroll_speed_ = 1.0f;
	}
} // !runner
