#include "menu_state.hpp"
#include "play_state.hpp"

#include <components/sprite_component.hpp>
#include <game/runtime.hpp>
#include <graphics/texture.hpp>
#include <graphics/texture_storage.hpp>
#include <input/input.hpp>
#include <platform/time.hpp>
#include <platform/debug.hpp>
#include <platform/window.hpp>
#include <scene/renderer.hpp>
#include <scene/sprite.hpp>

using namespace papaya;

namespace runner
{
	MenuState::MenuState(papaya::Runtime &runtime, PlayState *play)
		: runtime_(runtime)
		, keyboard_(runtime.input().keyboard())
		, next_(nullptr)
		, play_(play)
		, blink_frequency(0)
	{
	}

	MenuState::~MenuState()
	{
		delete_game_objects();
	}

	State *MenuState::next() const
	{
		return next_;
	}

	bool MenuState::update(const papaya::Time &delta_time)
	{
		// On Start
		static bool once = false;
		if( !once )
		{
			once = true;
			Debug::log("MenuState");
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

	void MenuState::render(papaya::Renderer &renderer)
	{
		if( blink_frequency > 30 )
		{
			render_game_objects(renderer);
		}
		renderer.clear(papaya::Color::Black);
		renderer.flush();
	}
	bool MenuState::init()
	{
		papaya::GameObject *welcome_ = new GameObject;
		const Texture *welcome_texture = runtime_.textures().find("assets/welcome_message.png");
		welcome_->add_component<SpriteComponent>();
		welcome_->get_component<SpriteComponent>()->sprite_.set_size(Vector2{ welcome_texture->width(), welcome_texture->height() });
		welcome_->get_component<SpriteComponent>()->sprite_.set_texcoord(Vector4{ 0.0f, 0.0f, 1.0f, 1.0f });
		welcome_->get_component<SpriteComponent>()->sprite_.set_texture(welcome_texture);

		Vector2 center = { Window::width_ / 2 - welcome_texture->width() / 2, Window::height_ / 2 - welcome_texture->height() / 2 };
		welcome_->get_component<TransformComponent>()->transform_.set_position(center);
		push(*welcome_);
		return true;
	}
} // !runner