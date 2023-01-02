#include "engine.h"
#include "class/class.h"
#include "object/object.h"

#include <fstream>
#include <iostream>

#define MONO_RUNTIME_NAME "mono_runtime"

namespace tulip {

	static char* readBytes(const std::string& filepath, uint32_t* outSize) {
		std::ifstream stream(filepath, std::ios::binary | std::ios::ate);

		if (!stream) {
			return nullptr;
		}

		std::streampos end = stream.tellg();
		stream.seekg(0, std::ios::beg);
		uint32_t size = static_cast<uint32_t>(end - stream.tellg());

		if (size == 0)
		{
			return nullptr;
		}

		char* buffer = new char[size];
		stream.read((char*)buffer, size);
		stream.close();

		*outSize = size;
		return buffer;

	}

	static void alterInstance(MonoObject* mono_object) {
		MonoClass* mono_class = mono_object_get_class(mono_object);
		MonoClassField* name = mono_class_get_field_from_name(mono_class, "");
	}

	static MonoClass* getMonoClassFromAssembly(MonoAssembly* assembly, const char* namespaceName, const char* className) {
		MonoImage* image = mono_assembly_get_image(assembly);
		MonoClass* mono_class = mono_class_from_name(image, namespaceName, className);

		if (mono_class == nullptr) {
			return nullptr;
		}

		return mono_class;

	}

	static void callMethod(MonoObject* mono_object) {
		MonoClass* object_class = mono_object_get_class(mono_object);
		MonoMethod* method = mono_class_get_method_from_name(object_class, "printFloat", 0);

		if (method == nullptr) {
			return;
		}

		MonoObject* exception = nullptr;
		mono_runtime_invoke(method, mono_object, nullptr, &exception);


	}

	struct TulipMonoData {
		MonoDomain* root_domain = nullptr;
		MonoDomain* app_domain;
	};

	static TulipMonoData mono_data = {};

	static MonoAssembly* loadCSharpAssambly(const std::string& assemblyPath) {
		uint32_t fileSize;
		char* fileData = readBytes(assemblyPath, &fileSize);
		  
		MonoImageOpenStatus status;
		MonoImage* image = mono_image_open_from_data_full(fileData, fileSize, 1, &status, 0);

		if (status != MONO_IMAGE_OK) {
			const char* errorMsg = mono_image_strerror(status);
			std::cout << errorMsg << std::endl;
			return nullptr;
		}

		MonoAssembly* assembly = mono_assembly_load_from_full(image, assemblyPath.c_str(), &status, 0);
		mono_image_close(image);

		delete[] fileData;

		return assembly;
	}

	bool ScriptEngine::init() {
		mono_set_assemblies_path("../vendor/mono/lib");

		mono_data.root_domain = mono_jit_init(MONO_RUNTIME_NAME);
		if (mono_data.root_domain == nullptr) {
			std::cout << "ERROR: Initializing mono failed!" << std::endl;
			return false;
		}

		char app_name[] = "mono_app";

		mono_data.app_domain = mono_domain_create_appdomain(app_name, nullptr);
		mono_domain_set(mono_data.app_domain, true);

		auto assembly = loadCSharpAssambly("../tulipscript/resources/scripts/tulipscriptcore.dll");
		MonoClass* myClass = getMonoClassFromAssembly(assembly, "tulip", "CSharpTest");
		TulipScriptClass my_class = TulipScriptClass(assembly, "tulip", "CSharpTest");

		auto obj = my_class.create();

		obj->call("printFloattt");

		return true;
	}

	MonoDomain* ScriptEngine::getAppDomain() {
		return mono_data.app_domain;
	}

	void ScriptEngine::printAssemblyTypes(MonoAssembly* assembly) {
		MonoImage* image = mono_assembly_get_image(assembly);
		const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
		int32_t numTypes = mono_table_info_get_rows(typeDefinitionsTable);

		for (int i = 0; i < numTypes; i++) {
			uint32_t cols[MONO_TYPEDEF_SIZE];
			mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);
			const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
			const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);

			std::cout << "Namespace: " << nameSpace << "\nName: " << name << std::endl;

		}

	}

}
