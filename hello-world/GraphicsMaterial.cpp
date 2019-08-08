#include "Texture.h"
#include "GraphicsMaterial.h"

namespace
{
	Engine::Graphics::Texture& get_texture(Engine::Graphics::Texture* p_texture)
	{
		return *p_texture;
	}
}

namespace Engine
{
	namespace Graphics
	{
		float Material::get_shininess() const
		{
			return shininess_;
		}

		void Material::set_shininess(float shininess)
		{
			shininess_ = shininess;
		}

		float Material::get_parallax_scale() const
		{
			return parallax_scale_;
		}

		void Material::set_parallax_scale(float parallax_scale)
		{
			parallax_scale_ = parallax_scale;
		}

		Texture& Material::get_ambient() const
		{
			return get_texture(p_ambient_);
		}

		void Material::set_ambient(const String::View& name)
		{
		}

		Texture& Material::get_diffuse() const
		{
			return get_texture(p_diffuse_);
		}

		void Material::set_diffuse(const String::View& name)
		{
		}

		Texture& Material::get_specular() const
		{
			return get_texture(p_specular_);
		}

		void Material::set_specular(const String::View& name)
		{
		}

		Texture& Material::get_emissive() const
		{
			return get_texture(p_emissive_);
		}

		void Material::set_emissive(const String::View& name)
		{
		}

		Texture& Material::get_normal_map() const
		{
			return get_texture(p_normal_map_);
		}

		void Material::set_normal_map(const String::View& name)
		{
		}

		Texture& Material::get_depth_map() const
		{
			return get_texture(p_depth_map_);
		}

		void Material::set_depth_map(const String::View& name)
		{
		}

		void Material::release_locations() const
		{
			const auto release_texture_location = [](Texture* p_texture)
			{
				if (p_texture)
					p_texture->release_location();
			};

			release_texture_location(p_ambient_);
			release_texture_location(p_diffuse_);
			release_texture_location(p_specular_);
			release_texture_location(p_emissive_);
			release_texture_location(p_normal_map_);
		}
	}
}
