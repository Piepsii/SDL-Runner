#include "play_state.hpp"
#include "menu_state.hpp"

#include <components/jump_component.hpp>
#include <components/sprite_component.hpp>
#include <components/scrollable_component.hpp>
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
	PlayState::PlayState(papaya::Runtime &runtime, MenuState *menu)
		: runtime_(runtime)
		, keyboard_(runtime.input().keyboard())
		, next_(nullptr)
		, menu_(menu)
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
		}

		// Input
		if( game_objects != nullptr )
		{
			handle_input_game_objects(runtime_.input());
		}
		if( keyboard_.released(Key::Escape) )
		{
			next_ = menu_;
			return false;
		}

		// Update
		update_game_objects(delta_time);
		ScrollableComponent::scroll_speed_ += 0.001f;
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
		GameObject *character = new GameObject;
		//GameObject* high_score = new GameObject;
		const Texture *character_texture = runtime_.textures().find("assets/octopus_1.png");
		character->add_component<SpriteComponent>();
		character->get_component<SpriteComponent>()->sprite_.set_size(Vector2{ character_texture->width(), character_texture->height() });
		character->get_component<SpriteComponent>()->sprite_.set_texcoord(Vector4{ 0.0f, 0.0f, 1.0f, 1.0f });
		character->get_component<SpriteComponent>()->sprite_.set_texture(character_texture);
		character->add_component<TransformComponent>();
		Vector2 center = { Window::width_ / 3 - character_texture->width() / 2, Window::height_ / 2 - character_texture->height() / 2 };
		character->get_component<TransformComponent>()->transform_.set_position(center);
		character->add_component<JumpComponent>();
		push(*character);
		
		const Texture *ground_texture = runtime_.textures().find("assets/parallax_1.png");
		int spawn_amount = Window::width_ / ground_texture->width();
		for( int i = 0; i < spawn_amount + 1; i++ )
		{
			GameObject *ground = new GameObject;
			ground->add_component<SpriteComponent>();
			ground->get_component<SpriteComponent>()->sprite_.set_size(Vector2{ ground_texture->width(), ground_texture->height() });
			ground->get_component<SpriteComponent>()->sprite_.set_texcoord(Vector4{ 0.0f, 0.0f, 1.0f, 1.0f });
			ground->get_component<SpriteComponent>()->sprite_.set_texture(ground_texture);
			ground->add_component<TransformComponent>();
			ground->add_component<ScrollableComponent>();
			center = { i * ( ground_texture->width() - 2 ) , Window::height_ / 2 - ground_texture->height() / 2 + ground_texture->height() / 2 };
			ground->get_component<TransformComponent>()->transform_.set_position(center);
			push(*ground);
		}

		const Texture *obstacle_1_texture = runtime_.textures().find("assets/coral_1.png");
		const Texture *obstacle_2_texture = runtime_.textures().find("assets/coral_2.png");
		int spawn_amount_obstacles = Window::width_ / obstacle_1_texture->width() / 4;
		for( int i = 0; i < spawn_amount_obstacles + 1; i++ )
		{
			GameObject *obstacle_1 = new GameObject;
			obstacle_1->add_component<SpriteComponent>();
			obstacle_1->get_component<SpriteComponent>()->sprite_.set_size(Vector2{ obstacle_1_texture->width(), obstacle_1_texture->height() });
			obstacle_1->get_component<SpriteComponent>()->sprite_.set_texcoord(Vector4{ 0.0f, 0.0f, 1.0f, 1.0f });
			obstacle_1->get_component<SpriteComponent>()->sprite_.set_texture(obstacle_1_texture);
			obstacle_1->add_component<TransformComponent>();
			obstacle_1->add_component<ScrollableComponent>();
			obstacle_1->get_component<ScrollableComponent>()->add_texture(obstacle_2_texture);
			obstacle_1->get_component<ScrollableComponent>()->chance_of_spawning = 33;
			center = { i * obstacle_1_texture->width() * 4 , Window::height_ / 2 - obstacle_1_texture->height() / 2 };
			obstacle_1->get_component<TransformComponent>()->transform_.set_position(center);
			push(*obstacle_1);
		}
		return true;
	}
} // !runner
