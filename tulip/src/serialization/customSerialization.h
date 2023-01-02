#pragma once
#include <scene/component/components.h>

#include <glm.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <entt/entt.hpp>

#define UUID_ID "uuid"

#define TAG_COMPONENT_ID "tag_c"
#define TRANSFORM_COMPONENT_ID "tra_c"
#define SPRITE_RENDERER_COMPONENT_ID "spr_c"
#define CAMERA_COMPONENT_ID "cam_c"

#define TAG_ID "tag"
#define TRANSLATION_ID "trn"
#define ROTATION_ID "rot"
#define SCALE_ID "sca"
#define COLOR_ID "col"
#define SPRITE_ID "spr"
#define CAMERA_ID "cam"

#define TEXTURE_PATH_ID "pth"
#define TEXTURE_FILTER_ID "flt"
#define TEXTURE_FORMAT_ID "fmt"
#define TEXTURE_TYPE_ID "typ"
namespace glm {

	template<class Archive> void serialize(Archive& archive, glm::vec2& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y)); }
	template<class Archive> void serialize(Archive& archive, glm::vec3& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z)); }
	template<class Archive> void serialize(Archive& archive, glm::vec4& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z), CEREAL_NVP(v.w)); }
	template<class Archive> void serialize(Archive& archive, glm::ivec2& v) {
		archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y));
	}
	template<class Archive> void serialize(Archive& archive, glm::ivec3& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z)); }
	template<class Archive> void serialize(Archive& archive, glm::ivec4& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z), CEREAL_NVP(v.w)); }
	template<class Archive> void serialize(Archive& archive, glm::uvec2& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y)); }
	template<class Archive> void serialize(Archive& archive, glm::uvec3& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z)); }
	template<class Archive> void serialize(Archive& archive, glm::uvec4& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z), CEREAL_NVP(v.w)); }
	template<class Archive> void serialize(Archive& archive, glm::dvec2& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y)); }
	template<class Archive> void serialize(Archive& archive, glm::dvec3& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z)); }
	template<class Archive> void serialize(Archive& archive, glm::dvec4& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z), CEREAL_NVP(v.w)); }

	// glm matrices serialization
	template<class Archive> void serialize(Archive& archive, glm::mat2& m) { archive(CEREAL_NVP(m[0]), CEREAL_NVP(m[1])); }
	template<class Archive> void serialize(Archive& archive, glm::dmat2& m) { archive(CEREAL_NVP(m[0]), CEREAL_NVP(m[1])); }
	template<class Archive> void serialize(Archive& archive, glm::mat3& m) { archive(CEREAL_NVP(m[0]), CEREAL_NVP(m[1]), CEREAL_NVP(m[2])); }
	template<class Archive> void serialize(Archive& archive, glm::mat4& m) { archive(CEREAL_NVP(m[0]), CEREAL_NVP(m[1]), CEREAL_NVP(m[2]), CEREAL_NVP(m[3])); }
	template<class Archive> void serialize(Archive& archive, glm::dmat4& m) { archive(CEREAL_NVP(m[0]), CEREAL_NVP(m[1]), CEREAL_NVP(m[2]), CEREAL_NVP(m[3])); }

}

CEREAL_REGISTER_TYPE_WITH_NAME(tulip::OrthoCamera, "ortho_cam");

namespace tulip {

	class Entity;

	struct EntityComponentsHelper {
		entt::entity handle;
		std::string uuid;
		bool use_tag_c = false;
		TagComponent tag_c;
		bool use_tra_c = false;
		TransformComponent tra_c;
		bool use_spr_c = false;
		SpriteRendererComponent spr_c;
		bool use_cam_c = false;
		CameraComponent cam_c;

		static EntityComponentsHelper make(Entity entity);
	};


	template<class Archive> void save(Archive& archive, const EntityComponentsHelper& helper) {
		archive(cereal::make_nvp(UUID_ID, helper.uuid));
		if (helper.use_tag_c) archive(cereal::make_nvp(TAG_COMPONENT_ID, helper.tag_c));
		if (helper.use_tra_c) archive(cereal::make_nvp(TRANSFORM_COMPONENT_ID, helper.tra_c));
		if (helper.use_spr_c) archive(cereal::make_nvp(SPRITE_RENDERER_COMPONENT_ID, helper.spr_c));
		if (helper.use_cam_c) archive(cereal::make_nvp(CAMERA_COMPONENT_ID, helper.cam_c));
	}

	template<class Archive> void load(Archive& archive, EntityComponentsHelper& helper) {
		helper.use_tag_c = false;
		helper.use_tra_c = false;
		helper.use_spr_c = false;
		helper.use_cam_c = false;
		try {
			archive(cereal::make_nvp(UUID_ID, helper.uuid));
		} catch (const cereal::Exception&) {

		}
		try {
			archive(cereal::make_nvp(TAG_COMPONENT_ID, helper.tag_c));
			helper.use_tag_c = true;
		} catch (const cereal::Exception&) {

		}
		try {
			archive(cereal::make_nvp(TRANSFORM_COMPONENT_ID, helper.tra_c));
			helper.use_tra_c = true;
		} catch (const cereal::Exception&) {

		}
		try {
			archive(cereal::make_nvp(SPRITE_RENDERER_COMPONENT_ID, helper.spr_c));
			helper.use_spr_c = true;
		} catch (const cereal::Exception&) {

		}
		try {
			archive(cereal::make_nvp(CAMERA_COMPONENT_ID, helper.cam_c));
			helper.use_cam_c = true;
		} catch (const cereal::Exception&) {

		}

	}

	template<class Archive> void serialize(Archive& archive, TagComponent& tag) { archive(cereal::make_nvp(TAG_ID, tag.tag)); }
	template<class Archive> void serialize(Archive& archive, TransformComponent& tf) {
		archive(cereal::make_nvp(TRANSLATION_ID, tf.translation), cereal::make_nvp(ROTATION_ID, tf.rotation), cereal::make_nvp(SCALE_ID, tf.scale));
	}
	template<class Archive> void save(Archive& archive, const SpriteRendererComponent& sr) {
		archive(cereal::make_nvp(COLOR_ID, sr.color));
		if (sr.m_sprite) {
			archive(cereal::make_nvp(SPRITE_ID, sr.m_sprite->getSpec()));
		}
	}

	template<class Archive> void load(Archive& archive, SpriteRendererComponent& sr) {
		archive(cereal::make_nvp(COLOR_ID, sr.color));
		try {
			TextureSpecification spec = {};
			archive(cereal::make_nvp(SPRITE_ID, spec));
			sr.m_sprite = Texture::create(spec);
		} catch (const cereal::Exception&) {

		}
	}

	template<class Archive> void serialize(Archive& archive, TextureSpecification& spec) {
		archive(cereal::make_nvp(TEXTURE_PATH_ID, spec.path), cereal::make_nvp(TEXTURE_FILTER_ID, spec.texture_min_mag_filter), cereal::make_nvp(TEXTURE_FORMAT_ID, spec.texture_format), cereal::make_nvp(TEXTURE_TYPE_ID, spec.texture_type));
	}

	template<class Archive> void serialize(Archive& archive, CameraComponent& cam) {
		archive(cereal::make_nvp(CAMERA_ID, cam.m_camera));
	}

}