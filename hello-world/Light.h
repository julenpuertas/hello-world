#pragma once
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
			enum class Type : unsigned int
			{
				POINT = 0,
				DIRECTIONAL = 1,
				SPOT = 2
			};

			constexpr Light(const FVector3& ambient, const FVector3& diffuse, const FVector3& specular);
			constexpr Light(const FVector3& ambient, const FVector3& diffuse, const FVector3& specular, const FVector3& attenuation);
			constexpr Light(const FVector3& ambient, const FVector3& diffuse, const FVector3& specular, const FVector3& attenuation, float inner_cone_degrees, float outer_cone_degrees);
			
			constexpr Type get_type() const;
			constexpr void set_type(Type type);

			constexpr const FVector3& get_ambient() const;
			constexpr void set_ambient(const FVector3& ambient);

			constexpr const FVector3& get_diffuse() const;
			constexpr void set_diffuse(const FVector3& diffuse);

			constexpr const FVector3& get_specular() const;
			constexpr void set_specular(const FVector3& specular);

			constexpr const FVector3& get_attenuation() const;
			constexpr void set_attenuation(const FVector3& attenuation);

			constexpr float get_inner_cone_degrees() const;
			constexpr void set_inner_cone_degrees(float inner_cone_degrees);

			constexpr float get_outer_cone_degrees() const;
			constexpr void set_outer_cone_degrees(float outer_cone_degrees);

		private:
			Type type_;
			FVector3 ambient_;
			FVector3 diffuse_;
			FVector3 specular_;
			FVector3 attenuation_;
			float inner_cone_degrees_;
			float outer_cone_degrees_;
		};
	}
}

