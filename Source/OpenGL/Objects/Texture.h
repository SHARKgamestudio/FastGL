#pragma once

#include "../Common/Object.h"
#include "../Common/IBindable.h"

#include <string>

namespace OpenGL {
	/// <summary>
	/// A struct storing raw texture data loaded from an image file.
	/// </summary>
	struct TextureSrc {
		~TextureSrc(); // Destructor to free raw pixel-data (temporary solution).

		unsigned char* data;
		int width;
		int height;
		int channels;
	};

	/// <summary>
	/// Reads an image file from disk and returns every raw-data needed to load it in a GPU texture.
	/// </summary>
	/// <param name="path">The file-path to the image source (can be .png or .jpg).</param>
	/// <returns>A TextureSrc object, containing raw pixels and metadata. </returns>
	TextureSrc getTextureSrcFromFile(const std::string& path);

	/// <summary>
	/// Texture object, used to create and hold OpenGL textures from raw pixel-data.
	/// <para> WARNING : If you manually fill the TextureSrc struct, make sure the pixel-data is in UNCOMPRESSED RGBA byte format. </para>
	/// </summary>
	class Texture : public Object, IBindable {
	public:
		Texture(const TextureSrc& src);
		~Texture();

		void bind() const override;
		void unbind() const override;
	};
}