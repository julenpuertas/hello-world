#include "Light.h"
#if 0
namespace Engine
{
	namespace Graphics
	{
		Light::Light(const Color& ambient, const Color& diffuse, const Color& specular)
			: type_(Type::DIRECTIONAL)
			, ambient_(ambient)
			, diffuse_(diffuse)
			, specular_(specular)
		{}

		Light::Light(const Color& ambient, const Color& diffuse, const Color& specular, const Color& attenuation)
			: type_(Type::POINT)
			, ambient_(ambient)
			, diffuse_(diffuse)
			, specular_(specular)
			, attenuation_(attenuation)
		{}

		Light::Light(const Color& ambient, const Color& diffuse, const Color& specular, const Color& attenuation, float inner_cone_degrees, float outer_cone_degrees)
			: type_(Type::SPOT)
			, ambient_(ambient)
			, diffuse_(diffuse)
			, specular_(specular)
			, attenuation_(attenuation)
			, inner_cone_degrees_(inner_cone_degrees)
			, outer_cone_degrees_(outer_cone_degrees)
		{}

		Component* Light::clone() const
		{
			return new Light(*this);
		}

		Component::TypeInfo Light::get_type_info() const
		{
			return typeid(*this);
		}

		constexpr Light::Type Light::get_type() const
		{
			return type_;
		}

		constexpr void Light::set_type(Type type)
		{
			type_ = type;
		}

		constexpr const Color& Light::get_ambient() const
		{
			return ambient_;
		}

		constexpr void Light::set_ambient(const Color& ambient)
		{
			ambient_ = ambient;
		}

		constexpr const Color& Light::get_diffuse() const
		{
			return diffuse_;
		}

		constexpr void Light::set_diffuse(const Color& diffuse)
		{
			diffuse_ = diffuse;
		}

		constexpr const Color& Light::get_specular() const
		{
			return specular_;
		}

		constexpr void Light::set_specular(const Color& specular)
		{
			specular_ = specular;
		}

		constexpr const Color& Light::get_attenuation() const
		{
			return attenuation_;
		}

		constexpr void Light::set_attenuation(const Color& attenuation)
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
#endif