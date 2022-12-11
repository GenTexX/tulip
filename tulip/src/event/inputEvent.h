#pragma once

#include "event.h"

#include <sstream>
#include <cstdint>

#pragma warning(disable : 26812)

namespace tulip {

	using KeyCode = uint32_t;

	struct KeyboardEvent : public Event {
		KeyCode m_KeyCode = 0;
		EVENT_CATEGORY(KeyboardEventCategory | InputEventCategory)
	};

	struct KeyPressedEvent : public KeyboardEvent {
		KeyPressedEvent(KeyCode kcode) { this->m_KeyCode = kcode; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyPressed\tKeyCode: " << this->m_KeyCode;
			return ss.str();
		}

		EVENT_TYPE(KeyPressed)
	};

	struct KeyReleasedEvent : public KeyboardEvent {
		KeyReleasedEvent(KeyCode kcode) { this->m_KeyCode = kcode; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyReleased\tKeyCode: " << this->m_KeyCode;
			return ss.str();
		}

		EVENT_TYPE(KeyReleased)
	};

	struct MouseEvent : public Event {
		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseEvent";
			return ss.str();
		}

		EVENT_CATEGORY(InputEventCategory | MouseEventCategory)
	};

	struct MouseButtonEvent  : public MouseEvent {
		uint8_t m_Button = 0;

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonEvent";
			return ss.str();
		}
	};

	struct MouseButtonDown : public MouseButtonEvent {
		MouseButtonDown(uint8_t btn) { m_Button = btn; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonDown\tButton: " << (int)this->m_Button;
			return ss.str();
		}

		EVENT_TYPE(MouseButtonPressed)
	};

	struct MouseButtonUp : public MouseButtonEvent {
		MouseButtonUp(uint8_t btn) { m_Button = btn; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseButtonUp\tButton: " << (int)this->m_Button;
			return ss.str();
		}

		EVENT_TYPE(MouseButtonReleased)
	};

	struct MouseMovedEvent : public MouseEvent {
		int m_MousePosX, m_MousePosY;

		MouseMovedEvent(const int& x, const int& y) : m_MousePosX(x), m_MousePosY(y) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseMoved: " << this->m_MousePosX << ", " << this->m_MousePosY;
			return ss.str();
		}

		EVENT_TYPE(MouseMoved)
	};

	struct MouseScrolledEvent : public MouseEvent {
		int m_Scroll;

		MouseScrolledEvent(const int& scroll) : m_Scroll(scroll) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseScrolled: " << this->m_Scroll;
			return ss.str();
		}

		EVENT_TYPE(MouseScrolled)
	};

}

#pragma warning(default : 26812)