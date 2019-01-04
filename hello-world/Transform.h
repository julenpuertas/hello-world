#pragma once
#include "Rotation.h"

namespace Engine
{
	class Transform
	{
		FMatrix3 get_vector_transformation_inverse_matrix() const;

	public:
		class ParenthoodPolicy
		{
			bool translation_affected_;
			bool scale_affected_;
			bool rotation_affected_;

		public:
			explicit ParenthoodPolicy(bool value = true);
			ParenthoodPolicy(bool translation_affected, bool scale_affected, bool rotation_affected);

			bool is_translation_affected() const;
			bool is_scale_affected() const;
			bool is_rotation_affected() const;

			void set_translation_affected(bool translation_affected);
			void set_scale_affected(bool scale_affected);
			void set_rotation_affected(bool rotation_affected);
		};

		class Transformation
		{
			FMatrix3x4 translation_transformer_;
			FVector3 scale_transformer_;
			Rotation rotation_transformer_;

		public:
			Transformation(const FMatrix3x4& translation_transformer, const FVector3& scale_transformer, const Rotation& rotation_transformer);
			template <typename ... Args>
			Transform operator()(const Transform& transform, Args&& ... arguments) const;
		};

		FVector3 translation_;
		FVector3 scale_{ 1.f };
		Rotation rotation_;

		Transform() = default;
		template <typename ... Args>
		Transform(const FVector3& translation, const FVector3& scale, Args&& ... arguments);

		FMatrix3x4 get_matrix() const;
		FMatrix3x4 get_inverse_matrix() const;
		FMatrix3 get_normal_matrix() const;

		Transformation get_relative_to_local() const;
		Transformation get_local_to_relative() const;
	};
}

#include "Transform.inl"
