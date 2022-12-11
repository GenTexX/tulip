#pragma once

#include <core\core.h>
#include <event\event.h>

#include <functional>
#include <string>

namespace tulip {

	class Window {
	public:
		static Ref<Window> create(const int& width, const int& height, const std::string& title, const int& posX, const int& posY);

		virtual ~Window() {}

		virtual void update() = 0;
		virtual bool shouldClose() = 0;

		virtual void hide() = 0;
		virtual void show() = 0;

		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;
		virtual int getPosX() const = 0;
		virtual int getPosY() const = 0;
		virtual std::string getTitle() const = 0;

		virtual void setWidth(const int& w) = 0;
		virtual void setHeight(const int& h) = 0;
		virtual void setPosX(const int& x) = 0;
		virtual void setPosY(const int& y) = 0;
		virtual void setTitle(const std::string& title) = 0;

		using EventCallback = std::function<void(Event&)>;
		void setEventCallback(const EventCallback& callback) { this->m_eventCallback = callback; }

	protected:
		Window() {}
		EventCallback m_eventCallback;


	private:
		Window(Window& other) = delete;

	};

}