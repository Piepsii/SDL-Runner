#include "scene/sprite.hpp"
 
namespace papaya
{
	Sprite::Sprite()
		: color_(1.f, 1.f, 1.f, 1.f)
		, texture_(nullptr)
	{
		
	}

	Sprite::Sprite(const Vector2 &size, const Vector4 &texcoords)
		:color_(1.f, 1.f, 1.f, 1.f)
		, size_(size)
		, texcoords_(texcoords)
		, texture_(nullptr)
	{
	}

	Sprite::Sprite(const Vector2 &size, const Vector4 &texcoords, const Texture *texture)
		:color_(1.f, 1.f, 1.f, 1.f)
		, size_(size)
		, texcoords_(texcoords)
		, texture_(texture)
	{
	}

	bool Sprite::is_valid() const
	{
		return size_.x_ > 0.f && size_.y_ > 0.f;
	}

	bool Sprite::has_texture() const
	{
		return texture_ != nullptr;
	}

	void Sprite::set_color(const Color &color)
	{
		color_ = color;
	}

	void Sprite::set_size(const Vector2 &size)
	{
		size_ = size;
	}

	void Sprite::set_texcoords(const Vector4 &texcoords)
	{
		texcoords_ = texcoords;
	}

	void Sprite::set_texture(const Texture *texture)
	{
		texture_ = texture;
	}

	const Color &Sprite::get_color() const
	{
		return color_;
	}

	const Vector2 &Sprite::get_size() const
	{
		return size_;
	}

	const Vector4 &Sprite::get_texcoords() const
	{
		return texcoords_;
	}

	const Texture *Sprite::get_texture() const
	{
		return texture_;
	}
}