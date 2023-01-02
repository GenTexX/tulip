#include "type.h"

namespace tulip {

    TulipScriptType getTypeFromMonoType(MonoType* type) {

		auto mono_type_enum = mono_type_get_type(type);

		std::cout << mono_type_get_name(type) << ": " << mono_type_enum << std::endl;
		switch (mono_type_enum)
		{
		case MONO_TYPE_END:
			break;
		case MONO_TYPE_VOID:
			return TulipScriptType::TS_VOID;
		case MONO_TYPE_BOOLEAN:
			return TulipScriptType::TS_BOOL;
		case MONO_TYPE_CHAR:
			return TulipScriptType::TS_CHAR;
		case MONO_TYPE_I1:
			return TulipScriptType::TS_BYTE;
		case MONO_TYPE_U1:
			return TulipScriptType::TS_UBYTE;
		case MONO_TYPE_I2:
			return TulipScriptType::TS_SHORT;
		case MONO_TYPE_U2:
			return TulipScriptType::TS_USHORT;
		case MONO_TYPE_I4:
			return TulipScriptType::TS_INT;
		case MONO_TYPE_U4:
			return TulipScriptType::TS_UINT;
		case MONO_TYPE_I8:
			return TulipScriptType::TS_LONG;
		case MONO_TYPE_U8:
			return TulipScriptType::TS_ULONG;
		case MONO_TYPE_R4:
			return TulipScriptType::TS_FLOAT;
		case MONO_TYPE_R8:
			return TulipScriptType::TS_DOUBLE;
		case MONO_TYPE_STRING:
			return TulipScriptType::TS_STRING;
		case MONO_TYPE_PTR:
			return TulipScriptType::TS_PTR;
		case MONO_TYPE_BYREF:
			return TulipScriptType::TS_REF;
		case MONO_TYPE_VALUETYPE:
			return TulipScriptType::TS_VALTYPE;
		case MONO_TYPE_CLASS:
			return TulipScriptType::TS_CLASS;
		case MONO_TYPE_ARRAY:
			return TulipScriptType::TS_NDIM_ARRAY;
		case MONO_TYPE_SZARRAY:
			return TulipScriptType::TS_ARRAY;
		case MONO_TYPE_VAR:
			break;
		case MONO_TYPE_GENERICINST:
			break;
		case MONO_TYPE_TYPEDBYREF:
			break;
		case MONO_TYPE_I:
			break;
		case MONO_TYPE_U:
			break;
		case MONO_TYPE_FNPTR:
			break;
		case MONO_TYPE_OBJECT:
			break;
		case MONO_TYPE_MVAR:
			break;
		default:
			std::cout << "ERROR: Type not supported!" << std::endl;
			break;
		}

		return TulipScriptType::TS_INVALID;

	}

}
