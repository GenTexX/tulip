#include "iconProvider.h"

namespace tulip {

	IconProvider* IconProvider::s_instance = nullptr;

	IconProvider* IconProvider::get() {
		if (s_instance == nullptr)
			s_instance = new IconProvider();
		return s_instance;
	}

	IconProvider::~IconProvider() {
	}

	Ref<Texture> IconProvider::getIcon(ContentBrowserFileType type) {
		switch (type)
		{
		case tulip::FOLDER:
			return m_folder_icon;
		case tulip::IMAGE:
			return  m_unknown_file_icon;
		case tulip::SCRIPT:
			return  m_unknown_file_icon;
		case tulip::MODEL:
			return  m_unknown_file_icon;
		default:
			return  m_unknown_file_icon;
		}
		return m_unknown_file_icon;
	}

	IconProvider::IconProvider() {
		
		TextureFormat::RGBA8;

		TextureSpecification spec{};
		spec.path = "./assets/icons/unknown_file.png";
		spec.texture_format = TextureFormat::RGBA8;
		spec.texture_min_mag_filter = TextureMinMagFilter::NEAREST;
		spec.texture_type = TextureType::TEXTURE_2D;
		spec.flip = false;


		m_unknown_file_icon = Texture::create(spec);

		spec.path = "./assets/icons/folder.png";
		spec.texture_format = TextureFormat::RGBA8;
		spec.texture_min_mag_filter = TextureMinMagFilter::NEAREST;
		spec.texture_type = TextureType::TEXTURE_2D;
		spec.flip = false;


		m_folder_icon = Texture::create(spec);


	}

}