#include "Transform.h"

namespace Engine
{
	Transform::Concatenator::Policy::Policy(bool value)
		: translation_affected_(value)
		, scale_affected_(value)
		, rotation_affected_(value)
	{}

	Transform::Concatenator::Policy::Policy(bool translation_affected, bool scale_affected, bool rotation_affected)
		: translation_affected_(translation_affected)
		, scale_affected_(scale_affected)
		, rotation_affected_(rotation_affected)
	{}

	bool Transform::Concatenator::Policy::is_translation_affected() const
	{
		return translation_affected_;
	}

	bool Transform::Concatenator::Policy::is_scale_affected() const
	{
		return scale_affected_;
	}

	bool Transform::Concatenator::Policy::is_rotation_affected() const
	{
		return rotation_affected_;
	}

	void Transform::Concatenator::Policy::set_translation_affected(bool translation_affected)
	{
		translation_affected_ = translation_affected;
	}

	void Transform::Concatenator::Policy::set_scale_affected(bool scale_affected)
	{
		scale_affected_ = scale_affected;
	}

	void Transform::Concatenator::Policy::set_rotation_affected(bool rotation_affected)
	{
		rotation_affected_ = rotation_affected;
	}

	Transform::Concatenator::Concatenator(const FMatrix3x4& translation_transformer, const FVector3& scale_transformer, const Rotation& rotation_transformer)
		: translation_transformer_(translation_transformer)
		, scale_transformer_(scale_transformer)
		, rotation_transformer_(rotation_transformer)
	{}

	Transform Transform::Concatenator::concatenate(const Transform& transform, const Policy& policy) const
	{
		Transform result = transform;

		if (policy.is_translation_affected())
			result.translation_ = translation_transformer_ * result.translation_;

		if (policy.is_scale_affected())
			result.scale_ = scale_transformer_ * result.scale_;

		if (policy.is_rotation_affected())
			result.rotation_ = rotation_transformer_ * result.rotation_;

		return result;
	}

	FMatrix3 Transform::get_vector_transformation_inverse_matrix() const
	{
		const FVector3 inverse_scale = 1.f / scale_;
		FMatrix3 vector_transformation_inverse_matrix = rotation_.get_inverse().get_matrix();

		for (size_t i = 0; i < FMatrix3::WIDTH; ++i)
			vector_transformation_inverse_matrix[i] *= inverse_scale;

		return vector_transformation_inverse_matrix;
	}

	const FVector3& Transform::get_translation() const
	{
		return translation_;
	}

	const FVector3& Transform::get_scale() const
	{
		return scale_;
	}

	const Rotation& Transform::get_rotation() const
	{
		return rotation_;
	}

	void Transform::set_translation(const FVector3& translation)
	{
		translation_ = translation;
	}

	void Transform::set_scale(const FVector3& scale)
	{
		scale_ = scale;
	}

	FMatrix3x4 Transform::get_matrix() const
	{
		FMatrix3x4 matrix(rotation_.get_matrix());

		const size_t matrix_last_column_index = FMatrix3x4::WIDTH - 1;
		for (size_t i = 0; i < matrix_last_column_index; ++i)
			matrix[i] *= scale_[i];

		matrix[matrix_last_column_index] = translation_;
		return matrix;
	}

	FMatrix3x4 Transform::get_inverse_matrix() const
	{
		FMatrix3x4 matrix(get_vector_transformation_inverse_matrix());
		const FVector3 negative_translation = -translation_;

		const size_t matrix_last_column_index = FMatrix3x4::WIDTH - 1;
		FVector3& matrix_last_column = matrix[matrix_last_column_index];
		for (size_t i = 0; i < matrix_last_column_index; ++i)
			matrix_last_column += matrix[i] * negative_translation[i];

		return matrix;
	}

	FMatrix3 Transform::get_normal_matrix() const
	{
		return get_vector_transformation_inverse_matrix().get_transpose();
	}

	Transform::Concatenator Transform::get_relative_to_local() const
	{
		return Concatenator(get_matrix(), scale_, rotation_);
	}

	Transform::Concatenator Transform::get_local_to_relative() const
	{
		return Concatenator(get_inverse_matrix(), 1.f / scale_, rotation_.get_inverse());
	}
}
