// play_state.cc

#include <components/animation_component.hpp>
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
#include <states/play_state.hpp>
#include <states/menu_state.hpp>

using namespace papaya;

namespace runner
{
	PlayState::PlayState(papaya::Runtime &runtime, MenuState *menu, GameOverState *game_over)
		: runtime_(runtime)
		, keyboard_(runtime.input().keyboard())
		, next_(nullptr)
		, menu_(menu)
		, game_over_(game_over)
		, score_object_(nullptr)
		, highest_score_object_(nullptr)
		, score_(0)
		, highest_score_(0)
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
		score_object_->get_component<TextComponent>()->set_number(score_);
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
			const Texture *character_texture = runtime_.textures().find("assets/octopus.png");
			const int number_of_sprites = 4;
			SpriteComponent *sc = character->add_component<SpriteComponent>();
			sc->sprite_.set_size(Vector2{ character_texture->width() / number_of_sprites, character_texture->height() });
			sc->sprite_.set_texcoord(Vector4{ 0.0f, 0.0f, 0.25f, 1.0f });
			sc->sprite_.set_texture(character_texture);
			position = { Window::width_ / 3 - character_texture->width() / 2, Window::height_ / 2 - character_texture->height() / 2 };
			character->get_component<TransformComponent>()->transform_.set_position(position);
			character->add_component<JumpComponent>();
			CollisionComponent* cc = character->add_component<CollisionComponent>();
			cc->set_collision_shape(Vector2(16.0f, 16.0f));
			AnimationComponent *ac = character->add_component<AnimationComponent>();
			push(*character);
		}
		/*--------------------------------------------------------------------------------------------------------------*/
		{
			const Texture *fish_texture = runtime_.textures().find("assets/fish.png");
			int spawn_amount = 10;
			for( int i = 0; i < spawn_amount + 1; ++i )
			{
				GameObject *fish = new GameObject;
				SpriteComponent *sc = fish->add_component<SpriteComponent>();
				sc->sprite_.set_size(Vector2{ fish_texture->width(), fish_texture->height() });
				sc->sprite_.set_texcoord(Vector4{ 0.0f, 0.0f, 1.0f, 1.0f });
				sc->sprite_.set_texture(fish_texture);
				fish->add_component<ScrollableComponent>();
				fish->get_component<ScrollableComponent>()->chance_of_spawning = 80;
				fish->get_component<ScrollableComponent>()->set_speed_variance(-0.2f);
				int x = std::rand() % Window::width_;
				int y = std::rand() % (Window::height_ / 2) - 32;
				fish->get_component<TransformComponent>()->transform_.set_position({ x, y});
				push(*fish);
			}
		}
		/*--------------------------------------------------------------------------------------------------------------*/
		{
			const Texture *shark_texture = runtime_.textures().find("assets/shark.png");
			int spawn_amount = 3;
			for( int i = 0; i < spawn_amount + 1; ++i )
			{
				GameObject *shark = new GameObject;
				SpriteComponent *sc = shark->add_component<SpriteComponent>();
				sc->sprite_.set_size(Vector2{ shark_texture->width(), shark_texture->height() });
				sc->sprite_.set_texcoord(Vector4{ 0.0f, 0.0f, 1.0f, 1.0f });
				sc->sprite_.set_texture(shark_texture);
				shark->add_component<ScrollableComponent>();
				shark->get_component<ScrollableComponent>()->chance_of_spawning = 50;
				shark->get_component<ScrollableComponent>()->set_speed_variance(-0.4f);
				int x = std::rand() % Window::width_;
				int y = std::rand() % (Window::height_ / 2) - 32;
				shark->get_component<TransformComponent>()->transform_.set_position({ x, y });
				push(*shark);
			}
		}
		/*--------------------------------------------------------------------------------------------------------------*/
		{
			const Texture *ground_texture = runtime_.textures().find("assets/parallax_1.png");
			int spawn_amount = Window::width_ / ground_texture->width() + 1;
			for( int i = 0; i < spawn_amount + 1; ++i )
			{
				GameObject *ground = new GameObject;
				SpriteComponent *sc = ground->add_component<SpriteComponent>();
				sc->sprite_.set_size(Vector2{ ground_texture->width(), ground_texture->height() });
				sc->sprite_.set_texcoord(Vector4{ 0.0f, 0.0f, 1.0f, 1.0f });
				sc->sprite_.set_texture(ground_texture);
				ground->add_component<ScrollableComponent>();
				position = { i * ground_texture->width() , Window::height_ / 2 };
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
				scc->set_is_changing_texture(true);
				position = { i * obstacle_1_texture->width() * 4 , Window::height_ / 2 - obstacle_1_texture->height() / 2 };
				obstacle->get_component<TransformComponent>()->transform_.set_position(position);
				CollisionComponent *cc = obstacle->add_component<CollisionComponent>();
				cc->set_collision_shape(Vector2(32.0f, 32.0f));
				push(*obstacle);
			}
		}
		/*--------------------------------------------------------------------------------------------------------------*/
		{
			score_object_ = new GameObject;
			TextComponent *tc = score_object_->add_component<TextComponent>();
			tc->set_texture_set(runtime_.textures().find("assets/digits.png"));
			tc->set_number(000000);
			position = { 100 , 10 };
			score_object_->get_component<TransformComponent>()->transform_.set_position(position);
			push(*score_object_);
		}
		/*--------------------------------------------------------------------------------------------------------------*/
		{
			highest_score_object_ = new GameObject;
			TextComponent *tc = highest_score_object_->add_component<TextComponent>();
			tc->set_texture_set(runtime_.textures().find("assets/digits.png"));
			tc->set_number(000000);
			position = { Window::width_ / 2 + 100 , 10 };
			highest_score_object_->get_component<TransformComponent>()->transform_.set_position(position);
			push(*highest_score_object_);
		}
		/*--------------------------------------------------------------------------------------------------------------*/
		{
			papaya::GameObject *score_message = new GameObject;
			const Texture *score_message_texture = runtime_.textures().find("assets/score_message.png");
			SpriteComponent *sc = score_message->add_component<SpriteComponent>();
			sc->sprite_.set_size(Vector2{ score_message_texture->width(), score_message_texture->height() });
			sc->sprite_.set_texcoord(Vector4{ 0.0f, 0.0f, 1.0f, 1.0f });
			sc->sprite_.set_texture(score_message_texture);

			position = { 5, 10 };
			score_message->get_component<TransformComponent>()->transform_.set_position(position);
			push(*score_message);
		}
		/*--------------------------------------------------------------------------------------------------------------*/
		{
			papaya::GameObject *high_score_message = new GameObject;
			const Texture *high_score_message_texture = runtime_.textures().find("assets/high_score_message.png");
			SpriteComponent *sc = high_score_message->add_component<SpriteComponent>();
			sc->sprite_.set_size(Vector2{ high_score_message_texture->width(), high_score_message_texture->height() });
			sc->sprite_.set_texcoord(Vector4{ 0.0f, 0.0f, 1.0f, 1.0f });
			sc->sprite_.set_texture(high_score_message_texture);

			position = { Window::width_ / 2 - 5, 10 };
			high_score_message->get_component<TransformComponent>()->transform_.set_position(position);
			push(*high_score_message);
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
		int i = 0;
		while( currentptr != nullptr )
		{
			if( currentptr->has_component<ScrollableComponent>() && currentptr->has_component<CollisionComponent>() )
			{
				currentptr->get_component<ScrollableComponent>()->set_transparent();
				currentptr->get_component<TransformComponent>()->transform_.set_position({ i * 32 * 4 , Window::height_ / 2 - 32 / 2 });
				++i;
			}
			currentptr = currentptr->next_;
		}
		score_ > highest_score_ ? highest_score_ = score_ : highest_score_ = highest_score_;
		highest_score_object_->get_component<TextComponent>()->set_number(highest_score_);
		score_ = 0;
		ScrollableComponent::scroll_speed_ = 1.0f;
	}
} // !runner
