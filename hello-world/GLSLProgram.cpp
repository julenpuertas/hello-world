#include <fstream>
#include "Angles.h"
#include "AssetRoots.h"
#include "Light.h"
#include "Texture.h"
#include "GraphicsMaterial.h"
#include "GameObject.h"
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

		const std::unique_ptr<GLchar[]> info_log(new GLchar[info_log_length]);
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
		void GLSLProgram::SetSubroutineUniformsResult::incorrect_subroutine_count_set()
		{
			correct_subroutine_count_set_ = false;
		}

		void GLSLProgram::SetSubroutineUniformsResult::add_non_set_subroutine_uniform_name(const String::View& non_set_subroutine_uniform_name)
		{
			non_set_subroutine_uniforms_names_.emplace_back(non_set_subroutine_uniform_name);
		}

		void GLSLProgram::SetSubroutineUniformsResult::add_non_set_subroutine_name(const String::View& non_set_subroutine_name)
		{
			non_set_subroutines_names_.emplace_back(non_set_subroutine_name);
		}

		GLSLProgram::SetSubroutineUniformsResult::operator bool() const
		{
			return non_set_subroutines_names_.empty() && non_set_subroutine_uniforms_names_.empty();
		}

		bool GLSLProgram::SetSubroutineUniformsResult::operator!() const
		{
			return !static_cast<bool>(*this);
		}

		void GLSLProgram::SetSubroutineUniformsResult::write(std::ostream& ostream) const
		{
			if (!correct_subroutine_count_set_)
			{
				ostream << "Incorrect count of subrotines set." << std::endl;
				return;
			}

			for (const String& non_set_subroutine_name : non_set_subroutines_names_)
				ostream << "Subroutine: " << non_set_subroutine_name << " not found." << std::endl;

			for (const String& non_set_subroutine_uniform_name : non_set_subroutine_uniforms_names_)
				ostream << "Subroutine uniform: " << non_set_subroutine_uniform_name << " not found." << std::endl;
		}

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

				const std::unique_ptr<GLchar[]> info_log(new GLchar[info_log_length]);
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
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return std::nullopt;

			glGetnUniformiv(handle_, uniform_location, 1, &value);
			return value;
		}

		template<> std::optional<unsigned> GLSLProgram::get_uniform<unsigned>(const String::View& name) const
		{
			GLuint value;
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return std::nullopt;

			glGetnUniformuiv(handle_, uniform_location, 1, &value);
			return value;
		}

		template<> std::optional<float> GLSLProgram::get_uniform<float>(const String::View& name) const
		{
			GLfloat value;
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return std::nullopt;

			glGetnUniformfv(handle_, uniform_location, 1, &value);
			return value;
		}

		template<> std::optional<SVector2> GLSLProgram::get_uniform<SVector2>(const String::View& name) const
		{
			Math::Vector<GLuint, 2> value;
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return std::nullopt;

			glGetnUniformuiv(handle_, uniform_location, Math::Vector<GLuint, 2>::SIZE, value.begin());
			return value;
		}

		template<> std::optional<IVector2> GLSLProgram::get_uniform<IVector2>(const String::View& name) const
		{
			IVector2 value;
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return std::nullopt;

			glGetnUniformiv(handle_, uniform_location, IVector2::SIZE, value.begin());
			return value;
		}

		template<> std::optional<FVector2> GLSLProgram::get_uniform<FVector2>(const String::View& name) const
		{
			FVector2 value;
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return std::nullopt;

			glGetnUniformfv(handle_, uniform_location, FVector2::SIZE, value.begin());
			return value;
		}

		template<> std::optional<FVector3> GLSLProgram::get_uniform<FVector3>(const String::View& name) const
		{
			FVector3 value;
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return std::nullopt;

			glGetnUniformfv(handle_, uniform_location, FVector3::SIZE, value.begin());
			return value;
		}

		template<> std::optional<FVector4> GLSLProgram::get_uniform<FVector4>(const String::View& name) const
		{
			FVector4 value;
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return std::nullopt;

			glGetnUniformfv(handle_, uniform_location, FVector4::SIZE, value.begin());
			return value;
		}

		template<> std::optional<FMatrix3> GLSLProgram::get_uniform<FMatrix3>(const String::View& name) const
		{
			FMatrix3 value;
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return std::nullopt;

			glGetnUniformfv(handle_, uniform_location, FMatrix3::WIDTH * FMatrix3::HEIGTH, value.begin());
			return value;
		}

		template<> std::optional<FMatrix4> GLSLProgram::get_uniform<FMatrix4>(const String::View& name) const
		{
			FMatrix4 value;
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return std::nullopt;

			glGetnUniformfv(handle_, uniform_location, FMatrix4::WIDTH * FMatrix4::HEIGTH, value.begin());
			return value;
		}

		bool GLSLProgram::try_set_uniform(const String::View& name, bool value) const
		{
			return try_set_uniform(name, value ? 1u : 0u);
		}

		bool GLSLProgram::try_set_uniform(const String::View& name, int value) const
		{
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return false;

			glProgramUniform1i(handle_, uniform_location, value);
			return true;
		}

		bool GLSLProgram::try_set_uniform(const String::View& name, unsigned value) const
		{
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return false;

			glProgramUniform1ui(handle_, uniform_location, value);
			return true;
		}

		bool GLSLProgram::try_set_uniform(const String::View& name, float value) const
		{
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return false;

			glProgramUniform1f(handle_, uniform_location, value);
			return true;
		}

		bool GLSLProgram::try_set_uniform(const String::View& name, const SVector2& vector) const
		{
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return false;

			Math::Vector<GLuint, 2> ogl_vector = vector;
			glProgramUniform2ui(handle_, uniform_location, ogl_vector.x, ogl_vector.y);
			return true;
		}

		bool GLSLProgram::try_set_uniform(const String::View& name, const IVector2& vector) const
		{
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return false;

			glProgramUniform2i(handle_, uniform_location, vector.x, vector.y);
			return true;
		}

		bool GLSLProgram::try_set_uniform(const String::View& name, const FVector2& vector) const
		{
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return false;

			glProgramUniform2f(handle_, uniform_location, vector.x, vector.y);
			return true;
		}

		bool GLSLProgram::try_set_uniform(const String::View& name, const FVector3& vector) const
		{
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return false;

			glProgramUniform3f(handle_, uniform_location, vector.x, vector.y, vector.z);
			return true;
		}

		bool GLSLProgram::try_set_uniform(const String::View& name, const FVector4& vector) const
		{
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return false;

			glProgramUniform4f(handle_, uniform_location, vector.x, vector.y, vector.z, vector.w);
			return true;
		}

		bool GLSLProgram::try_set_uniform(const String::View& name, const FMatrix3& matrix) const
		{
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return false;

			glProgramUniformMatrix3fv(handle_, uniform_location, 1, GL_FALSE, matrix.cbegin());
			return true;
		}

		bool GLSLProgram::try_set_uniform(const String::View& name, const FMatrix4& matrix) const
		{
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return false;

			glProgramUniformMatrix4fv(handle_, uniform_location, 1, GL_FALSE, matrix.cbegin());
			return true;
		}

		bool GLSLProgram::try_set_uniform(const String::View& name, const Transform& camera_transform, const Light& light) const
		{
#if 0
			const GameObject* p_light_owner = light.get_owner();
			if (!p_light_owner)
				return false;

			Transform light_transform = p_light_owner->get_world_transform();
			const Transform::Concatenator local_to_camera_relative = camera_transform.get_local_to_relative();
			light_transform = local_to_camera_relative.concatenate(light_transform, Transform::Concatenator::Policy(true));

			const size_t name_size = name.size();

			String material_name = name;
			material_name += ".translation_";
			if (!try_set_uniform(material_name, light_transform.get_translation()))
				return false;

			material_name.erase(name_size);
			material_name += ".orientation_";
			if (!try_set_uniform(material_name, light_transform.get_rotation().get_orientation(Math::Axis::Z)))
				return false;

			material_name.erase(name_size);
			material_name += ".type_";
			if (!try_set_uniform(material_name, static_cast<unsigned>(light.get_type())))
				return false;

			material_name.erase(name_size);
			material_name += ".inner_cone_radians_";
			if (!try_set_uniform(material_name, Math::Angles::degrees_to_radians(light.get_inner_cone_degrees())))
				return false;

			material_name.erase(name_size);
			material_name += ".outer_cone_radians_";
			if (!try_set_uniform(material_name, Math::Angles::degrees_to_radians(light.get_outer_cone_degrees())))
				return false;

			material_name.erase(name_size);
			material_name += ".attenuation_";
			if (!try_set_uniform(material_name, light.get_attenuation()))
				return false;

			material_name.erase(name_size);
			material_name += ".ambient_";
			if (!try_set_uniform(material_name, light.get_ambient()))
				return false;

			material_name.erase(name_size);
			material_name += ".diffuse_";
			if (!try_set_uniform(material_name, light.get_diffuse()))
				return false;

			material_name.erase(name_size);
			material_name += ".specular_";
			return try_set_uniform(material_name, light.get_specular());
#endif
			return false;
		}

		bool GLSLProgram::try_set_uniform(const String::View& name, Texture& texture) const
		{
			const GLint uniform_location = get_uniform_location(name);
			if (uniform_location < 0)
				return false;

			glProgramUniform1i(handle_, uniform_location, static_cast<GLint>(texture.get_location()));
			return true;
		}

		bool GLSLProgram::try_set_uniform(const String::View& name, const Material& material) const
		{
			const size_t name_size = name.size();

			String material_name = name;
			material_name += ".diffuse_";
			if (!try_set_uniform(material_name, material.get_diffuse()))
				return false;

			material_name.erase(name_size);
			material_name += ".specular_";
			if (!try_set_uniform(material_name, material.get_specular()))
				return false;

			material_name.erase(name_size);
			material_name += ".emissive_";
			if (!try_set_uniform(material_name, material.get_emissive()))
				return false;

			material_name.erase(name_size);
			material_name += ".shininess_";
			if (!try_set_uniform(material_name, material.get_shininess()))
				return false;

			material_name.erase(name_size);
			material_name += ".normal_map_";
			if (!try_set_uniform(material_name, material.get_normal_map()))
				return false;

			material_name.erase(name_size);
			material_name += ".depth_map_";
			if (!try_set_uniform(material_name, material.get_depth_map()))
				return false;

			material_name.erase(name_size);
			material_name += ".parallax_scale_";
			return try_set_uniform(material_name, material.get_parallax_scale());
		}

		GLSLProgram::SetSubroutineUniformsResult GLSLProgram::set_subroutine_uniforms(const Map<String::View>& names, Stage stage) const
		{
			SetSubroutineUniformsResult result;
			const size_t required_names_size = get_active_subroutine_uniform_locations(stage);
			if (required_names_size != names.size())
			{
				result.incorrect_subroutine_count_set();
				return result;
			}

			const std::unique_ptr<GLuint[]> indices(new GLuint[required_names_size]);
			GLuint* const p_indices = indices.get();
			std::fill(p_indices, p_indices + required_names_size, GL_INVALID_INDEX);

			const GLenum stage_index = static_cast<GLenum>(stage);
			bool all_set = true;

			for (const Pair<const String::View, String::View>& uniform_subroutine : names)
			{
				const GLuint index = glGetSubroutineIndex(handle_, stage_index, uniform_subroutine.second.data());
				if (index == GL_INVALID_INDEX)
				{
					result.add_non_set_subroutine_name(uniform_subroutine.second);
					all_set = false;
				}

				else
				{
					const GLint location = glGetSubroutineUniformLocation(handle_, stage_index, uniform_subroutine.first.data());
					if (location < 0)
					{
						result.add_non_set_subroutine_uniform_name(uniform_subroutine.first);
						all_set = false;
					}

					else p_indices[location] = index;
				}
			}

			if (all_set)
				glUniformSubroutinesuiv(stage_index, static_cast<GLsizei>(required_names_size), p_indices);

			return result;
		}

		void GLSLProgram::swap(GLSLProgram& rhs)
		{
			std::swap(handle_, rhs.handle_);

			vertex_shader_name_.swap(rhs.vertex_shader_name_);
			tesselation_control_shader_name_.swap(rhs.tesselation_control_shader_name_);
			tesselation_evaluation_shader_name_.swap(rhs.tesselation_evaluation_shader_name_);
			geometry_shader_name_.swap(rhs.geometry_shader_name_);
			fragment_shader_name_.swap(rhs.fragment_shader_name_);
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

			const std::unique_ptr<GLchar[]> info_log(new GLchar[info_log_length]);
			GLchar* p_info_log_data = info_log.get();
			glGetProgramInfoLog(handle_, info_log_length, nullptr, p_info_log_data);
			ostream << p_info_log_data << std::endl;
		}
	}
}
