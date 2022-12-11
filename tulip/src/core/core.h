#pragma once
#include <memory>
#include <assert.h>

#ifdef TULIP_DEBUG
#define TULIP_ASSERT(x, ...) { if(!(x)) { assert(__VA_ARGS__); } }
#else
#define TULIP_ASSERT(x, ...)
#endif
namespace tulip {

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> createRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using UniqueRef = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr UniqueRef<T> createUniqueRef(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

}