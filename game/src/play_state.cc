#include "play_state.hpp"
#include "menu_state.hpp"

#include <components/jump_component.hpp>
#include <components/sprite_component.hpp>
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
		if( keyboard_.released(Key::Escape) )
		{
			next_ = menu_;
			return false;
		}
		else if( keyboard_.pressed(Key::Space) )
		{
			character_.get_component<JumpComponent>()->jump();
		}

		// Update
		background_.update(delta_time);
		character_.update(delta_time);
		obstacle_pool_.update(delta_time);
		high_score.update(delta_time);
		return true;
	}

	void PlayState::render(papaya::Renderer &renderer)
	{
		background_.render(renderer);
		character_.render(renderer);
		obstacle_pool_.render(renderer);
		high_score.render(renderer);
		renderer.clear(papaya::Color::Black);
		renderer.flush();
	}
	bool PlayState::init()
	{
		const Texture *background_texture = runtime_.textures().find("assets/parallax_1.png");
		background_.add_component<SpriteComponent>();
		background_.get_component<SpriteComponent>()->sprite_.set_size(Vector2{ background_texture->width(), background_texture->height() });
		background_.get_component<SpriteComponent>()->sprite_.set_texcoord(Vector4{ 0.0f, 0.0f, 1.0f, 1.0f });
		background_.get_component<SpriteComponent>()->sprite_.set_texture(background_texture);

		const Texture *character_texture = runtime_.textures().find("assets/octopus_1.png");
		character_.add_component<SpriteComponent>();
		character_.get_component<SpriteComponent>()->sprite_.set_size(Vector2{ character_texture->width(), character_texture->height() });
		character_.get_component<SpriteComponent>()->sprite_.set_texcoord(Vector4{ 0.0f, 0.0f, 1.0f, 1.0f });
		character_.get_component<SpriteComponent>()->sprite_.set_texture(character_texture);
		character_.add_component<TransformComponent>();
		Vector2 center = { Window::width_ / 3 - character_texture->width() / 2, Window::height_ / 2 - character_texture->height() / 2 };
		character_.get_component<TransformComponent>()->transform_.set_position(center);
		character_.add_component<JumpComponent>();

		obstacle_pool_.add_component<SpriteComponent>();
		high_score.add_component<SpriteComponent>();
		return true;
	}
} // !runner
