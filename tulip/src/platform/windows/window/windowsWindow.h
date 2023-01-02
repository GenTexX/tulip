#pragma once

#include <string>
#include <platform/windows/platformWindows.h>
#include <windowsx.h>

#include <core\core.h>
#include <window\window.h>

namespace tulip {

	LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const int& width, const int& height, const std::string& title, const int& posX, const int& posY);
		WindowsWindow(const Window& other) = delete;
		WindowsWindow& operator=(const Window& other) = delete;
		virtual ~WindowsWindow();

		virtual TulipWindowHandle getWindowHandle();
		virtual OGLContext getContext() const;

		virtual void hide() override;
		virtual void show() override;

		virtual void update();
		virtual bool shouldClose();

		virtual int getWidth() const;
		virtual int getHeight() const;
		virtual int getPosX() const;
		virtual int getPosY() const;
		virtual std::string getTitle() const;

		virtual void setWidth(const int& w);
		virtual void setHeight(const int& h);
		virtual void setPosX(const int& x);
		virtual void setPosY(const int& y);
		virtual void setTitle(const std::string& title);

	private:
		std::wstring m_wndClassName;
		HINSTANCE m_hInstance;
		HWND m_hWnd;
		OGLContext m_context;
		bool m_shouldClose;

		bool processMessages();
		RECT getClientRect() const;
		RECT getWindowRect() const;

		friend LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	};

}