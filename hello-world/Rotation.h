#pragma once
#include <glm\gtc\quaternion.hpp>
#include "Array.h"
#include "Pair.h"
#include "Vector.h"
#include "Matrix.h"

namespace Engine
{
	class Rotation
	{
		glm::fquat quaternion_;
		explicit Rotation(const glm::fquat& quaternion);
		void normalize();

	public:
		Rotation() = default;
		explicit Rotation(float degrees, Math::Axis axis);
		explicit Rotation(float degrees, const FVector3& axis);
		explicit Rotation(const FVector3& euler_degrees);
		explicit Rotation(const FVector3& start, const FVector3& end);

		Rotation& operator*=(const Rotation& rhs);
		Rotation operator*(const Rotation& rhs) const;
		Rotation& operator/=(const Rotation& rhs);
		Rotation operator/(const Rotation& rhs) const;
		Rotation get_inverse() const;
		FVector3 operator*(const FVector3& rhs) const;
		bool operator ==(const Rotation& rhs) const;

		void rotate_over(float degrees, Math::Axis axis);
		void rotate_over(float degrees, const FVector3& axis);
		FVector3 get_euler_angles() const;
		Pair<FVector3, float> get_axis_angle() const;
		FVector3 get_orientation(Math::Axis axis) const;
		Array<FVector3, 3> get_orientation() const;
		FMatrix3 get_matrix() const;
	};
}
