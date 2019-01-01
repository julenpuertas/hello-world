#include "Transform.h"

namespace Engine
{
	FMatrix3 Transform::get_vector_transformation_inverse_matrix() const
	{
		FVector3 inverse_scale = 1.f / scale_;
		FMatrix3 vector_transformation_inverse_matrix = rotation_.get_inverse().get_matrix();

		for (size_t i = 0; i < FMatrix3::WIDTH; ++i)
			vector_transformation_inverse_matrix[i] *= inverse_scale;

		return vector_transformation_inverse_matrix;
	}

	FMatrix3x4 Transform::get_matrix() const
	{
		FMatrix3x4 matrix(rotation_.get_matrix());

		const size_t matrix_last_column_index = FMatrix3x4::WIDTH - 1;
		for (size_t i = 0; i < matrix_last_column_index; ++i)
			matrix[i] *= scale_;

		matrix[matrix_last_column_index] = translation_;
		return matrix;
	}

	FMatrix3x4 Transform::get_inverse_matrix() const
	{
		FMatrix3x4 matrix(get_vector_transformation_inverse_matrix());
		const FVector3 negative_translation = -translation_;

		const size_t matrix_last_column_index = FMatrix3x4::WIDTH - 1;
		glm::fvec3& last_column = matrix[matrix_last_column_index];
		for (size_t i = 0; i < matrix_last_column_index; ++i)
		{
			const float negative_translation_coordinate = negative_translation[i];
			glm::fvec3& matrix_column = matrix[i];

			for (size_t j = 0; j < FMatrix3x4::HEIGTH; ++j)
				last_column[j] += matrix_column[j] * negative_translation_coordinate;
		}

		return matrix;
	}

	FMatrix3 Transform::get_normal_matrix() const
	{
		return get_vector_transformation_inverse_matrix().get_transpose();
	}

	Transform Transform::operator*(const Transform& rhs) const
	{
		return Transform(local_to_parent(rhs.translation_), scale_ * rhs.scale_, rotation_ * rhs.rotation_);
	}

	Transform Transform::operator / (const Transform& rhs) const
	{
		return Transform(rhs.parent_to_local(translation_), scale_ / rhs.scale_, rhs.rotation_.get_inverse() * rotation_);
	}

	FVector3 Transform::parent_to_local(const FVector3& point) const
	{
		return get_inverse_matrix() * point;
	}

	FVector3 Transform::local_to_parent(const FVector3& point) const
	{
		return get_matrix() * point;
	}
}
