#include "Light.h"

namespace Engine
{
	namespace Graphics
	{
		constexpr Light::Light(const FVector3& ambient, const FVector3& diffuse, const FVector3& specular)
			: type_(Type::DIRECTIONAL)
			, ambient_(ambient)
			, diffuse_(diffuse)
			, specular_(specular)
		{}

		constexpr Light::Light(const FVector3& ambient, const FVector3& diffuse, const FVector3& specular, const FVector3& attenuation)
			: type_(Type::POINT)
			, ambient_(ambient)
			, diffuse_(diffuse)
			, specular_(specular)
			, attenuation_(attenuation)
		{}

		constexpr Light::Light(const FVector3& ambient, const FVector3& diffuse, const FVector3& specular, const FVector3& attenuation, float inner_cone_degrees, float outer_cone_degrees)
			: type_(Type::SPOT)
			, ambient_(ambient)
			, diffuse_(diffuse)
			, specular_(specular)
			, attenuation_(attenuation)
			, inner_cone_degrees_(inner_cone_degrees)
			, outer_cone_degrees_(outer_cone_degrees)
		{}

		constexpr Light::Type Light::get_type() const
		{
			return type_;
		}

		constexpr void Light::set_type(Type type)
		{
			type_ = type;
		}

		constexpr const FVector3& Light::get_ambient() const
		{
			return ambient_;
		}

		constexpr void Light::set_ambient(const FVector3& ambient)
		{
			ambient_ = ambient;
		}

		constexpr const FVector3& Light::get_diffuse() const
		{
			return diffuse_;
		}

		constexpr void Light::set_diffuse(const FVector3& diffuse)
		{
			diffuse_ = diffuse;
		}

		constexpr const FVector3& Light::get_specular() const
		{
			return specular_;
		}

		constexpr void Light::set_specular(const FVector3& specular)
		{
			specular_ = specular;
		}

		constexpr const FVector3& Light::get_attenuation() const
		{
			return attenuation_;
		}

		constexpr void Light::set_attenuation(const FVector3& attenuation)
		{
			attenuation_ = attenuation;
		}

		constexpr float Light::get_inner_cone_degrees() const
		{
			return inner_cone_degrees_;
		}

		constexpr void Light::set_inner_cone_degrees(float inner_cone_degrees)
		{
			inner_cone_degrees_ = inner_cone_degrees;
		}

		constexpr float Light::get_outer_cone_degrees() const
		{
			return outer_cone_degrees_;
		}

		constexpr void Light::set_outer_cone_degrees(float outer_cone_degrees)
		{
			outer_cone_degrees_ = outer_cone_degrees;
		}
	}
}
