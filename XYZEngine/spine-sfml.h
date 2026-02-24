
#ifndef SPINE_SFML_H_
#define SPINE_SFML_H_

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "spine/spine.h"

namespace spine {

	class SkeletonDrawable : public sf::Drawable {
	public:
		Skeleton *skeleton;
		AnimationState *state;
		float timeScale;

		SkeletonDrawable(SkeletonData *skeleton, AnimationStateData *stateData = 0);

		~SkeletonDrawable();

		void update(float deltaTime, Physics physics = Physics_Update);

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		void setUsePremultipliedAlpha(bool usePMA) { usePremultipliedAlpha = usePMA; };

		bool getUsePremultipliedAlpha() { return usePremultipliedAlpha; };

	private:
		bool ownsAnimationStateData;
		mutable bool usePremultipliedAlpha;
		sf::VertexArray *vertexArray;
	};

	class SFMLTextureLoader : public TextureLoader {
	public:

		virtual void load(AtlasPage &page, const String &path);

		virtual void unload(void *texture);

		String toString() const;
	};

	class NullTextureLoader : public TextureLoader {
	public:
		virtual void load(AtlasPage&, const String&) {}

		virtual void unload(void*) {}
	};

	class NullAttachmentLoader : public AttachmentLoader {
		virtual RegionAttachment* newRegionAttachment(Skin&, const String& name, const String&, Sequence*) {
			return new (__FILE__, __LINE__) RegionAttachment(name);
		}

		virtual MeshAttachment* newMeshAttachment(Skin&, const String& name, const String&, Sequence*) {
			return new (__FILE__, __LINE__) MeshAttachment(name);
		}

		virtual BoundingBoxAttachment* newBoundingBoxAttachment(Skin&, const String& name) {
			return new (__FILE__, __LINE__) BoundingBoxAttachment(name);
		}

		virtual PathAttachment* newPathAttachment(Skin&, const String& name) {
			return new (__FILE__, __LINE__) PathAttachment(name);
		}

		virtual PointAttachment* newPointAttachment(Skin&, const String& name) {
			return new (__FILE__, __LINE__) PointAttachment(name);
		}

		virtual ClippingAttachment* newClippingAttachment(Skin&, const String& name) {
			return new (__FILE__, __LINE__) ClippingAttachment(name);
		}

		virtual void configureAttachment(Attachment*) {
		}
	};

} /* namespace spine */
#endif /* SPINE_SFML_H_ */
