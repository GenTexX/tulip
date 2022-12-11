#pragma once

#include "event.h"
#include <core\core.h>
#include <window\window.h>

#include <cstdint>
#include <sstream>

namespace tulip {

	struct WindowEvent : public Event {
		Window* m_window = 0;
		std::string toString() const override { return "WindowEvent"; }
		EVENT_CATEGORY(WindowEventCategory)
	};

	struct WindowShownEvent : public WindowEvent {
		WindowShownEvent(Window* w) { this->m_window = w; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowEvent: shown";
			return ss.str();
		}

		EVENT_TYPE(WindowShown)
	};

	struct WindowHiddenEvent : public WindowEvent {
		WindowHiddenEvent(Window* w) { this->m_window = w; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowEvent: hidden";
			return ss.str();
		}

		EVENT_TYPE(WindowHidden)
	};

	struct WindowMovedEvent : public WindowEvent {
		int m_PosX, m_PosY;

		WindowMovedEvent(const int& posx, const int& posy, Window* w) : m_PosX(posx), m_PosY(posy) { this->m_window = w; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowEvent: moved: " << this->m_PosX << "px, " << this->m_PosY << "px";
			return ss.str();
		}

		EVENT_TYPE(WindowMoved)
	};

	struct WindowResizeEvent : public WindowEvent {
		int m_Width, m_Height;

		WindowResizeEvent(const int& width, const int& height, Window* w) : m_Width(width), m_Height(height) { this->m_window = w; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowEvent: resized: " << this->m_Width << "px, " << this->m_Height << "px";
			return ss.str();
		}

		EVENT_TYPE(WindowResized)
	};

	struct WindowMinimizeEvent : public WindowEvent {
		WindowMinimizeEvent(Window* w) { this->m_window = w; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowEvent: minimized";
			return ss.str();
		}

		EVENT_TYPE(WindowMinimized)
	};

	struct WindowMaximizeEvent : public WindowEvent {
		WindowMaximizeEvent(Window* w) { this->m_window = w; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowEvent: maximized";
			return ss.str();
		}

		EVENT_TYPE(WindowMaximized)
	};

	struct WindowEnterEvent : public WindowEvent {
		WindowEnterEvent(Window* w) { this->m_window = w; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowEvent: entered";
			return ss.str();
		}

		EVENT_TYPE(WindowEnter)
	};

	struct WindowLeaveEvent : public WindowEvent {
		WindowLeaveEvent(Window* w) { this->m_window = w; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowEvent: left";
			return ss.str();
		}

		EVENT_TYPE(WindowLeave)
	};

	struct WindowFocusGainEvent : public WindowEvent {
		WindowFocusGainEvent(Window* w) { this->m_window = w; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowEvent: focus gained";
			return ss.str();
		}

		EVENT_TYPE(WindowFocusGained)
	};

	struct WindowFocusLoseEvent : public WindowEvent {
		WindowFocusLoseEvent(Window* w) { this->m_window = w; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowEvent: focus lost";
			return ss.str();
		}

		EVENT_TYPE(WindowFocusLost)
	};

	struct WindowCloseEvent : public WindowEvent {
		WindowCloseEvent(Window* w) { this->m_window = w; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowEvent: closed";
			return ss.str();
		}

		EVENT_TYPE(WindowClose)
	};

	struct WindowTakeFocusEvent : public WindowEvent {
		WindowTakeFocusEvent(Window* w) { this->m_window = w; };

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowEvent: take focus";
			return ss.str();
		}

		EVENT_TYPE(WindowTakeFocus)
	};

	struct WindowHitTestEvent : public WindowEvent {
		WindowHitTestEvent(Window* w) { this->m_window = w; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowEvent: hit test";
			return ss.str();
		}

		EVENT_TYPE(WindowHitTest)
	};


}