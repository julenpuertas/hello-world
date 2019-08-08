#pragma once
#include "String.h"

namespace Engine
{
	namespace Graphics
	{
		class Texture;

		class Material
		{
			float shininess_ = 0.f;
			float parallax_scale_ = 0.f;

			Texture* p_ambient_ = nullptr;
			Texture* p_diffuse_ = nullptr;
			Texture* p_specular_ = nullptr;
			Texture* p_emissive_ = nullptr;
			Texture* p_normal_map_ = nullptr;
			Texture* p_depth_map_ = nullptr;

		public:
			float get_shininess() const;
			void set_shininess(float shininess);
			float get_parallax_scale() const;
			void set_parallax_scale(float parallax_scale);

			Texture& get_ambient() const;
			void set_ambient(const String::View& name);

			Texture& get_diffuse() const;
			void set_diffuse(const String::View& name);

			Texture& get_specular() const;
			void set_specular(const String::View& name);

			Texture& get_emissive() const;
			void set_emissive(const String::View& name);

			Texture& get_normal_map() const;
			void set_normal_map(const String::View& name);

			Texture& get_depth_map() const;
			void set_depth_map(const String::View& name);

			void release_locations() const;
		};
	}
}

