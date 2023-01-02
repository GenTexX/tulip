#include "object.h"
#include <iostream>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/attrdefs.h>


namespace tulip {

	TulipScriptObject::TulipScriptObject(MonoAssembly* assembly, MonoDomain* app_domain, MonoClass* mono_class)
		: m_field_count(0), m_property_count(0), m_method_count(0), m_fields(nullptr), m_properties(nullptr), m_methods(nullptr) {
		m_object = mono_object_new(app_domain, mono_class);
		if (m_object == nullptr) return;

		//CONSTRUCT (calls the default constructor)
		mono_runtime_object_init(m_object);

		//FIELDS
		{
			auto num_fields = mono_class_num_fields(mono_class);
			if (num_fields > 0) {
				void* iter = nullptr;
				MonoClassField* field;
				while ((field = mono_class_get_fields(mono_class, &iter))) {
					auto field_flags = mono_field_get_flags(field);

					//if not static
					if (!(field_flags & MONO_FIELD_ATTR_STATIC)) {
						m_field_count++;
					}
				}
				if (m_field_count > 0) {
					m_fields = new TulipScriptField[m_field_count];

					size_t field_index = 0;
					iter = nullptr;
					while ((field = mono_class_get_fields(mono_class, &iter))) {
						auto field_flags = mono_field_get_flags(field);
						//if not static
						if (!(field_flags & MONO_FIELD_ATTR_STATIC) && field_index < m_field_count) {
							m_fields[field_index++] = TulipScriptField(field);
						}
					}
				}
			}
		}

		//PROPERTIES
		{
			auto num_props = mono_class_num_properties(mono_class);
			if (num_props > 0) {
				void* iter = nullptr;
				MonoProperty* prop;
				while ((prop = mono_class_get_properties(mono_class, &iter))) {
					auto prop_flags = mono_property_get_flags(prop);
					bool static_get = (mono_method_get_flags(mono_property_get_get_method(prop), nullptr) & MONO_METHOD_ATTR_STATIC);
					bool static_set = (mono_method_get_flags(mono_property_get_set_method(prop), nullptr) & MONO_METHOD_ATTR_STATIC);
					if (!static_get && !static_set) {
						m_property_count++;
					}
				}

				if (m_property_count > 0) {
					m_properties = new MonoProperty*[m_property_count];

					size_t prop_index = 0;
					iter = nullptr;
					while ((prop = mono_class_get_properties(mono_class, &iter))) {
						auto prop_flags = mono_property_get_flags(prop);
						bool static_get = (mono_method_get_flags(mono_property_get_get_method(prop), nullptr) & MONO_METHOD_ATTR_STATIC);
						bool static_set = (mono_method_get_flags(mono_property_get_set_method(prop), nullptr) & MONO_METHOD_ATTR_STATIC);
						if (!static_get && !static_set) {
							m_properties[prop_index] = prop;
						}
					}
				}
			}
		}
		//METHODS
		{
			auto num_methods = mono_class_num_properties(mono_class);
			if (num_methods > 0) {
				void* iter = nullptr;
				MonoMethod* method;
				while ((method = mono_class_get_methods(mono_class, &iter))) 
					if (!(mono_method_get_flags(method, nullptr) & MONO_METHOD_ATTR_STATIC)) m_method_count++;
				
				if (m_method_count) {
					m_methods = new MonoMethod*[m_method_count];

					size_t method_index = 0;
					iter = nullptr;
					while ((method = mono_class_get_methods(mono_class, &iter))) 
						if (!(mono_method_get_flags(method, nullptr) & MONO_METHOD_ATTR_STATIC) && method_index < m_method_count) {	m_methods[method_index++] = method; }
				}
			}
		}

	}

	TulipScriptObject::~TulipScriptObject() {
		delete[] m_fields;
		delete[] m_properties;
		delete[] m_methods;
	}

	void TulipScriptObject::call(const char* method_name) {
		float success;
		for (size_t i = 0; i < m_method_count; i++) {
			if (strcmp(method_name, mono_method_get_name(m_methods[i])) == 0) {
				mono_runtime_invoke(m_methods[i], m_object, nullptr, nullptr); //FIXXME: add parameters and exception handling
				success = true;
			}
		}
	}

}