#include "class.h"
#include "../util/errors.h"

#include <iostream>
#include <cstring>

#include "../engine.h"

#include <mono/metadata/attrdefs.h>
#include <mono/metadata/reflection.h>

namespace tulip {

	TulipScriptClass::TulipScriptClass(MonoAssembly* assembly, const char* name_space, const char* class_name)
	: m_field_count(0), m_property_count(0), m_method_count(0) {
		m_assembly = assembly;
		MonoImage* image = mono_assembly_get_image(assembly);
		m_class = mono_class_from_name(image, name_space, class_name);

		if (m_class == nullptr) {
			std::cout << "error: allocating " << class_name << "failed" << std::endl;
			size_t string_length = strlen(TULIPSCRIPT_CLASS_ALLOC_ERROR) + 1;
			m_name = new char[string_length];
			strcpy_s(m_name, string_length, TULIPSCRIPT_CLASS_ALLOC_ERROR);
			return;
		}

		size_t name_space_length = strlen(name_space);
		m_name_space = new char[name_space_length + 1];
		strcpy_s(m_name_space, name_space_length + 1, name_space);

		size_t class_name_length = strlen(class_name);
		m_name = new char[class_name_length + 1];
		strcpy_s(m_name, class_name_length + 1, class_name);
		
		//FIELDS
		{
			auto num_fields = mono_class_num_fields(m_class);
			if (num_fields > 0) {
				void* iter = nullptr;
				MonoClassField* field;
				while ((field = mono_class_get_fields(m_class, &iter)))
					if (mono_field_get_flags(field) & MONO_FIELD_ATTR_STATIC) m_field_count++;	
				
				if (m_field_count > 0) {
					m_fields = new TulipScriptField[m_field_count];

					size_t field_index = 0;
					iter = nullptr;
					while ((field = mono_class_get_fields(m_class, &iter)))
						if ((mono_field_get_flags(field) & MONO_FIELD_ATTR_STATIC) && field_index < m_field_count)
							m_fields[field_index++] = TulipScriptField(field);
				}
			}
		}

		//PROPERTIES
		{
			auto num_props = mono_class_num_properties(m_class);
			if (num_props > 0) {
				void* iter = nullptr;
				MonoProperty* prop;
				while ((prop = mono_class_get_properties(m_class, &iter))) {
					auto prop_flags = mono_property_get_flags(prop);
					bool static_get = (mono_method_get_flags(mono_property_get_get_method(prop), nullptr) & MONO_METHOD_ATTR_STATIC);
					bool static_set = (mono_method_get_flags(mono_property_get_set_method(prop), nullptr) & MONO_METHOD_ATTR_STATIC);
					if (static_get && static_set) m_property_count++;
				}

				if (m_property_count > 0) {
					m_properties = new MonoProperty*[m_property_count];

					size_t prop_index = 0;
					iter = nullptr;
					while ((prop = mono_class_get_properties(m_class, &iter))) {
						auto prop_flags = mono_property_get_flags(prop);
						MonoMethod* get = mono_property_get_get_method(prop);
						bool static_get = get != nullptr ? (mono_method_get_flags(get, nullptr) & MONO_METHOD_ATTR_STATIC) : true;
						MonoMethod* set = mono_property_get_set_method(prop);
						bool static_set = set != nullptr ? (mono_method_get_flags(set, nullptr) & MONO_METHOD_ATTR_STATIC) : true;
						if (static_get && static_set) 
							m_properties[prop_index++] = prop;
						
					}
				}
			}
		}

		//METHODS
		{
			auto num_methods = mono_class_num_properties(m_class);
			if (num_methods > 0) {
				void* iter = nullptr;
				MonoMethod* method;
				while ((method = mono_class_get_methods(m_class, &iter)))
					if ((mono_method_get_flags(method, nullptr) & MONO_METHOD_ATTR_STATIC)) m_method_count++;

				if (m_method_count) {
					m_methods = new MonoMethod*[m_method_count];

					size_t method_index = 0;
					iter = nullptr;
					while ((method = mono_class_get_methods(m_class, &iter)))
						if ((mono_method_get_flags(method, nullptr) & MONO_METHOD_ATTR_STATIC) && method_index < m_method_count)
							m_methods[method_index++] = method;
				}
			}
		}

	}

	TulipScriptClass::~TulipScriptClass() {
		delete[] m_fields;
		delete[] m_properties;
		delete[] m_methods;
	}

	std::shared_ptr<TulipScriptObject> TulipScriptClass::create() {
		return std::make_shared<TulipScriptObject>(m_assembly, ScriptEngine::getAppDomain(), m_class);
	}


}