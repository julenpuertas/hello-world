#include "GLSLProgram.h"

namespace
{

}

namespace Engine
{
	namespace Graphics
	{
		GLint GLSLProgram::get_uniform_location(const String::View& name) const
		{
			return glGetUniformLocation(handle_, name.data());
		}

		void GLSLProgram::unload()
		{
			if (is_loaded())
			{
				glDeleteProgram(handle_);
				handle_ = 0;
			}
		}

		bool GLSLProgram::is_loaded() const
		{
			return handle_ > 0;
		}

		size_t GLSLProgram::get_max_vertex_uniforms()
		{
			GLint count;
			glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &count);
			return count;
		}

		size_t GLSLProgram::get_max_fragment_uniforms()
		{
			GLint count;
			glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &count);
			return count;
		}

		size_t GLSLProgram::get_max_geometry_uniforms()
		{
			GLint count;
			glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, &count);
			return count;
		}

		GLSLProgram::GLSLProgram(const String::View& vertex_shader_name, const String::View& fragment_shader_name, std::ostream* p_ostream)
		{
		}

		GLSLProgram::GLSLProgram(const String::View& vertex_shader_name, const String::View& tesselation_control_shader_name, const String::View& tesselation_evaluation_shader_name, const String::View& fragment_shader_name, std::ostream* p_ostream)
		{
		}

		GLSLProgram::GLSLProgram(const String::View& vertex_shader_name, const String::View& geometry_shader_name, const String::View& fragment_shader_name, std::ostream* p_ostream)
		{
		}

		GLSLProgram::GLSLProgram(const String::View& vertex_shader_name, const String::View& tesselation_control_shader_name, const String::View& tesselation_evaluation_shader_name, const String::View& geometry_shader_name, const String::View& fragment_shader_name, std::ostream* p_ostream)
		{
		}

		GLSLProgram::GLSLProgram(const GLSLProgram& rhs)
		{
		}

		GLSLProgram::GLSLProgram(GLSLProgram&& rhs)
		{
		}

		GLSLProgram::~GLSLProgram()
		{
		}

		GLSLProgram& GLSLProgram::operator=(const GLSLProgram& rhs)
		{
			if (this != &rhs)
				return *this;

			return *this;
		}
		GLSLProgram& GLSLProgram::operator=(GLSLProgram&& rhs)
		{
			if (this != &rhs)
				return *this;

			return *this;
		}
		bool GLSLProgram::operator==(const GLSLProgram & rhs) const
		{
			return false;
		}
		bool GLSLProgram::operator!=(const GLSLProgram & rhs) const
		{
			return false;
		}
		void GLSLProgram::use() const
		{
		}
		String GLSLProgram::build()
		{
			return String();
		}
		String GLSLProgram::get_log() const
		{
			return String();
		}
		size_t GLSLProgram::get_shader_count() const
		{
			return size_t();
		}
		size_t GLSLProgram::get_active_subroutine_uniform_locations(const Stage shader_type) const
		{
			return size_t();
		}
		template<> std::optional<bool> GLSLProgram::get_uniform<bool>(const String::View& name) const
		{
			return bool();
		}

		template<> std::optional<int> GLSLProgram::get_uniform<int>(const String::View& name) const
		{
			return int();
		}

		template<> std::optional<unsigned> GLSLProgram::get_uniform<unsigned>(const String::View& name) const
		{
			return unsigned();
		}

		template<> std::optional<float> GLSLProgram::get_uniform<float>(const String::View& name) const
		{
			return float();
		}

		template<> std::optional<SVector2> GLSLProgram::get_uniform<SVector2>(const String::View& name) const
		{
			return SVector2();
		}

		template<> std::optional<IVector2> GLSLProgram::get_uniform<IVector2>(const String::View& name) const
		{
			return IVector2();
		}

		template<> std::optional<FVector2> GLSLProgram::get_uniform<FVector2>(const String::View& name) const
		{
			return FVector2();
		}

		template<> std::optional<FVector3> GLSLProgram::get_uniform<FVector3>(const String::View& name) const
		{
			return FVector3();
		}

		template<> std::optional<FVector4> GLSLProgram::get_uniform<FVector4>(const String::View& name) const
		{
			return FVector4();
		}

		template<> std::optional<FMatrix3> GLSLProgram::get_uniform<FMatrix3>(const String::View& name) const
		{
			return FMatrix3();
		}

		template<> std::optional<FMatrix4> GLSLProgram::get_uniform<FMatrix4>(const String::View& name) const
		{
			return FMatrix4();
		}

		bool GLSLProgram::set_uniform(const String::View& name, bool value) const
		{
		}
		bool GLSLProgram::set_uniform(const String::View& name, int value) const
		{
		}
		bool GLSLProgram::set_uniform(const String::View& name, unsigned value) const
		{
		}
		bool GLSLProgram::set_uniform(const String::View& name, float value) const
		{
		}
		bool GLSLProgram::set_uniform(const String::View& name, const SVector2& vector) const
		{
		}
		bool GLSLProgram::set_uniform(const String::View& name, const IVector2& vector) const
		{
		}
		bool GLSLProgram::set_uniform(const String::View& name, const FVector2& vector) const
		{
		}
		bool GLSLProgram::set_uniform(const String::View& name, const FVector3& vector) const
		{
		}
		bool GLSLProgram::set_uniform(const String::View& name, const FVector4& vector) const
		{
		}
		bool GLSLProgram::set_uniform(const String::View& name, const FMatrix3& matrix) const
		{
		}
		bool GLSLProgram::set_uniform(const String::View& name, const FMatrix4& matrix) const
		{
		}
		bool GLSLProgram::set_uniform(const String::View& name, Texture& texture) const
		{
		}
		bool GLSLProgram::set_uniform(const String::View& name, const Transform& camera_transform, const Light& light) const
		{
		}
		bool GLSLProgram::set_uniform(const String::View& name, const Material& material) const
		{
		}
		bool GLSLProgram::set_uniform(const Map<String::View>& names, Stage stage) const
		{
		}
		void GLSLProgram::swap(GLSLProgram & rhs)
		{
		}
	}
}
