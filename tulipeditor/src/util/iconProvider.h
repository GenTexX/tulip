#pragma once

#include <texture\texture.h>
#include <core\core.h>

#include "contentbrowser\contentBrowser.h"

namespace tulip {

	class IconProvider {
	public:
		static IconProvider* get();
		~IconProvider();

		Ref<Texture> getIcon(ContentBrowserFileType type);

	private:
		static IconProvider* s_instance;

		IconProvider();

		Ref<Texture> m_unknown_file_icon;
		Ref<Texture> m_folder_icon;
		Ref<Texture> m_image_file_icon;
		Ref<Texture> m_script_file_icon;
		Ref<Texture> m_model_file_icon;


	};

}