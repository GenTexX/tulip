#pragma once
#include <string>

#include <filesystem>

#include <core\core.h>

namespace tulip {

	enum ContentBrowserFileType {
		UNKNOWN = 0,
		FOLDER = 1,
		IMAGE = 2,
		SCRIPT = 3,
		MODEL = 4
	};

	class ContentBrowser;

	class ContentBrowserElement {

	public:
		ContentBrowserElement(ContentBrowser& browser) : m_browser(browser) {}
		~ContentBrowserElement() {}

		virtual bool render() = 0;

		ContentBrowserFileType getType() { return m_type; }
	protected:
		ContentBrowserFileType m_type;
		std::string m_name;
		ContentBrowser& m_browser;
	};

	class ContentBrowserFile : public ContentBrowserElement {
	public:
		ContentBrowserFile(ContentBrowser& browser, const std::filesystem::directory_entry& p);
		~ContentBrowserFile();

		virtual bool render() override;
	};

	class ContentBrowserDirectory : public ContentBrowserElement {
	public:
		ContentBrowserDirectory(ContentBrowser& browser, const std::filesystem::directory_entry& p);
		~ContentBrowserDirectory();

		virtual bool render() override;
	private:
		std::string m_path;

	};

	class ContentBrowser {
	public:
		ContentBrowser(const std::string&);
		~ContentBrowser();

		std::string getCurrentDir() {
			return m_current_dir;
		}

		void render();

		friend class ContentBrowserFile;
		friend class ContentBrowserDirectory;

	private:
		std::string m_current_dir;

		std::vector<Ref<ContentBrowserElement>> m_elements;



	};

}