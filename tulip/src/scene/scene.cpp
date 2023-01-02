#include "tulippch.h"
#include "scene.h"

#include <graphicsapi\gAPI.h>

#include <scene\entity\entity.h>

namespace tulip {

	Scene::Scene() {

	}

	Scene::~Scene() {

	}

	Entity Scene::createEntity(const std::string& tag) {
		EntityHandle handle = m_registry.create();

		Entity entity(handle, this);
		entity.addComponent<TagComponent>(TagComponent{ tag });
		entity.addComponent<TransformComponent>(TransformComponent{});

		return entity;
	}

	void Scene::removeEntity(Entity entity) {
		m_registry.destroy(entity.m_handle);
	}


	void Scene::update() {}
	
	void Scene::editorUpdate(Entity selected) {
		if (m_active_camera != entt::null) {
			if (m_registry.any_of<CameraComponent>(m_active_camera)) {
				auto camera_camera_component = m_registry.get<CameraComponent>(m_active_camera);
				auto camera_transform_component = m_registry.get<TransformComponent>(m_active_camera);

				auto group = m_registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

				GraphicsAPI::beginScene(glm::inverse(camera_transform_component.getTransform()), camera_camera_component);

				for (auto entity : group) {
					auto [transform_component, sprite_renderer_component] = group.get<TransformComponent, SpriteRendererComponent>(entity);
					if (sprite_renderer_component.m_sprite) {
						GraphicsAPI::drawEditorQuad(transform_component, sprite_renderer_component.color, sprite_renderer_component.m_sprite->rendererID(), entity == selected.m_handle);
					} else
						GraphicsAPI::drawEditorQuad(transform_component, sprite_renderer_component.color, entity == selected.m_handle);
				}

				GraphicsAPI::endScene();
			}
		}
	}

	void Scene::activeCamera(Entity entity) { m_active_camera = entity.m_handle; }

	Entity Scene::activeCamera() { return Entity(m_active_camera, this); }

}