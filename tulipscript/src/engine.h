#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

namespace tulip {

	class ScriptEngine {
	public:
		static bool init();

		static MonoDomain* getAppDomain();

		static void printAssemblyTypes(MonoAssembly* assembly);

	private:
		ScriptEngine() {}
		~ScriptEngine() {}

	};

}