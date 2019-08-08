#include "Rotation.h"

namespace Engine
{
	void Rotation::normalize()
	{
		quaternion_ = glm::normalize(quaternion_);
	}

	Rotation::Rotation(const glm::fquat& quaternion)
		: quaternion_(quaternion)
	{
		normalize();
	}

	Rotation::Rotation(float degrees, Math::Axis axis)
		: quaternion_(Rotation(degrees, FVector3(axis)).quaternion_)
	{}

	Rotation::Rotation(float degrees, const FVector3& axis)
		: quaternion_(glm::angleAxis(glm::radians(degrees), axis.get_normalized()))
	{
		normalize();
	}

	Rotation::Rotation(const FVector3& euler_degrees)
		: quaternion_((Rotation(euler_degrees.z, Math::Axis::Z) * Rotation(euler_degrees.y, Math::Axis::Y) * Rotation(euler_degrees.y, Math::Axis::X)).quaternion_)
	{}

	Rotation::Rotation(const FVector3& start, const FVector3& end)
		: quaternion_(glm::rotation(start.get_normalized(), end.get_normalized()))
	{
		normalize();
	}

	Rotation& Rotation::operator*=(const Rotation& rhs)
	{
		quaternion_ = quaternion_ * rhs.quaternion_;
		normalize();
		return *this;
	}

	Rotation Rotation::operator*(const Rotation& rhs) const
	{
		return Rotation(quaternion_ * rhs.quaternion_);
	}

	Rotation Rotation::get_inverse() const
	{
		return Rotation(glm::inverse(quaternion_));
	}

	Rotation& Rotation::operator/=(const Rotation& rhs)
	{
		quaternion_ = quaternion_ * glm::inverse(rhs.quaternion_);
		normalize();
		return *this;
	}

	Rotation Rotation::operator/(const Rotation& rhs) const
	{
		return Rotation(quaternion_ * glm::inverse(rhs.quaternion_));
	}

	FVector3 Rotation::operator*(const FVector3& rhs) const
	{
		return quaternion_ * rhs;
	}

	bool Rotation::operator ==(const Rotation& rhs) const
	{
		return glm::all(glm::epsilonEqual(quaternion_, rhs.quaternion_, Math::get_epsilon<float>()));
	}

	void Rotation::rotate_over(float degrees, Math::Axis axis)
	{
		rotate_over(degrees, FVector3(axis));
	}

	void Rotation::rotate_over(float degrees, const FVector3& axis)
	{
		Rotation& this_ref = *this;
		this_ref = Rotation(degrees, this_ref * axis) * this_ref;
	}

	FVector3 Rotation::get_euler_angles() const
	{
		return glm::degrees(glm::eulerAngles(quaternion_));
	}

	Pair<FVector3, float> Rotation::get_axis_angle() const
	{
		return std::make_pair(FVector3(glm::axis(quaternion_)), glm::degrees(glm::angle(quaternion_)));
	}

	FVector3 Rotation::get_orientation(Math::Axis axis) const
	{
		return *this * FVector3(axis);
	}

	Array<FVector3, FVector3::SIZE> Rotation::get_orientation() const
	{
		Array<FVector3, FVector3::SIZE> result;
		for (size_t i = 0; i < FVector3::SIZE; ++i)
			result[i] = get_orientation(static_cast<Math::Axis>(i));

		return result;
	}

	FMatrix3 Rotation::get_matrix() const
	{
		return glm::mat3_cast(quaternion_);
	}
}
