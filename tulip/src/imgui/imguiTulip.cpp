#include "tulippch.h"
#include "imguiTulip.h"

#include <logging\logger.h>
#include <graphicsapi\opengl\imgui\imGuiOpenGL.h>

#include <glm.hpp>

#include <assert.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>

namespace tulip {

	struct InputTextCallback_UserData {
		std::string* Str;
		ImGuiInputTextCallback  ChainCallback;
		void* ChainCallbackUserData;
	};

	static int InputTextCallback(ImGuiInputTextCallbackData* data) {
		InputTextCallback_UserData* user_data = (InputTextCallback_UserData*)data->UserData;
		if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
		{
			// Resize string callback
			// If for some reason we refuse the new length (BufTextLen) and/or capacity (BufSize) we need to set them back to what we want.
			std::string* str = user_data->Str;
			IM_ASSERT(data->Buf == str->c_str());
			str->resize(data->BufTextLen);
			data->Buf = (char*)str->c_str();
		} else if (user_data->ChainCallback)
		{
			// Forward to user callback, if any
			data->UserData = user_data->ChainCallbackUserData;
			return user_data->ChainCallback(data);
		}
		return 0;
	}


	UniqueRef<ImGuiTulip> ImGuiTulip::s_instance = ImGuiTulip::create();
	std::unordered_map<std::string, std::vector<ImFont*>> ImGuiTulip::s_fonts;
	ImGuiTheme ImGuiTulip::s_theme = {};

	bool ImGuiTulip::init(TulipWindowHandle twh) {
		bool implinit = s_instance->initImpl(twh);
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.Fonts->AddFontDefault();

		initTheme();

		return implinit;
	}

	void ImGuiTulip::initTheme() {

		//COLORS
		s_theme.colors[COLOR_PRIMARY] = glm::vec4{ 0.284f, 0.573f, 0.749f, 1.0f };
		s_theme.colors[COLOR_PRIMARY_HOVER] = s_theme.colors[COLOR_PRIMARY] * 1.2f;
		s_theme.colors[COLOR_PRIMARY_ACTIVE] = s_theme.colors[COLOR_PRIMARY] * 0.8f;

		s_theme.colors[COLOR_SECONDARY] = glm::vec4{ 0.478f, 0.415f, 0.553f, 1.0f };
		s_theme.colors[COLOR_SECONDARY_HOVER] = s_theme.colors[COLOR_SECONDARY] * 1.2f;
		s_theme.colors[COLOR_SECONDARY_ACTIVE] = s_theme.colors[COLOR_SECONDARY] * 0.8f;

		s_theme.colors[COLOR_LIGHT] = glm::vec4{ 0.471f, 0.471f, 0.471f, 1.0f };
		s_theme.colors[COLOR_LIGHT_HOVER] = s_theme.colors[COLOR_LIGHT] * 1.2f;
		s_theme.colors[COLOR_LIGHT_ACTIVE] = s_theme.colors[COLOR_LIGHT] * 0.8f;

		s_theme.colors[COLOR_DARK] = glm::vec4{ 0.08f, 0.08f, 0.08f, 1.0f };
		s_theme.colors[COLOR_DARK_HOVER] = s_theme.colors[COLOR_DARK] * 1.2f;
		s_theme.colors[COLOR_DARK_ACTIVE] = s_theme.colors[COLOR_DARK] * 0.8f;

		s_theme.colors[COLOR_SUCCESS] = glm::vec4{ 0.2f, 0.404f, 0.231f, 1.0f };
		s_theme.colors[COLOR_SUCCESS_HOVER] = s_theme.colors[COLOR_SUCCESS] * 1.2f;
		s_theme.colors[COLOR_SUCCESS_ACTIVE] = s_theme.colors[COLOR_SUCCESS] * 0.8f;

		s_theme.colors[COLOR_DANGER] = glm::vec4{ 0.671f, 0.086f, 0.188f, 1.0f };
		s_theme.colors[COLOR_DANGER_HOVER] = s_theme.colors[COLOR_DANGER] * 1.2f;
		s_theme.colors[COLOR_DANGER_ACTIVE] = s_theme.colors[COLOR_DANGER] * 0.8f;

		s_theme.colors[COLOR_WARNING] = glm::vec4{ 1.0f, 0.764f, 0.121f, 1.0f };
		s_theme.colors[COLOR_WARNING_HOVER] = s_theme.colors[COLOR_WARNING] * 1.2f;
		s_theme.colors[COLOR_WARNING_ACTIVE] = s_theme.colors[COLOR_WARNING] * 0.8f;

		//BUTTON
		s_theme.button_rounding = 2.0f;

	}

	void ImGuiTulip::loadFont(const std::string& path, const std::string& font) {
		std::vector<ImFont*> fontContainer;

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		fontContainer.emplace_back(io.Fonts->AddFontFromFileTTF(path.c_str(), 16.0));
		fontContainer.emplace_back(io.Fonts->AddFontFromFileTTF(path.c_str(), 18.5f));
		fontContainer.emplace_back(io.Fonts->AddFontFromFileTTF(path.c_str(), 22.0f));

		s_fonts[font] = fontContainer;

	}

	void ImGuiTulip::pushFont(const std::string& font, uint8_t size) {
		size %= 4;
		size--;
		if (s_fonts.find(font) != s_fonts.end()) {
			ImGui::PushFont(s_fonts[font][size]);
		} else {
			TULIP_CORE_ERROR("Unkown Font {}! Did you forget to load it?", font.c_str());
			ImGui::PushFont(ImGui::GetIO().FontDefault);
		}
	}

	void ImGuiTulip::popFont() {
		ImGui::PopFont();
	}

	void ImGuiTulip::setDefaultFont(const std::string& font, uint8_t size) {
		size %= 4;
		size--;
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.FontDefault = s_fonts[font][size];
	}

	bool ImGuiTulip::ButtonEx(const std::string& label, const ImVec2& size_arg, bool centered, ElementSize element_size, uint8_t color_index) {


		ImGuiButtonFlags flags = ImGuiButtonFlags_None;

		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems) return false;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const ImGuiID id = window->GetID(label.c_str());
		const ImVec2 label_size = ImGui::CalcTextSize(label.c_str(), NULL, true);

		ImVec2 frame_padding;
		switch (element_size)
		{
		case tulip::ElementSize::SMALL:
			frame_padding = style.FramePadding * 2.0f;
			frame_padding.x *= 2.0f;
			break;
		case tulip::ElementSize::MEDIUM:
			frame_padding = style.FramePadding * 5.0f;
			break;
		case tulip::ElementSize::LARGE:
			frame_padding = style.FramePadding * 8.0f;
			break;
		default:
			frame_padding = style.FramePadding * 2.0f;
			break;
		}

		if (centered)
		{
			float size = ImGui::CalcTextSize(label.c_str()).x + frame_padding.x;
			float avail = ImGui::GetContentRegionAvail().x;

			float off = (avail - size) * 0.5f;
			if (off > 0.0f)
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
		}

		ImVec2 pos = window->DC.CursorPos;
		if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && frame_padding.y < window->DC.CurrLineTextBaseOffset)
			pos.y += window->DC.CurrLineTextBaseOffset - frame_padding.y;
		ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + frame_padding.x * 2.0f, label_size.y + frame_padding.y * 2.0f);

		size = ImGui::CalcItemSize(size_arg, label_size.x + frame_padding.x, label_size.y + frame_padding.y);
			

		const ImRect bb(pos, pos + size);
		ImGui::ItemSize(size, style.FramePadding.y);
		if (!ImGui::ItemAdd(bb, id)) return false;

		if (g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat) flags |= ImGuiButtonFlags_Repeat;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);


		const ImU32 col = ImGui::ColorConvertFloat4ToU32((held && hovered) ? *(ImVec4*)&s_theme.colors[color_index + 2] : hovered ? *(ImVec4*)&s_theme.colors[color_index + 1] : *(ImVec4*)&s_theme.colors[color_index]);

		ImGui::RenderNavHighlight(bb, id);

		ImGui::RenderFrame(bb.Min, bb.Max, col, true, s_theme.button_rounding);

		if (g.LogEnabled) ImGui::LogSetNextTextDecoration("[", "]");
		ImGui::RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label.c_str(), NULL, &label_size, style.ButtonTextAlign, &bb);

		IMGUI_TEST_ENGINE_ITEM_INFO(id, label.c_str(), g.LastItemData.StatusFlags);
		return pressed;

	}

	bool ImGuiTulip::TreeNodeEx(const void* ptr_id, const std::string& label, bool is_selected, uint8_t color_index, va_list args) {

		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems) return false;

		auto id = window->GetID(ptr_id);

		const char* lbl, * lbl_end;
		ImFormatStringToTempBufferV(&lbl, &lbl_end, label.c_str(), args);

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_OpenOnArrow;
		if (is_selected) flags |= ImGuiTreeNodeFlags_Selected;

		ImGuiContext& g = *GImGui;
		const ImGuiStyle& style = g.Style;
		const bool display_frame = (flags & ImGuiTreeNodeFlags_Framed) != 0;
		const ImVec2 padding = (display_frame || (flags & ImGuiTreeNodeFlags_FramePadding)) ? style.FramePadding : ImVec2(style.FramePadding.x, ImMin(window->DC.CurrLineTextBaseOffset, style.FramePadding.y));

		if (!lbl_end)
			lbl_end = ImGui::FindRenderedTextEnd(lbl);
		const ImVec2 label_size = ImGui::CalcTextSize(lbl, lbl_end, false);

		// We vertically grow up to current line height up the typical widget height.
		const float frame_height = ImMax(ImMin(window->DC.CurrLineSize.y, g.FontSize + style.FramePadding.y * 2), label_size.y + padding.y * 2);
		ImRect frame_bb;
		frame_bb.Min.x = (flags & ImGuiTreeNodeFlags_SpanFullWidth) ? window->WorkRect.Min.x : window->DC.CursorPos.x;
		frame_bb.Min.y = window->DC.CursorPos.y;
		frame_bb.Max.x = window->WorkRect.Max.x;
		frame_bb.Max.y = window->DC.CursorPos.y + frame_height;
		if (display_frame)
		{
			// Framed header expand a little outside the default padding, to the edge of InnerClipRect
			// (FIXME: May remove this at some point and make InnerClipRect align with WindowPadding.x instead of WindowPadding.x*0.5f)
			frame_bb.Min.x -= IM_FLOOR(window->WindowPadding.x * 0.5f - 1.0f);
			frame_bb.Max.x += IM_FLOOR(window->WindowPadding.x * 0.5f);
		}

		const float text_offset_x = g.FontSize + (display_frame ? padding.x * 3 : padding.x * 2);           // Collapser arrow width + Spacing
		const float text_offset_y = ImMax(padding.y, window->DC.CurrLineTextBaseOffset);                    // Latch before ItemSize changes it
		const float text_width = g.FontSize + (label_size.x > 0.0f ? label_size.x + padding.x * 2 : 0.0f);  // Include collapser
		ImVec2 text_pos(window->DC.CursorPos.x + text_offset_x, window->DC.CursorPos.y + text_offset_y);
		ImGui::ItemSize(ImVec2(text_width, frame_height), padding.y);

		// For regular tree nodes, we arbitrary allow to click past 2 worth of ItemSpacing
		ImRect interact_bb = frame_bb;
		if (!display_frame && (flags & (ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_SpanFullWidth)) == 0)
			interact_bb.Max.x = frame_bb.Min.x + text_width + style.ItemSpacing.x * 2.0f;

		// Store a flag for the current depth to tell if we will allow closing this node when navigating one of its child.
		// For this purpose we essentially compare if g.NavIdIsAlive went from 0 to 1 between TreeNode() and TreePop().
		// This is currently only support 32 level deep and we are fine with (1 << Depth) overflowing into a zero.
		const bool is_leaf = (flags & ImGuiTreeNodeFlags_Leaf) != 0;
		bool is_open = ImGui::TreeNodeUpdateNextOpen(id, flags);
		if (is_open && !g.NavIdIsAlive && (flags & ImGuiTreeNodeFlags_NavLeftJumpsBackHere) && !(flags & ImGuiTreeNodeFlags_NoTreePushOnOpen))
			window->DC.TreeJumpToParentOnPopMask |= (1 << window->DC.TreeDepth);

		bool item_add = ImGui::ItemAdd(interact_bb, id);
		g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_HasDisplayRect;
		g.LastItemData.DisplayRect = frame_bb;

		if (!item_add)
		{
			if (is_open && !(flags & ImGuiTreeNodeFlags_NoTreePushOnOpen))
				ImGui::TreePushOverrideID(id);
			IMGUI_TEST_ENGINE_ITEM_INFO(g.LastItemData.ID, label, g.LastItemData.StatusFlags | (is_leaf ? 0 : ImGuiItemStatusFlags_Openable) | (is_open ? ImGuiItemStatusFlags_Opened : 0));
			return is_open;
		}

		ImGuiButtonFlags button_flags = ImGuiTreeNodeFlags_None;
		if (flags & ImGuiTreeNodeFlags_AllowItemOverlap)
			button_flags |= ImGuiButtonFlags_AllowItemOverlap;
		if (!is_leaf)
			button_flags |= ImGuiButtonFlags_PressedOnDragDropHold;

		const float arrow_hit_x1 = (text_pos.x - text_offset_x) - style.TouchExtraPadding.x;
		const float arrow_hit_x2 = (text_pos.x - text_offset_x) + (g.FontSize + padding.x * 2.0f) + style.TouchExtraPadding.x;
		const bool is_mouse_x_over_arrow = (g.IO.MousePos.x >= arrow_hit_x1 && g.IO.MousePos.x < arrow_hit_x2);
		if (window != g.HoveredWindow || !is_mouse_x_over_arrow)
			button_flags |= ImGuiButtonFlags_NoKeyModifiers;

		if (is_mouse_x_over_arrow)
			button_flags |= ImGuiButtonFlags_PressedOnClick;
		else if (flags & ImGuiTreeNodeFlags_OpenOnDoubleClick)
			button_flags |= ImGuiButtonFlags_PressedOnClickRelease | ImGuiButtonFlags_PressedOnDoubleClick;
		else
			button_flags |= ImGuiButtonFlags_PressedOnClickRelease;

		bool selected = is_selected;
		const bool was_selected = selected;

		bool hovered, held;
		bool pressed = ImGui::ButtonBehavior(interact_bb, id, &hovered, &held, button_flags);
		bool toggled = false;
		if (!is_leaf)
		{
			if (pressed && g.DragDropHoldJustPressedId != id)
			{
				if ((flags & (ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick)) == 0 || (g.NavActivateId == id))
					toggled = true;
				if (flags & ImGuiTreeNodeFlags_OpenOnArrow)
					toggled |= is_mouse_x_over_arrow && !g.NavDisableMouseHover; // Lightweight equivalent of IsMouseHoveringRect() since ButtonBehavior() already did the job
				if ((flags & ImGuiTreeNodeFlags_OpenOnDoubleClick) && g.IO.MouseClickedCount[0] == 2)
					toggled = true;
			} else if (pressed && g.DragDropHoldJustPressedId == id)
			{
				IM_ASSERT(button_flags & ImGuiButtonFlags_PressedOnDragDropHold);
				if (!is_open) // When using Drag and Drop "hold to open" we keep the node highlighted after opening, but never close it again.
					toggled = true;
			}

			if (g.NavId == id && g.NavMoveDir == ImGuiDir_Left && is_open)
			{
				toggled = true;
				ImGui::NavMoveRequestCancel();
			}
			if (g.NavId == id && g.NavMoveDir == ImGuiDir_Right && !is_open) // If there's something upcoming on the line we may want to give it the priority?
			{
				toggled = true;
				ImGui::NavMoveRequestCancel();
			}

			if (toggled)
			{
				is_open = !is_open;
				window->DC.StateStorage->SetInt(id, is_open);
				g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_ToggledOpen;
			}
		}

		if (flags & ImGuiTreeNodeFlags_AllowItemOverlap)
			ImGui::SetItemAllowOverlap();

		// In this branch, TreeNodeBehavior() cannot toggle the selection so this will never trigger.
		if (selected != was_selected) //-V547
			g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_ToggledSelection;

		// Render
		const ImU32 text_col = ImGui::GetColorU32(ImGuiCol_Text);
		ImGuiNavHighlightFlags nav_highlight_flags = ImGuiNavHighlightFlags_TypeThin;
		if (display_frame)
		{
			// Framed type
			const ImU32 bg_col = ImGui::ColorConvertFloat4ToU32((held && hovered) ? *(ImVec4*)&s_theme.colors[color_index + 2] : hovered ? *(ImVec4*)&s_theme.colors[color_index] : *(ImVec4*)&s_theme.colors[color_index]);

			ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, bg_col, true, style.FrameRounding);
			ImGui::RenderNavHighlight(frame_bb, id, nav_highlight_flags);
			if (flags & ImGuiTreeNodeFlags_Bullet)
				ImGui::RenderBullet(window->DrawList, ImVec2(text_pos.x - text_offset_x * 0.60f, text_pos.y + g.FontSize * 0.5f), text_col);
			else if (!is_leaf)
				ImGui::RenderArrow(window->DrawList, ImVec2(text_pos.x - text_offset_x + padding.x, text_pos.y), text_col, is_open ? ImGuiDir_Down : ImGuiDir_Right, 1.0f);
			else // Leaf without bullet, left-adjusted text
				text_pos.x -= text_offset_x;
			if (flags & ImGuiTreeNodeFlags_ClipLabelForTrailingButton)
				frame_bb.Max.x -= g.FontSize + style.FramePadding.x;

			if (g.LogEnabled)
				ImGui::LogSetNextTextDecoration("###", "###");
			ImGui::RenderTextClipped(text_pos, frame_bb.Max, lbl, lbl_end, &label_size);
		} else {
			// Unframed typed for tree nodes
			if (hovered || selected)
			{
				const ImU32 bg_col = ImGui::ColorConvertFloat4ToU32(((held && !hovered) || (selected && !hovered)) ? *(ImVec4*)&s_theme.colors[color_index + 2] : hovered ? *(ImVec4*)&s_theme.colors[color_index] : *(ImVec4*)&s_theme.colors[color_index]);
				ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, bg_col, false);
			}
			ImGui::RenderNavHighlight(frame_bb, id, nav_highlight_flags);
			if (flags & ImGuiTreeNodeFlags_Bullet)
				ImGui::RenderBullet(window->DrawList, ImVec2(text_pos.x - text_offset_x * 0.5f, text_pos.y + g.FontSize * 0.5f), text_col);
			else if (!is_leaf)
				ImGui::RenderArrow(window->DrawList, ImVec2(text_pos.x - text_offset_x + padding.x, text_pos.y + g.FontSize * 0.15f), text_col, is_open ? ImGuiDir_Down : ImGuiDir_Right, 0.70f);
			if (g.LogEnabled)
				ImGui::LogSetNextTextDecoration(">", NULL);
			ImGui::RenderText(text_pos, lbl, lbl_end, false);
		}

		if (is_open && !(flags & ImGuiTreeNodeFlags_NoTreePushOnOpen))
			ImGui::TreePushOverrideID(id);
		IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | (is_leaf ? 0 : ImGuiItemStatusFlags_Openable) | (is_open ? ImGuiItemStatusFlags_Opened : 0));
		return is_open;
	}

	bool ImGuiTulip::TextInputEx(const std::string& label, std::string* txt) {

		ImGuiInputTextFlags flags = ImGuiInputTextFlags_CallbackResize;

		InputTextCallback_UserData cb_user_data;
		cb_user_data.Str = txt;
		cb_user_data.ChainCallback = NULL;
		cb_user_data.ChainCallbackUserData = NULL;
		ImGui::Text(label.c_str());
		ImGui::SameLine();
		ImGui::PushItemWidth(-1.0f);
		bool result = ImGui::InputText(("##" + label).c_str(), (char*)txt->c_str(), txt->capacity() + 1, flags, InputTextCallback, &cb_user_data);
		ImGui::PopItemWidth();
		return result;
	}

	void ImGuiTulip::BeginContainerEx(const float& padding) {
		ImGui::BeginTable("container", 3);
		ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, padding);
		ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthStretch);
		ImGui::TableSetupColumn("three", ImGuiTableColumnFlags_WidthFixed, padding);

		ImGui::TableNextColumn();
		ImGui::TableNextColumn();
	}

	void ImGuiTulip::EndContainerEx() {
		ImGui::TableNextColumn();
		ImGui::EndTable();
	}

	void ImGuiTulip::Vector3fEx(const std::string& label, glm::vec3* vec, const float& reset) {

		if (ImGui::TreeNodeEx(label.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });

			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 buttonSize = { lineHeight * .75f, lineHeight };

			ImGui::BeginTable((label + "").c_str(), 3);
			ImGui::TableNextColumn();

			//X Value
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f, 0.1f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.96f, 0.12f, 0.24f, 1.0f });
			if (ImGui::ButtonEx("X", buttonSize, ImGuiButtonFlags_PressedOnDoubleClick))
				vec->x = reset;
			ImGui::SameLine();
			ImGui::PushItemWidth(-1);
			ImGui::DragFloat("##X", &(vec->x), 0.05f, 0.0f, 0.0f, "%.2f");
			ImGui::PopItemWidth();
			ImGui::TableNextColumn();
			//Y Value
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.218f, 0.64f, 0.38f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.533f, 0.74f, 0.612f, 1.0f });
			if (ImGui::ButtonEx("Y", buttonSize, ImGuiButtonFlags_PressedOnDoubleClick))
				vec->y = reset;
			ImGui::SameLine();
			ImGui::PushItemWidth(-1);
			ImGui::DragFloat("##Y", &(vec->y), 0.05f, 0.0f, 0.0f, "%.2f");
			ImGui::PopItemWidth();
			ImGui::TableNextColumn();

			//Z Value
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.218f, 0.38f, 0.64f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.533f, 0.612f, 0.74f, 1.0f });
			if (ImGui::ButtonEx("Z", buttonSize, ImGuiButtonFlags_PressedOnDoubleClick))
				vec->z = reset;

			ImGui::SameLine();
			ImGui::PushItemWidth(-1);
			ImGui::DragFloat("##Z", &(vec->z), 0.05f, 0.0f, 0.0f, "%.2f");
			ImGui::PopItemWidth();

			ImGui::EndTable();

			ImGui::PopStyleColor(6);
			ImGui::PopStyleVar(1);
			ImGui::TreePop();
		}
	}

	UniqueRef<ImGuiTulip> ImGuiTulip::create() {
#ifdef TULIP_PLATFORM_WINDOWS
		return createUniqueRef<ImGuiOpenGL>();
#else
		return createUniqueRef<ImGuiOpenGL>();
#endif
	}
}
