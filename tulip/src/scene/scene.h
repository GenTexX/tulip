#pragma once
#include <core/core.h>
#include <scene/component/components.h>
#include <serialization/customSerialization.h>

#include <entt/entt.hpp>
#include <cereal/access.hpp>
#include <cereal/cereal.hpp>

#include <string>
#include <vector>

namespace tulip {

	class Entity;

	using Registry = entt::registry;

	class Scene {
	public:
		Scene();
		~Scene();

		Entity createEntity(const std::string& tag = "Unnamed Entity");
		void removeEntity(Entity entity);

		void editorUpdate(Entity selected);
		void update();

		void activeCamera(Entity entity);
		Entity activeCamera();

		using EntityIterateFunction = std::function<void(Entity)>;
		void forEachEntity(EntityIterateFunction func) const {
			m_registry.each([&](auto handle) {
				
				Entity entity(handle, this);
				func(entity);
				
				});
		}

	private:
		Registry  m_registry;

		entt::entity m_active_camera;

		friend class Entity;

		friend class cereal::access;
		template<class Archive>
		void save(Archive& archive) const {
			archive(cereal::make_nvp("name", std::string("untitled")));
			std::vector<EntityComponentsHelper> entities;
			this->forEachEntity([&](Entity entity) {
				entities.insert(entities.begin(), EntityComponentsHelper::make(entity));
				});
			archive(cereal::make_nvp("entities", entities));
			archive(cereal::make_nvp("activecam", (ENTT_ID_TYPE)m_active_camera));
		}

		template<class Archive>
		void load(Archive& archive) {
			//archive(cereal::make_nvp("name", std::string("untitled")));
			std::vector<EntityComponentsHelper> entities;
			archive(cereal::make_nvp("entities", entities));
			for (auto entity : entities) {
				entt::entity e = m_registry.create();
				if (entity.use_tag_c) m_registry.emplace<TagComponent>(e, entity.tag_c);
				if (entity.use_tra_c) m_registry.emplace<TransformComponent>(e, entity.tra_c);
				if (entity.use_spr_c) m_registry.emplace<SpriteRendererComponent>(e, entity.spr_c);
				if (entity.use_cam_c) { m_registry.emplace<CameraComponent>(e, entity.cam_c); m_active_camera = e; }
			}
			//archive(cereal::make_nvp("activecam", (ENTT_ID_TYPE)m_active_camera)); //change, so that uuid is saved
		}


	};

}