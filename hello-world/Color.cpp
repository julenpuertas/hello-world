//#include "Color.h"
//namespace Engine
//{
//	namespace Graphics
//	{
//		Color::Color(const FVector3& color)
//		{
//			set_red(color.r);
//			set_green(color.g);
//			set_blue(color.b);
//		}
//
//		Color::Color(float gray)
//		{
//			set_red(gray);
//			set_green(gray);
//			set_blue(gray);
//		}
//
//		Color::Color(float red, float green, float blue)
//		{
//			set_red(red);
//			set_green(green);
//			set_blue(blue);
//		}
//
//		float Color::get_red() const
//		{
//			return color_.r;
//		}
//
//		float Color::get_green() const
//		{
//			return color_.g;
//		}
//
//		float Color::get_blue() const
//		{
//			return color_.b;
//		}
//
//		RGB Color::get_rgb() const
//		{
//			RGB rgb;
//
//			for (size_t i = 0; color_.SIZE; ++i)
//				rgb[i] = static_cast<unsigned char>(color_[i] * std::numeric_limits<unsigned char>::max());
//
//			return rgb;
//		}
//
//		void Color::set_red(float red)
//		{
//			color_.r = std::clamp(red, 0.f, 1.f);
//		}
//
//		void Color::set_green(float green)
//		{
//			color_.g = std::clamp(green, 0.f, 1.f);
//		}
//
//		void Color::set_blue(float blue)
//		{
//			color_.b = std::clamp(blue, 0.f, 1.f);
//		}
//
//		Color Color::operator+(const Color& rhs) const
//		{
//			return Color(color_ + rhs.color_);
//		}
//
//		const Color& Color::operator+=(const Color& rhs)
//		{
//			set_red(color_.r + rhs.color_.r);
//			set_green(color_.g + rhs.color_.g);
//			set_blue(color_.b + rhs.color_.b);
//			return *this;
//		}
//
//		Color Color::operator-(const Color& rhs) const
//		{
//			return Color(color_ - rhs.color_);
//		}
//
//		const Color& Color::operator-=(const Color& rhs)
//		{
//			set_red(color_.r - rhs.color_.r);
//			set_green(color_.g - rhs.color_.g);
//			set_blue(color_.b - rhs.color_.b);
//			return *this;
//		}
//
//		Color Color::operator*(const Color& rhs) const
//		{
//			Color result = *this;
//			return result *= rhs;
//		}
//
//		const Color& Color::operator*=(const Color& rhs)
//		{
//			color_ *= rhs.color_;
//			return *this;
//		}
//
//		Color Color::operator*(float rhs) const
//		{
//			return Color(color_ * std::abs(rhs));
//		}
//
//		const Color& Color::operator*=(float rhs)
//		{
//			set_red(color_.r * rhs);
//			set_green(color_.g * rhs);
//			set_blue(color_.b * rhs);
//
//			return *this;
//		}
//
//		Color Color::operator/(const Color & rhs) const
//		{
//			return Color(color_ / rhs.color_);
//		}
//
//		const Color& Color::operator/=(const Color & rhs)
//		{
//			Color result = *this;
//			return result /= rhs;
//		}
//
//		Color Color::operator/(float rhs) const
//		{
//			Color result = *this;
//			return result /= rhs;
//		}
//
//		const Color& Color::operator/=(float rhs)
//		{
//			return *this *= 1.f / rhs;
//		}
//
//		Color operator*(float lhs, const Color & rhs)
//		{
//			return rhs * lhs;
//		}
//	}
//}
