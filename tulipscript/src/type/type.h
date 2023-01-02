#pragma once

#include <mono/metadata/class.h>

#include <iostream>

namespace tulip {

	enum class TulipScriptType {
		TS_INVALID,
		TS_VOID,
		TS_BOOL,
		TS_CHAR, 
		TS_BYTE,	TS_UBYTE,
		TS_SHORT,	TS_USHORT,
		TS_INT,		TS_UINT,
		TS_LONG,	TS_ULONG,
		TS_FLOAT, 
		TS_DOUBLE, 
		TS_DECIMAL, 
		TS_STRING, 
		TS_CLASS,
		TS_REF,
		TS_ARRAY,	TS_NDIM_ARRAY,
		TS_VALTYPE,
		TS_PTR
	};

	TulipScriptType getTypeFromMonoType(MonoType* type);

}