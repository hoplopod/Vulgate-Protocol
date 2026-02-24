#include "pch.h"

#include "spine-sfml.h"

#ifndef SPINE_MESH_VERTEX_COUNT_MAX
#define SPINE_MESH_VERTEX_COUNT_MAX 1000
#endif

using namespace sf;
using namespace spine;

sf::BlendMode blendModes[] = {
		sf::BlendMode(sf::BlendMode::SrcAlpha, sf::BlendMode::OneMinusSrcAlpha),
		sf::BlendMode(sf::BlendMode::SrcAlpha, sf::BlendMode::One),
		sf::BlendMode(sf::BlendMode::DstColor, sf::BlendMode::OneMinusSrcAlpha),
		sf::BlendMode(sf::BlendMode::One, sf::BlendMode::OneMinusSrcColor)};

sf::BlendMode blendModesPma[] = {
		sf::BlendMode(sf::BlendMode::One, sf::BlendMode::OneMinusSrcAlpha),
		sf::BlendMode(sf::BlendMode::One, sf::BlendMode::One),
		sf::BlendMode(sf::BlendMode::DstColor, sf::BlendMode::OneMinusSrcAlpha),
		sf::BlendMode(sf::BlendMode::One, sf::BlendMode::OneMinusSrcColor),
};

SkeletonRenderer *skeletonRenderer = nullptr;

SkeletonDrawable::SkeletonDrawable(SkeletonData *skeletonData, AnimationStateData *stateData) : timeScale(1),
																								usePremultipliedAlpha(false),
																								vertexArray(new VertexArray(Triangles, skeletonData->getBones().size() * 4)) {
	Bone::setYDown(true);
	skeleton = new (__FILE__, __LINE__) Skeleton(skeletonData);
	ownsAnimationStateData = stateData == 0;
	if (ownsAnimationStateData) stateData = new (__FILE__, __LINE__) AnimationStateData(skeletonData);
	state = new (__FILE__, __LINE__) AnimationState(stateData);
}

SkeletonDrawable::~SkeletonDrawable() {
	delete vertexArray;
	if (ownsAnimationStateData) delete state->getData();
	delete state;
	delete skeleton;
}

void SkeletonDrawable::update(float deltaTime, Physics physics) {
	state->update(deltaTime * timeScale);
	state->apply(*skeleton);
	skeleton->update(deltaTime * timeScale);
	skeleton->updateWorldTransform(physics);
}

inline void toSFMLColor(uint32_t color, sf::Color *sfmlColor) {
	sfmlColor->a = (color >> 24) & 0xFF;
	sfmlColor->r = (color >> 16) & 0xFF;
	sfmlColor->g = (color >> 8) & 0xFF;
	sfmlColor->b = color & 0xFF;
}

void SkeletonDrawable::draw(RenderTarget &target, RenderStates states) const {
	states.texture = NULL;
	vertexArray->clear();

	if (!skeletonRenderer) skeletonRenderer = new (__FILE__, __LINE__) SkeletonRenderer();
	RenderCommand *command = skeletonRenderer->render(*skeleton);
	while (command) {
		Vertex vertex;
		float *positions = command->positions;
		float *uvs = command->uvs;
		uint32_t *colors = command->colors;
		uint16_t *indices = command->indices;
		Texture *texture = (Texture *) command->texture;
		Vector2u size = texture->getSize();
		for (int i = 0, n = command->numIndices; i < n; ++i) {
			int ii = indices[i];
			int index = ii << 1;
			vertex.position.x = positions[index];
			vertex.position.y = positions[index + 1];
			vertex.texCoords.x = uvs[index] * size.x;
			vertex.texCoords.y = uvs[index + 1] * size.y;
			toSFMLColor(colors[ii], &vertex.color);
			vertexArray->append(vertex);
		}
		BlendMode blendMode = command->blendMode;
		states.blendMode = usePremultipliedAlpha ? blendModesPma[blendMode] : blendModes[blendMode];
		states.texture = texture;
		target.draw(*vertexArray, states);
		vertexArray->clear();

		command = command->next;
	}
}

class NullTextureLoader : public TextureLoader {
public:
	virtual void load(AtlasPage &, const String &) {}

	virtual void unload(void *) {}
};

class NullAttachmentLoader : public AttachmentLoader {
	virtual RegionAttachment *newRegionAttachment(Skin &, const String &name, const String &, Sequence *) {
		return new (__FILE__, __LINE__) RegionAttachment(name);
	}

	virtual MeshAttachment *newMeshAttachment(Skin &, const String &name, const String &, Sequence *) {
		return new (__FILE__, __LINE__) MeshAttachment(name);
	}

	virtual BoundingBoxAttachment *newBoundingBoxAttachment(Skin &, const String &name) {
		return new (__FILE__, __LINE__) BoundingBoxAttachment(name);
	}

	virtual PathAttachment *newPathAttachment(Skin &, const String &name) {
		return new (__FILE__, __LINE__) PathAttachment(name);
	}

	virtual PointAttachment *newPointAttachment(Skin &, const String &name) {
		return new (__FILE__, __LINE__) PointAttachment(name);
	}

	virtual ClippingAttachment *newClippingAttachment(Skin &, const String &name) {
		return new (__FILE__, __LINE__) ClippingAttachment(name);
	}

	virtual void configureAttachment(Attachment *) {
	}
};

void SFMLTextureLoader::load(AtlasPage &page, const String &path) {
	Texture *texture = new Texture();
	if (!texture->loadFromFile(path.buffer())) return;

	if (page.magFilter == TextureFilter_Linear) texture->setSmooth(true);
	if (page.uWrap == TextureWrap_Repeat && page.vWrap == TextureWrap_Repeat) texture->setRepeated(true);

	page.texture = texture;
	Vector2u size = texture->getSize();
	page.width = size.x;
	page.height = size.y;
}

void SFMLTextureLoader::unload(void *texture) {
	delete (Texture *) texture;
}

SpineExtension *spine::getDefaultExtension() {
	return new DefaultSpineExtension();
}
