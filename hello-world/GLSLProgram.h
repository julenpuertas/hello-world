#pragma once
#include <optional>
#include <GL/glew.h>
#include "Swapable.h"
#include "Map.h"
#include "Matrix.h"
#include "Writable.h"

#include "GraphicsMaterial.h"
#include "Light.h"
#include "Transform.h"

namespace Engine
{
	//class Transform;

	namespace Graphics
	{
		class Texture;
		//class Light;
		//class Material;

		class GLSLProgram
			: public IO::IWritable
			, public ISwapable<GLSLProgram>
		{
			GLint handle_ = 0;
			String vertex_shader_name_;
			String tesselation_control_shader_name_;
			String tesselation_evaluation_shader_name_;
			String geometry_shader_name_;
			String fragment_shader_name_;

			GLint get_uniform_location(const String::View& name) const;
			void unload();
			bool is_loaded() const;

		public:
			enum class Stage : GLenum
			{
				VERTEX = GL_VERTEX_SHADER,
				TESSELATION_CONTROL = GL_TESS_CONTROL_SHADER,
				TESSELATION_EVALUATION = GL_TESS_EVALUATION_SHADER,
				GEOMETRY = GL_GEOMETRY_SHADER,
				FRAGMENT = GL_FRAGMENT_SHADER
			};

			class SetSubroutineUniformsResult
				: public IO::IWritable
			{
				DynamicArray<String> non_set_subroutine_uniforms_names_;
				DynamicArray<String> non_set_subroutines_names_;
				bool correct_subroutine_count_set_ = true;

			public:
				void incorrect_subroutine_count_set();
				void add_non_set_subroutine_uniform_name(const String::View& non_set_subroutine_uniform_name);
				void add_non_set_subroutine_name(const String::View& non_set_subroutine_name);

				operator bool() const;
				bool operator!() const;

				void write(std::ostream& ostream) const override;
			};

			static size_t get_max_vertex_uniforms();
			static size_t get_max_fragment_uniforms();
			static size_t get_max_geometry_uniforms();

			GLSLProgram(const String::View& vertex_shader_name, const String::View& fragment_shader_name, std::ostream& error_log);
			GLSLProgram(const String::View& vertex_shader_name, const String::View& tesselation_control_shader_name, const String::View& tesselation_evaluation_shader_name, const String::View& fragment_shader_name, std::ostream& error_log);
			GLSLProgram(const String::View& vertex_shader_name, const String::View& geometry_shader_name, const String::View& fragment_shader_name, std::ostream& error_log);
			GLSLProgram(const String::View& vertex_shader_name, const String::View& tesselation_control_shader_name, const String::View& tesselation_evaluation_shader_name, const String::View& geometry_shader_name, const String::View& fragment_shader_name, std::ostream& error_log);
			GLSLProgram(const GLSLProgram& rhs, std::ostream& error_log);
			GLSLProgram(GLSLProgram&& rhs);
			~GLSLProgram();

			GLSLProgram& operator=(const GLSLProgram& rhs) = delete;
			GLSLProgram& operator=(GLSLProgram&& rhs);

			bool operator==(const GLSLProgram& rhs) const;
			bool operator!=(const GLSLProgram& rhs) const;

			void use() const;
			void build(std::ostream& error_log);
			size_t get_shader_count() const;
			size_t get_active_subroutine_uniform_locations(const Stage shader_type) const;

			template <typename T> std::optional<T> get_uniform(const String::View& name) const;

			template <> std::optional<bool> get_uniform<bool>(const String::View& name) const;
			template <> std::optional<int> get_uniform<int>(const String::View& name) const;
			template <> std::optional<unsigned> get_uniform<unsigned>(const String::View& name) const;
			template <> std::optional<float> get_uniform<float>(const String::View& name) const;
			template <> std::optional<SVector2> get_uniform<SVector2>(const String::View& name) const;
			template <> std::optional<IVector2> get_uniform<IVector2>(const String::View& name) const;
			template <> std::optional<FVector2> get_uniform<FVector2>(const String::View& name) const;
			template <> std::optional<FVector3> get_uniform<FVector3>(const String::View& name) const;
			template <> std::optional<FVector4> get_uniform<FVector4>(const String::View& name) const;
			template <> std::optional<FMatrix3> get_uniform<FMatrix3>(const String::View& name) const;
			template <> std::optional<FMatrix4> get_uniform<FMatrix4>(const String::View& name) const;

			bool set_uniform(const String::View& name, bool value) const;
			bool set_uniform(const String::View& name, int value) const;
			bool set_uniform(const String::View& name, unsigned value) const;
			bool set_uniform(const String::View& name, float value) const;
			bool set_uniform(const String::View& name, const SVector2& vextor) const;
			bool set_uniform(const String::View& name, const IVector2& vextor) const;
			bool set_uniform(const String::View& name, const FVector2& vextor) const;
			bool set_uniform(const String::View& name, const FVector3& vextor) const;
			bool set_uniform(const String::View& name, const FVector4& vextor) const;
			bool set_uniform(const String::View& name, const FMatrix3& matrix) const;
			bool set_uniform(const String::View& name, const FMatrix4& matrix) const;
			bool set_uniform(const String::View& name, Texture& texture) const;
			bool set_uniform(const String::View& name, const Transform& camera_transform, const Light& light) const;
			bool set_uniform(const String::View& name, const Material& material) const;
			SetSubroutineUniformsResult set_subroutine_uniforms(const Map<String::View>& names, Stage stage) const;

			void swap(GLSLProgram& rhs) override;
			void write(std::ostream& ostream) const override;

			//void set_uniform(const String::View& name, const DynamicArray<float>& values) const;
			//void set_uniform(const String::View& name, const DynamicArray<FMatrix4>& values) const;
			//void set_uniform(const String::View& name, const DynamicArray<FMatrix3>& values) const;
			//void set_uniform(const String::View& name, const DynamicArray<FVector4>& values) const;
		};
	}
}
