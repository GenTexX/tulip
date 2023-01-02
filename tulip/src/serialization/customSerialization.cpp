#include "tulippch.h"
#include "customSerialization.h"
#include <scene/entity/entity.h>

namespace tulip {
	EntityComponentsHelper tulip::EntityComponentsHelper::make(Entity entity) {
		EntityComponentsHelper helper;
		helper.handle = entity.m_handle;
		helper.uuid = "not_implemented_yet";

		auto& tag_component = entity.getComponent<TagComponent>();
		helper.tag_c = tag_component;
		helper.use_tag_c = true;

		auto& transform_component = entity.getComponent<TransformComponent>();
		helper.tra_c = transform_component;
		helper.use_tra_c = true;

		if (entity.hasComponent<SpriteRendererComponent>()) {
			auto& sprite_renderer_component = entity.getComponent<SpriteRendererComponent>();
			helper.spr_c = sprite_renderer_component;
			helper.use_spr_c = true;
		}

		if (entity.hasComponent<CameraComponent>()) {
			auto& camera_component = entity.getComponent<CameraComponent>();
			helper.cam_c = camera_component;
			helper.use_cam_c = true;
		}

		return helper;
	}

}
