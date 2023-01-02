#pragma once
#include "../field/field.h"

#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>

namespace tulip {

	class TulipScriptObject {
	public:
		TulipScriptObject(MonoAssembly* assembly, MonoDomain* app_domain, MonoClass* mono_class);
		~TulipScriptObject();

		void call(const char* mothod_name);

	private:
		MonoObject* m_object;

		size_t m_field_count;
		TulipScriptField* m_fields;
		size_t m_property_count;
		MonoProperty** m_properties;
		size_t m_method_count;
		MonoMethod** m_methods;

	};

}