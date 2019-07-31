#include <fstream>
#include "Array.h"
#include "AssetRoots.h"
#include "GLSLProgram.h"

namespace
{
	void load_shader(const Engine::String::View& shader_file_name, Engine::String& shader_src, std::ostream& error_log)
	{
		using namespace Engine;

		std::filesystem::path file_name = AssetRoots::SHADERS;
		file_name.append(shader_file_name);
		std::ifstream shader_file(file_name);
		if (!shader_file.good())
			error_log << "Could not open file " << shader_file_name << '.' << std::endl;

		String line;
		while (shader_file.good())
		{
			std::getline(shader_file, line);
			shader_src += line;
			shader_src += '\n';
			line.clear();
		}
	}

	std::optional<GLuint> load_shader(const Engine::String::View& shader_file_name, Engine::Graphics::GLSLProgram::Stage glsl_program_stage, std::ostream& error_log)
	{
		using namespace Engine;
		using Graphics::GLSLProgram;

		if (shader_file_name.empty())
			return std::nullopt;

		String shader_src;
		load_shader(shader_file_name, shader_src, error_log);
		const char* shader_src_c_str = shader_src.c_str();

		const GLuint shader = glCreateShader(static_cast<GLenum>(glsl_program_stage));
		glShaderSource(shader, 1, &shader_src_c_str, nullptr);
		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status != GL_FALSE)
			return shader;

		GLint info_log_length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);

		std::unique_ptr<GLchar> info_log(new GLchar[info_log_length]);
		GLchar* p_info_log_data = info_log.get();
		glGetShaderInfoLog(shader, info_log_length, nullptr, p_info_log_data);

		error_log << "Compile failure in ";
		switch (glsl_program_stage)
		{
		case GLSLProgram::Stage::VERTEX:
			error_log << "vertex";
			break;
		case GLSLProgram::Stage::TESSELATION_CONTROL:
			error_log << "tess control";
			break;
		case GLSLProgram::Stage::TESSELATION_EVALUATION:
			error_log << "tess evaluation";
			break;
		case GLSLProgram::Stage::GEOMETRY:
			error_log << "geometry";
			break;
		case GLSLProgram::Stage::FRAGMENT:
			error_log << "fragmet";
			break;
		}
		error_log << " shader:" << std::endl << p_info_log_data << std::endl;

		return std::nullopt;
	}
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

		GLSLProgram::GLSLProgram(const String::View& vertex_shader_name, const String::View& fragment_shader_name, std::ostream& error_log)
			: vertex_shader_name_(vertex_shader_name)
			, fragment_shader_name_(fragment_shader_name)
		{
			build(error_log);
		}

		GLSLProgram::GLSLProgram(const String::View& vertex_shader_name, const String::View& tesselation_control_shader_name, const String::View& tesselation_evaluation_shader_name, const String::View& fragment_shader_name, std::ostream& error_log)
			: vertex_shader_name_(vertex_shader_name)
			, tesselation_control_shader_name_(tesselation_control_shader_name)
			, tesselation_evaluation_shader_name_(tesselation_evaluation_shader_name)
			, fragment_shader_name_(fragment_shader_name)
		{
			build(error_log);
		}

		GLSLProgram::GLSLProgram(const String::View& vertex_shader_name, const String::View& geometry_shader_name, const String::View& fragment_shader_name, std::ostream& error_log)
			: vertex_shader_name_(vertex_shader_name)
			, geometry_shader_name_(geometry_shader_name)
			, fragment_shader_name_(fragment_shader_name)
		{
			build(error_log);
		}

		GLSLProgram::GLSLProgram(const String::View& vertex_shader_name, const String::View& tesselation_control_shader_name, const String::View& tesselation_evaluation_shader_name, const String::View& geometry_shader_name, const String::View& fragment_shader_name, std::ostream& error_log)
			: vertex_shader_name_(vertex_shader_name)
			, tesselation_control_shader_name_(tesselation_control_shader_name)
			, tesselation_evaluation_shader_name_(tesselation_evaluation_shader_name)
			, geometry_shader_name_(geometry_shader_name)
			, fragment_shader_name_(fragment_shader_name)
		{
			build(error_log);
		}

		GLSLProgram::GLSLProgram(const GLSLProgram& rhs, std::ostream& error_log)
			: vertex_shader_name_(rhs.vertex_shader_name_)
			, tesselation_control_shader_name_(rhs.tesselation_control_shader_name_)
			, tesselation_evaluation_shader_name_(rhs.tesselation_evaluation_shader_name_)
			, geometry_shader_name_(rhs.geometry_shader_name_)
			, fragment_shader_name_(rhs.fragment_shader_name_)
		{
			build(error_log);
		}

		GLSLProgram::GLSLProgram(GLSLProgram&& rhs)
			: handle_(std::move(rhs.handle_))
			, vertex_shader_name_(std::move(rhs.vertex_shader_name_))
			, tesselation_control_shader_name_(std::move(rhs.tesselation_control_shader_name_))
			, tesselation_evaluation_shader_name_(std::move(rhs.tesselation_evaluation_shader_name_))
			, geometry_shader_name_(std::move(rhs.geometry_shader_name_))
			, fragment_shader_name_(std::move(rhs.fragment_shader_name_))
		{
			rhs.handle_ = 0;
		}

		GLSLProgram::~GLSLProgram()
		{
			unload();
		}

		GLSLProgram& GLSLProgram::operator=(GLSLProgram&& rhs)
		{
			if (this == &rhs)
				return *this;

			unload();

			handle_ = std::move(rhs.handle_);
			rhs.handle_ = 0;

			vertex_shader_name_ = std::move(rhs.vertex_shader_name_);
			tesselation_control_shader_name_ = std::move(rhs.tesselation_control_shader_name_);
			tesselation_evaluation_shader_name_ = std::move(rhs.tesselation_evaluation_shader_name_);
			geometry_shader_name_ = std::move(rhs.geometry_shader_name_);
			fragment_shader_name_ = std::move(rhs.fragment_shader_name_);

			return *this;
		}

		bool GLSLProgram::operator==(const GLSLProgram& rhs) const
		{
			return vertex_shader_name_ == rhs.vertex_shader_name_ && tesselation_control_shader_name_ == rhs.tesselation_control_shader_name_ && tesselation_evaluation_shader_name_ == rhs.tesselation_evaluation_shader_name_ && geometry_shader_name_ == rhs.geometry_shader_name_ && fragment_shader_name_ == rhs.fragment_shader_name_;
		}

		bool GLSLProgram::operator!=(const GLSLProgram& rhs) const
		{
			return !(*this == rhs);
		}

		void GLSLProgram::use() const
		{
			GLint current_program_handle;
			glGetIntegerv(GL_CURRENT_PROGRAM, &current_program_handle);

			if (current_program_handle != handle_ && is_loaded())
				glUseProgram(handle_);
		}

		void GLSLProgram::build(std::ostream& error_log)
		{
			constexpr size_t max_glsl_program_stages = 5;
			size_t compiled_shader_count = 0;
			Array<GLuint, max_glsl_program_stages> shader_list;

			const auto compile_shader = [&shader_list, &compiled_shader_count, &error_log](const String::View& shader_file_name, Stage glsl_program_stage)
			{
				const std::optional<GLuint> shader = load_shader(shader_file_name, glsl_program_stage, error_log);
				if (shader)
					shader_list[compiled_shader_count++] = *shader;
			};

			compile_shader(vertex_shader_name_, Stage::VERTEX);
			compile_shader(tesselation_control_shader_name_, Stage::TESSELATION_CONTROL);
			compile_shader(tesselation_evaluation_shader_name_, Stage::TESSELATION_EVALUATION);
			compile_shader(geometry_shader_name_, Stage::GEOMETRY);
			compile_shader(fragment_shader_name_, Stage::FRAGMENT);

			handle_ = glCreateProgram();
			for (size_t i = 0; i < compiled_shader_count; ++i)
				glAttachShader(handle_, shader_list[i]);

			glLinkProgram(handle_);
			GLint status;
			glGetProgramiv(handle_, GL_LINK_STATUS, &status);
			if (status == GL_FALSE)
			{
				GLint info_log_length;
				glGetProgramiv(handle_, GL_INFO_LOG_LENGTH, &info_log_length);

				std::unique_ptr<GLchar> info_log(new GLchar[info_log_length]);
				GLchar* p_info_log_data = info_log.get();
				glGetProgramInfoLog(handle_, info_log_length, nullptr, p_info_log_data);

				error_log << "Linker failure: ";
				error_log << p_info_log_data;
				unload();
			}

			for (size_t i = 0; i < compiled_shader_count; ++i)
			{
				const GLuint shader = shader_list[i];
				glDetachShader(handle_, shader);
				glDeleteShader(shader);
			}
		}

		size_t GLSLProgram::get_shader_count() const
		{
			GLint count = 0;
			glGetProgramiv(handle_, GL_ATTACHED_SHADERS, &count);
			return count;
		}

		size_t GLSLProgram::get_active_subroutine_uniform_locations(const Stage shader_type) const
		{
			GLint value = 0;
			glGetProgramStageiv(handle_, static_cast<GLenum>(shader_type), GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS, &value);
			return value;
		}

		template<> std::optional<bool> GLSLProgram::get_uniform<bool>(const String::View& name) const
		{
			const std::optional<unsigned> optional_uniform = get_uniform<unsigned>(name);
			if (optional_uniform)
				return (*optional_uniform) != 0;

			return std::nullopt;
		}

		template<> std::optional<int> GLSLProgram::get_uniform<int>(const String::View& name) const
		{
			GLint value;
			const GLint unniform_location = get_uniform_location(name);
			if (unniform_location < 0)
				return std::nullopt;

			glGetnUniformiv(handle_, unniform_location, 1, &value);
			return value;
		}

		template<> std::optional<unsigned> GLSLProgram::get_uniform<unsigned>(const String::View& name) const
		{
			GLuint value;
			const GLint unniform_location = get_uniform_location(name);
			if (unniform_location < 0)
				return std::nullopt;

			glGetnUniformuiv(handle_, unniform_location, 1, &value);
			return value;
		}

		template<> std::optional<float> GLSLProgram::get_uniform<float>(const String::View& name) const
		{
			GLfloat value;
			const GLint unniform_location = get_uniform_location(name);
			if (unniform_location < 0)
				return std::nullopt;

			glGetnUniformfv(handle_, unniform_location, 1, &value);
			return value;
		}

		template<> std::optional<SVector2> GLSLProgram::get_uniform<SVector2>(const String::View& name) const
		{
			return SVector2();
		}

		template<> std::optional<IVector2> GLSLProgram::get_uniform<IVector2>(const String::View& name) const
		{
			IVector2 value;
			const GLint unniform_location = get_uniform_location(name);
			if (unniform_location < 0)
				return std::nullopt;

			glGetnUniformiv(handle_, unniform_location, IVector2::SIZE, &value.x);
			return value;
		}

		template<> std::optional<FVector2> GLSLProgram::get_uniform<FVector2>(const String::View& name) const
		{
			FVector2 value;
			const GLint unniform_location = get_uniform_location(name);
			if (unniform_location < 0)
				return std::nullopt;

			glGetnUniformfv(handle_, unniform_location, FVector2::SIZE, &value.x);
			return value;
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

		void GLSLProgram::swap(GLSLProgram& rhs)
		{

		}

		void GLSLProgram::write(std::ostream& ostream) const
		{
			GLint status;
			glValidateProgram(handle_);
			glGetProgramiv(handle_, GL_VALIDATE_STATUS, &status);

			if (status != GL_FALSE)
				return;

			GLint info_log_length;
			glGetProgramiv(handle_, GL_INFO_LOG_LENGTH, &info_log_length);

			if (info_log_length <= 0)
				return;

			std::unique_ptr<GLchar> info_log(new GLchar[info_log_length]);
			GLchar* p_info_log_data = info_log.get();
			glGetProgramInfoLog(handle_, info_log_length, nullptr, p_info_log_data);
			ostream << p_info_log_data << std::endl;
		}
	}
}
