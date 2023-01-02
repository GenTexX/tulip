#pragma once

#include "../type/type.h"
#include "../util/util.h"

#include <mono/metadata/class.h>

namespace tulip {

	class TulipScriptField {
	public:
		TulipScriptField() {}
		TulipScriptField(MonoClassField* field);
		~TulipScriptField();

	private:
		uint8_t m_accessibility;
		const char* m_name;
		MonoClassField* m_field;

		TulipScriptType m_type;
	};

}