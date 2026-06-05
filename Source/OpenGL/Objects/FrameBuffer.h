#pragma once

#include "../Utils/Types.h"
#include "../Common/Object.h"
#include "../Common/IBindable.h"

namespace OpenGL {
	class Texture;

	class FrameBuffer : public Object, public IBindable {
	public:
		FrameBuffer();
		~FrameBuffer();

		void attachTexture(const Texture& texture, AttachmentType type = AttachmentType::COLOR);
		void detachTexture(AttachmentType type);

		void bind() const override;
		void unbind() const override;
	};
}