// state.cc

#include "game\state.hpp"

namespace papaya
{
	void State::push(GameObject &game_object)
	{
		if( count_ == 0 )
		{
			game_objects_ = &game_object;
		}
		else
		{
			game_object.next_ = game_objects_;
			game_objects_ = &game_object;
		}
		count_++;
	}

	void State::delete_game_objects()
	{
		if( game_objects_ == nullptr )
		{
			return;
		}
		else
		{
			GameObject *currentptr = game_objects_;
			GameObject *tempptr = nullptr;

			for(int it = 0; it < count_; it++)
			{
				tempptr = currentptr;
				currentptr = currentptr->next_;
				delete tempptr;
			}
			currentptr = nullptr;
			tempptr = nullptr;
			game_objects_ = nullptr;
		}
	}

	void State::update_game_objects(const Time &delta_time)
	{
		GameObject *currentptr = game_objects_;
		for( int it = 0; it < count_; it++ )
		{
			currentptr->update(delta_time);
			currentptr = currentptr->next_;
		}
	}

	void State::render_game_objects(Renderer &renderer)
	{
		GameObject *currentptr = game_objects_;
		for( int it = 0; it < count_; it++ )
		{
			currentptr->render(renderer);
			currentptr = currentptr->next_;
		}
	}

	void State::handle_input_game_objects(Input &input)
	{
		GameObject *currentptr = game_objects_;
		for( int it = 0; it < count_; it++ )
		{
			currentptr->handle_input(input);
			currentptr = currentptr->next_;
		}
	}
} // !papaya