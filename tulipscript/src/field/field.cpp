#include "field.h"
#include "../type/type.h"

#include <mono/metadata/attrdefs.h>

#include <iostream>

namespace tulip {

	TulipScriptField::TulipScriptField(MonoClassField* field) {
		m_field = field;
		m_name = mono_field_get_name(field);
		m_accessibility = 0;

		uint32_t access_flag = mono_field_get_flags(field) & MONO_FIELD_ATTR_FIELD_ACCESS_MASK;
		switch (access_flag)
		{
		case MONO_FIELD_ATTR_PRIVATE:
			m_accessibility |= (uint8_t)Accessibility::PRIVATE;
			break;
		case MONO_FIELD_ATTR_FAM_AND_ASSEM:
			m_accessibility |= (uint8_t)Accessibility::PROTECTED | (uint8_t)Accessibility::INTERNAL;
			break;
		case MONO_FIELD_ATTR_ASSEMBLY:
			m_accessibility |= (uint8_t)Accessibility::INTERNAL;
			break;
		case MONO_FIELD_ATTR_FAMILY:
			m_accessibility |= (uint8_t)Accessibility::PROTECTED;
			break;
		case MONO_FIELD_ATTR_FAM_OR_ASSEM:
			m_accessibility |= (uint8_t)Accessibility::PROTECTED | (uint8_t)Accessibility::PRIVATE;
			break;
		case MONO_FIELD_ATTR_PUBLIC:
			m_accessibility |= (uint8_t)Accessibility::PUBLIC;
			break;
		}

		MonoType* mono_type = mono_field_get_type(m_field);
		m_type = getTypeFromMonoType(mono_type);

	}

	TulipScriptField::~TulipScriptField() {
		
	}

}