#pragma once
#define SDL_MAIN_HANDLED
#include <functional>
#include <string>

namespace tulip {

	class Window {
	public:
		virtual ~Window() {}

		virtual void update() = 0;
		virtual bool shouldClose() = 0;

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

	protected:
		Window() {}

	private:
		Window(Window& other) = delete;
		//using EventCallback = std::function<void(Event&)>;

	};

}