#pragma once
#include "Rotation.h"

namespace Engine
{
	class Transform
	{
		FMatrix3 get_vector_transformation_inverse_matrix() const;

		FVector3 translation_;
		FVector3 scale_{ 1.f };
		Rotation rotation_;

	public:
		class Concatenator
		{
			FMatrix3x4 translation_transformer_;
			FVector3 scale_transformer_;
			Rotation rotation_transformer_;

		public:
			class Policy
			{
				bool translation_affected_;
				bool scale_affected_;
				bool rotation_affected_;

			public:
				explicit Policy(bool value = true);
				Policy(bool translation_affected, bool scale_affected, bool rotation_affected);

				bool is_translation_affected() const;
				bool is_scale_affected() const;
				bool is_rotation_affected() const;

				void set_translation_affected(bool translation_affected);
				void set_scale_affected(bool scale_affected);
				void set_rotation_affected(bool rotation_affected);
			};

			Concatenator(const FMatrix3x4& translation_transformer, const FVector3& scale_transformer, const Rotation& rotation_transformer);
			Transform concatenate(const Transform& transform, const Policy& policy) const;
		};

		Transform() = default;
		template <typename ... Args> Transform(const FVector3& translation, const FVector3& scale, Args&& ... arguments);

		const FVector3& get_translation() const;
		const FVector3& get_scale() const;
		const Rotation& get_rotation() const;

		void set_translation(const FVector3& translation);
		void set_scale(const FVector3& scale);
		template <typename ... Args> void set_rotation(Args&& ... arguments);

		FMatrix3x4 get_matrix() const;
		FMatrix3x4 get_inverse_matrix() const;
		FMatrix3 get_normal_matrix() const;

		Concatenator get_relative_to_local() const;
		Concatenator get_local_to_relative() const;
	};
}

#include "Transform.inl"
