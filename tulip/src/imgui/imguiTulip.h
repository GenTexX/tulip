#pragma once

#include <core\core.h>
#include <platform\platform.h>
#include <logging\logger.h>
#include <imgui\theme.h>
#include <imgui.h>

#include <unordered_map>


namespace tulip {

	

	class ImGuiTulip {
	public:
		~ImGuiTulip() {}

		static bool init(TulipWindowHandle twh);
		static void initTheme();
		static bool shutdown() { return s_instance->shutDownImpl(); }
		static void loadFont(const std::string& path, const std::string& font);
		static void pushFont(const std::string& font, uint8_t size);
		static void popFont();
		static void setDefaultFont(const std::string& font, uint8_t size);


		static bool ButtonPrimary(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::MEDIUM, COLOR_PRIMARY); }
		static bool ButtonPrimarySmall(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::SMALL, COLOR_PRIMARY); }
		static bool ButtonPrimaryLarge(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::LARGE, COLOR_PRIMARY); }
		static bool ButtonSecondary(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::MEDIUM, COLOR_SECONDARY); }
		static bool ButtonSecondarySmall(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::SMALL, COLOR_SECONDARY); }
		static bool ButtonSecondaryLarge(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::LARGE, COLOR_SECONDARY); }
		static bool ButtonLight(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::MEDIUM, COLOR_LIGHT); }
		static bool ButtonLightSmall(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::SMALL, COLOR_LIGHT); }
		static bool ButtonLightLarge(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::LARGE, COLOR_LIGHT); }
		static bool ButtonDark(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::MEDIUM, COLOR_DARK); }
		static bool ButtonDarkSmall(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::SMALL, COLOR_DARK); }
		static bool ButtonDarkLarge(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::LARGE, COLOR_DARK); }
		static bool ButtonSuccess(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::MEDIUM, COLOR_SUCCESS); }
		static bool ButtonSuccessSmall(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::SMALL, COLOR_SUCCESS); }
		static bool ButtonSuccessLarge(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::LARGE, COLOR_SUCCESS); }
		static bool ButtonDanger(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::MEDIUM, COLOR_DANGER); }
		static bool ButtonDangerSmall(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::SMALL, COLOR_DANGER); }
		static bool ButtonDangerLarge(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::LARGE, COLOR_DANGER); }
		static bool ButtonWarning(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::MEDIUM, COLOR_WARNING); }
		static bool ButtonWarningSmall(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::SMALL, COLOR_WARNING); }
		static bool ButtonWarningLarge(const std::string& label, bool centered = false, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }) { return ButtonEx(label, size_arg, centered, ElementSize::LARGE, COLOR_WARNING); }

		static bool TreeNodePrimary(void* ptr_id, const std::string& label, bool is_selected, ...) { va_list args; va_start(args, is_selected); bool is_open = TreeNodeEx(ptr_id, label, is_selected, COLOR_PRIMARY, args); va_end(args); return is_open; }
		static bool TreeNodeSecondary(void* ptr_id, const std::string& label, bool is_selected, ...) { va_list args; va_start(args, is_selected); bool is_open = TreeNodeEx(ptr_id, label, is_selected, COLOR_SECONDARY, args); va_end(args); return is_open; }
		static bool TreeNodeLight(void* ptr_id, const std::string& label, bool is_selected, ...) { va_list args; va_start(args, is_selected); bool is_open = TreeNodeEx(ptr_id, label, is_selected, COLOR_LIGHT, args); va_end(args); return is_open; }
		static bool TreeNodeDark(void* ptr_id, const std::string& label, bool is_selected, ...) { va_list args; va_start(args, is_selected); bool is_open = TreeNodeEx(ptr_id, label, is_selected, COLOR_DARK, args); va_end(args); return is_open; }
		static bool TreeNodeSuccess(void* ptr_id, const std::string& label, bool is_selected, ...) { va_list args; va_start(args, is_selected); bool is_open = TreeNodeEx(ptr_id, label, is_selected, COLOR_SUCCESS, args); va_end(args); return is_open; }
		static bool TreeNodeDanger(void* ptr_id, const std::string& label, bool is_selected, ...) { va_list args; va_start(args, is_selected); bool is_open = TreeNodeEx(ptr_id, label, is_selected, COLOR_DANGER, args); va_end(args); return is_open; }
		static bool TreeNodeWarning(void* ptr_id, const std::string& label, bool is_selected, ...) { va_list args; va_start(args, is_selected); bool is_open = TreeNodeEx(ptr_id, label, is_selected, COLOR_WARNING, args); va_end(args); return is_open; }

		static void InputText(const std::string& label, std::string *txt) { TextInputEx(label, txt); }

		static void BeginContainer(const float& padding) { BeginContainerEx(padding); }
		static void EndContainer() { EndContainerEx(); }

		static void Vector3f(const std::string& label, glm::vec3* vec, const float& reset = 0.0f) { Vector3fEx(label, vec, reset); }

	protected:
		ImGuiTulip() : m_initialized(false) {};
		bool m_initialized;
		virtual bool initImpl(TulipWindowHandle twh) = 0;
		virtual bool shutDownImpl() = 0;

	private:
		static UniqueRef<ImGuiTulip> create();
		static UniqueRef<ImGuiTulip> s_instance;

		//Font System
		static std::unordered_map<std::string, std::vector<ImFont*>> s_fonts;

		//Theme
		static ImGuiTheme s_theme;

		static bool ButtonEx(const std::string& label, const ImVec2& size_arg = ImVec2{ 0.0f, 0.0f }, bool centered = false, ElementSize element_size = ElementSize::MEDIUM, uint8_t color_index = 0);
		static bool TreeNodeEx(const void* ptr_id, const std::string& label, bool is_selected, uint8_t color_index, va_list args);
		static bool TextInputEx(const std::string& label, std::string *txt);

		static void BeginContainerEx(const float& padding);
		static void EndContainerEx();

		static void Vector3fEx(const std::string& label, glm::vec3* vec, const float& reset = 0.0f);
	};

}