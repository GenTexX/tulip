#pragma once
#include <core/core.h>
#include <scene/scene.h>
#include <scene/entity/entity.h>
#include <scene/component/components.h>

#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

#include <iostream>
#include <fstream>

namespace tulip {

	enum class SerializationFormat {
		XML = 1,
		JSON = 2,
		BINARY = 3
	};

	template<typename T>
	class Serializer {
	public:
		Serializer(const Ref<T>& ref, SerializationFormat format) : m_ref(ref), m_format(format) {}
		~Serializer() {}

		bool save(const std::string& filepath) {
			auto ofstreamflags = m_format == SerializationFormat::BINARY ? std::ios_base::binary | std::ios_base::out : std::ios_base::out;
			std::ofstream stream(filepath.c_str(), ofstreamflags);

			switch (m_format)
			{
			case tulip::SerializationFormat::XML:
			{
				cereal::XMLOutputArchive oarchive(stream);
				oarchive(cereal::make_nvp((std::string("tulip")), *m_ref));
				break;
			}
			case tulip::SerializationFormat::JSON:
			{
				cereal::JSONOutputArchive oarchive(stream);
				oarchive(cereal::make_nvp((std::string("tulip")), *m_ref));
				break;
			}
			case tulip::SerializationFormat::BINARY:
			{
				cereal::PortableBinaryOutputArchive oarchive(stream);
				oarchive(cereal::make_nvp((std::string("tulip")), *m_ref));
				break;
			}
			default:
				TULIP_CORE_ERROR("ERROR: Serialization-Format not supported!");
				return false;
			}
			return true;
		}

		bool load(const std::string& filepath) {
			auto ifstreamflags = m_format == SerializationFormat::BINARY ? std::ios_base::binary | std::ios_base::in : std::ios_base::in;
			std::ifstream stream(filepath.c_str(), ifstreamflags);

			switch (m_format)
			{
			case tulip::SerializationFormat::XML:
			{
				cereal::XMLInputArchive iarchive(stream);
				iarchive(cereal::make_nvp((std::string("tulip")), *m_ref));
				break;
			}
			case tulip::SerializationFormat::JSON:
			{
				cereal::JSONInputArchive iarchive(stream);
				iarchive(cereal::make_nvp((std::string("tulip")), *m_ref));
				break;
			}
			case tulip::SerializationFormat::BINARY:
			{
				cereal::PortableBinaryInputArchive iarchive(stream);
				iarchive(cereal::make_nvp((std::string("tulip")), *m_ref));
				break;
			}
			default:
				TULIP_CORE_ERROR("ERROR: Serialization-Format not supported!");
				return false;
			}
			return true;


		}

	private:
		Ref<T> m_ref;
		SerializationFormat m_format;

	};

}