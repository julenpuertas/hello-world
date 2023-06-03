#pragma once
//#include "Color.h"
#include "Vector.h"
#include "Component.h"

namespace Engine
{
	namespace Graphics
	{
		class Light
			: public Component
		{
		public:
#if 0
			enum class Type : unsigned
			{
				POINT = 0,
				DIRECTIONAL = 1,
				SPOT = 2
			};

			Light(const Color& ambient, const Color& diffuse, const Color& specular);
			Light(const Color& ambient, const Color& diffuse, const Color& specular, const Color& attenuation);
			Light(const Color& ambient, const Color& diffuse, const Color& specular, const Color& attenuation, float inner_cone_degrees, float outer_cone_degrees);
			
			Component* clone() const override;
			TypeInfo get_type_info() const override;

			constexpr Type get_type() const;
			constexpr void set_type(Type type);

			constexpr const Color& get_ambient() const;
			constexpr void set_ambient(const Color& ambient);

			constexpr const Color& get_diffuse() const;
			constexpr void set_diffuse(const Color& diffuse);

			constexpr const Color& get_specular() const;
			constexpr void set_specular(const Color& specular);

			constexpr const Color& get_attenuation() const;
			constexpr void set_attenuation(const Color& attenuation);

			constexpr float get_inner_cone_degrees() const;
			constexpr void set_inner_cone_degrees(float inner_cone_degrees);

			constexpr float get_outer_cone_degrees() const;
			constexpr void set_outer_cone_degrees(float outer_cone_degrees);
#endif
		private:
#if 0
			Type type_;
			Color ambient_;
			Color diffuse_;
			Color specular_;
			Color attenuation_;
#endif
			//FVector3 foo;
			float inner_cone_degrees_ = 0.f;
			float outer_cone_degrees_ = 0.f;
		};
	}
}
