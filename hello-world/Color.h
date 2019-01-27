//#pragma once
//#include "RGB.h"
//
//namespace Engine
//{
//	namespace Graphics
//	{
//		using RGB = Math::Vector<unsigned char, 3>;
//
//		class Color
//		{
//			FVector3 color_;
//
//			Color(const FVector3& color);
//
//		public:
//			Color() = default;
//			explicit Color(float gray);
//			Color(float red, float green, float blue);
//
//			float get_red() const;
//			float get_green() const;
//			float get_blue() const;
//			RGB get_rgb() const;
//
//			void set_red(float red);
//			void set_green(float green);
//			void set_blue(float blue);
//
//			Color operator+(const Color& rhs) const;
//			const Color& operator+=(const Color& rhs);
//
//			Color operator-(const Color& rhs) const;
//			const Color& operator-=(const Color& rhs);
//
//			Color operator*(const Color& rhs) const;
//			const Color& operator*=(const Color& rhs);
//
//			Color operator*(float rhs) const;
//			const Color& operator*=(float rhs);
//
//			Color operator/(const Color& rhs) const;
//			const Color& operator/=(const Color& rhs);
//
//			Color operator/(float rhs) const;
//			const Color& operator/=(float rhs);
//		};
//
//		Color operator*(float lhs, const Color& rhs);
//	}
//}
