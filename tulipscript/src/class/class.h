#pragma once
#include "../field/field.h"
#include "../object/object.h"

#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>

#include <cstdarg>

#include <memory>

namespace tulip {

	class TulipScriptClass {
	public:
		TulipScriptClass(MonoAssembly* assembly, const char* name_space, const char* class_name);
		~TulipScriptClass();

		std::shared_ptr<TulipScriptObject> create();

	private:
		MonoAssembly* m_assembly;
		char* m_name_space;
		char* m_name;
		MonoClass* m_class;

		//fields
		uint32_t m_field_count;
		TulipScriptField* m_fields;

		//properties
		uint32_t m_property_count;
		MonoProperty** m_properties;

		//methods
		uint32_t m_method_count;
		MonoMethod** m_methods;
	}; 

}