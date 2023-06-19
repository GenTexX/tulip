#pragma once
#include <scene/scene.h>
#include <entt/entt.hpp>
#include <cereal/access.hpp>

class EntityComponentsHelper;

namespace tulip {

	using EntityHandle = entt::entity;

	class Entity {
	public:
		Entity() : m_handle(entt::null), m_scene() {}
		Entity(EntityHandle handle, Scene *scene) : m_handle(handle) { m_scene = scene; }
		Entity(EntityHandle handle, Scene const *scene) : m_handle(handle) { m_scene = const_cast<Scene*>(scene); }
		~Entity() {}

		void* id() { return (void*)(uint64_t)(uint32_t)m_handle; };

		bool operator==(const Entity& other) { return m_handle == other.m_handle; };
		bool operator!=(const Entity& other) { return m_handle != other.m_handle; };


		operator bool() { 
			return m_handle != entt::null; 
		}

		template<typename T, typename... Args>
		void addComponent(Args&&... args) {
			m_scene->m_registry.emplace<T>(m_handle, std::forward<Args>(args)...);
		}

		template<typename T>
		void removeComponent() {
			m_scene->m_registry.remove<T>(m_handle);
		}

		template<typename T, typename... Other>
		T& getComponent() const {
			return m_scene->m_registry.get<T>(m_handle);
		}

		template<typename T, typename... Other>
		bool hasComponent() const {
			return m_scene->m_registry.any_of<T, Other...>(m_handle);
		}

		void reset() {
			m_handle = entt::null;
		}

	private:
		EntityHandle m_handle;
	    Scene *m_scene; // maybe better if smart pointer (WeakRef or something)

		friend class Scene;
		friend struct EntityComponentsHelper;
		
	};


}