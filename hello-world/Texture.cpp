#include <stb-master/stb_image.h>
#include "Texture.h"
#include "AssetRoots.h"

namespace Engine
{
	namespace Graphics
	{
		ID::Provider Texture::g_id_provider;

		void Texture::load(const SVector2& size, Format format, PixelData::Format pixel_data_format, PixelData::Type pixel_data_type, const void* p_pixel_data)
		{
			unload();

			glGenTextures(1, &handle_);

			bind();
			const Math::Vector<GLsizei, 2> gl_size = size;
			glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format), gl_size.x, gl_size.y, 0, static_cast<GLenum>(pixel_data_format), static_cast<GLenum>(pixel_data_type), p_pixel_data);
		}

		Texture::Texture(const String::View& name)
		{
			IVector2 size;
			int comp_count;

			String file_name = AssetRoots::TEXTURES.generic_string();
			file_name.append(name);

			Byte* const p_image_data = stbi_load(file_name.c_str(), &size.x, &size.y, &comp_count, 0);
			if (p_image_data)
			{
				// default values
				Format format = Format::RGBA;
				PixelData::Format data_format = PixelData::Format::RGBA;

				switch (comp_count)
				{
				case 1:
					data_format = PixelData::Format::RED;
					format = Format::RED;
					break;
				case 2:
					data_format = PixelData::Format::RG;
					format = Format::RG;
					break;
				case 3:
					data_format = PixelData::Format::RGB;
					format = Format::RGB;
				}

				load(size, format, data_format, PixelData::Type::UNSIGNED_BYTE, p_image_data);
				stbi_image_free(p_image_data);

				set_min_filter(MinFilter::LINEAR);
				set_mag_filter(MagFilter::LINEAR);
			}
		}

		Texture::Texture(const Color& color)
		{
			load(SVector2(1), Format::RGB, PixelData::Format::RGB, PixelData::Type::FLOAT, &color);

			set_min_filter(MinFilter::LINEAR);
			set_mag_filter(MagFilter::LINEAR);
		}

		Texture::Texture(const Table<float>& table)
		{
			load(table.get_dimensions(), Format::R16F, PixelData::Format::RED, PixelData::Type::FLOAT, table.get());

			set_min_filter(MinFilter::LINEAR);
			set_mag_filter(MagFilter::LINEAR);
		}

		Texture::Texture(const Table<FVector2>& table)
		{
			load(table.get_dimensions(), Format::RG16F, PixelData::Format::RG, PixelData::Type::FLOAT, table.get());

			set_min_filter(MinFilter::LINEAR);
			set_mag_filter(MagFilter::LINEAR);
		}

		Texture::Texture(const Table<FVector3>& table)
		{
			load(table.get_dimensions(), Format::RGB16F, PixelData::Format::RGB, PixelData::Type::FLOAT, table.get());

			set_min_filter(MinFilter::LINEAR);
			set_mag_filter(MagFilter::LINEAR);
		}

		Texture::Texture(const SVector2& size)
		{
			load(size, Format::DEPTH_COMPONENT, PixelData::Format::DEPTH_COMPONENT, PixelData::Type::FLOAT, nullptr);

			set_min_filter(MinFilter::NEAREST);
			set_mag_filter(MagFilter::NEAREST);
			set_wrap(Math::Vector<Wrap, 2>(Wrap::CLAMP_TO_EDGE));
		}

		Texture::Texture(const SVector2& size, Format format)
		{
			load(size, format, PixelData::Format::RGBA, PixelData::Type::FLOAT, nullptr);
		}

		Texture::Texture(const SVector2& size, Format format, PixelData::Format pixel_data_format, PixelData::Type pixel_data_type, const void* p_pixel_data)
		{
			load(size, format, pixel_data_format, pixel_data_type, p_pixel_data);
		}

		size_t Texture::get_location()
		{
			location_.assign();
			const size_t location = location_;

			glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(location));
			bind();

			return location;
		}

		GLuint Texture::get_handle() const
		{
			return handle_;
		}

		Texture::MinFilter Texture::get_min_filter() const
		{
			GLint filter;
			glGetTextureParameteriv(handle_, GL_TEXTURE_MIN_FILTER, &filter);
			return static_cast<MinFilter>(filter);
		}

		void Texture::set_min_filter(MinFilter filter) const
		{
			glTextureParameteri(handle_, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filter));
		}

		Texture::MagFilter Texture::get_mag_filter() const
		{
			GLint filter;
			glGetTextureParameteriv(handle_, GL_TEXTURE_MAG_FILTER, &filter);
			return static_cast<MagFilter>(filter);
		}

		void Texture::set_mag_filter(MagFilter filter) const
		{
			glTextureParameteri(handle_, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filter));
		}

		Math::Vector<Texture::Wrap, 2> Texture::get_wrap() const
		{
			Math::Vector<GLint, 2> wrap;
			glGetTextureParameteriv(handle_, GL_TEXTURE_WRAP_S, &wrap.s);
			glGetTextureParameteriv(handle_, GL_TEXTURE_WRAP_T, &wrap.t);
			return wrap;
		}

		void Texture::set_wrap(const Math::Vector<Wrap, 2>& wrap) const
		{
			glTextureParameteri(handle_, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrap.s));
			glTextureParameteri(handle_, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrap.t));
		}

		Texture::Texture(Texture&& rhs)
			: handle_(std::move(rhs.handle_))
			, location_(std::move(rhs.location_))
		{
			rhs.handle_ = 0;
		}

		Texture::~Texture()
		{
			unload();
		}

		Texture& Texture::operator=(Texture&& rhs)
		{
			if (this != &rhs)
			{
				unload();
				handle_ = std::move(rhs.handle_);
				location_ = std::move(rhs.location_);
				rhs.handle_ = 0;
			}

			return *this;
		}

		void Texture::unload()
		{
			release_location();
			glDeleteTextures(1, &handle_);
		}

		SVector2 Texture::get_size(size_t mipmap_level) const
		{
			Math::Vector<GLint, 2> size;
			const GLint int_mipmap_level = static_cast<GLint>(mipmap_level);
			glGetTextureLevelParameteriv(handle_, int_mipmap_level, GL_TEXTURE_WIDTH, &size.x);
			glGetTextureLevelParameteriv(handle_, int_mipmap_level, GL_TEXTURE_HEIGHT, &size.y);
			return size;
		}

		void Texture::bind() const
		{
			glBindTexture(GL_TEXTURE_2D, handle_);
		}

		void Texture::release_location()
		{
			location_.release();
		}

		void Texture::swap(Texture& rhs)
		{
			std::swap(handle_, rhs.handle_);
			std::swap(location_, rhs.location_);
		}
	}
}
