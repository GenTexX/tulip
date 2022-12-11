#include "tulippch.h"
#include "windowsWindow.h"
#include <logging\logger.h>
#include <event\inputEvent.h>
#include <event\windowEvent.h>
#include <event\keycode.h>

namespace tulip {
	WindowsWindow::WindowsWindow(const int& width, const int& height, const std::string& title, const int& posX, const int& posY) {
		m_eventCallback = nullptr;
		m_shouldClose = false;

		m_hInstance = GetModuleHandle(nullptr);
		m_wndClassName.assign(title.begin(), title.end());

		WNDCLASS wndClass = {};
		wndClass.lpszClassName = m_wndClassName.c_str();
		wndClass.hInstance = this->m_hInstance;
		wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.lpfnWndProc = windowProc;

		RegisterClass(&wndClass);

		DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_OVERLAPPEDWINDOW | WS_SYSMENU;

		RECT rect;
		rect.left = posX;
		rect.top = posY;
		rect.right = posX + width;
		rect.bottom = posY + height;

		AdjustWindowRect(&rect, style, false);

		m_hWnd = CreateWindowEx(
			0,
			m_wndClassName.c_str(),
			m_wndClassName.c_str(),
			style,
			rect.left,
			rect.top,
			rect.right - rect.left,
			rect.bottom - rect.top,
			NULL,
			NULL,
			m_hInstance,
			(LPVOID)(this)
		);

		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
			PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
			32,                   // Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                   // Number of bits for the depthbuffer
			8,                    // Number of bits for the stencilbuffer
			0,                    // Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		this->m_deviceContext = GetDC(this->m_hWnd);
		int pf = ChoosePixelFormat(this->m_deviceContext, &pfd);
		SetPixelFormat(this->m_deviceContext, pf, &pfd);
		this->m_glHandle = wglCreateContext(this->m_deviceContext);
		wglMakeCurrent(this->m_deviceContext, this->m_glHandle);

	}

	WindowsWindow::~WindowsWindow() {

		ReleaseDC(this->m_hWnd, this->m_deviceContext);
		wglDeleteContext(this->m_glHandle);

		UnregisterClass(this->m_wndClassName.c_str(), this->m_hInstance);

	}

	void WindowsWindow::hide() {
		ShowWindow(this->m_hWnd, SW_HIDE);
	}

	void WindowsWindow::show() {
		ShowWindow(this->m_hWnd, SW_SHOW);
	}

	void WindowsWindow::update() {
		this->m_shouldClose = !processMessages();
		SwapBuffers(this->m_deviceContext);
	}

	bool WindowsWindow::shouldClose() {
		return m_shouldClose;
	}

	int WindowsWindow::getWidth() const {
		RECT rect = this->getClientRect();
		return rect.right - rect.left;
	}

	int WindowsWindow::getHeight() const {
		RECT rect = this->getClientRect();
		return rect.bottom - rect.top;
	}

	int WindowsWindow::getPosX() const {
		RECT rect = this->getWindowRect();
		return rect.left;
	}

	int WindowsWindow::getPosY() const {
		RECT rect = this->getWindowRect();
		return rect.top;
	}

	std::string WindowsWindow::getTitle() const {
		wchar_t title[100];
		GetWindowText(this->m_hWnd, title, 100);
		std::wstring tmp = title;
		std::string result;
		size_t size;
		result.resize(tmp.length());
		wcstombs_s(&size, &result[0], result.size() + 1, tmp.c_str(), tmp.size());
		return result;
	}

	void WindowsWindow::setWidth(const int& w) {
		RECT rect = this->getClientRect();
		SetWindowPos(this->m_hWnd, HWND_TOPMOST, rect.left, rect.top, w, rect.bottom - rect.top, SWP_NOMOVE);
	}

	void WindowsWindow::setHeight(const int& h) {
		RECT rect = this->getClientRect();
		SetWindowPos(this->m_hWnd, HWND_TOPMOST, rect.left, rect.top, rect.right - rect.left, h, SWP_NOMOVE);
	}

	void WindowsWindow::setPosX(const int& x) {
		RECT rect = this->getWindowRect();
		SetWindowPos(this->m_hWnd, HWND_TOPMOST, x, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOSIZE);
	}

	void WindowsWindow::setPosY(const int& y) {
		RECT rect = this->getWindowRect();
		SetWindowPos(this->m_hWnd, HWND_TOPMOST, rect.left, y, rect.right - rect.left, rect.bottom - rect.top, SWP_NOSIZE);
	}

	void WindowsWindow::setTitle(const std::string& title) {
		std::wstring tmp;
		size_t size;
		tmp.resize(title.length());
		mbstowcs_s(&size, &tmp[0], tmp.size() + 1, title.c_str(), title.size());
		SetWindowText(this->m_hWnd, tmp.c_str());
	}

	bool WindowsWindow::processMessages() {

		MSG msg = {};
		bool quit = false;
		while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {

			if (msg.message == WM_QUIT) {
				quit = true;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}



		return !quit;
	}

	RECT WindowsWindow::getClientRect() const {

		RECT rect = {};

		if (!GetClientRect(this->m_hWnd, &rect)) {
			TULIP_CORE_ERROR("ERROR: Failed to get Window Rect!");
		}

		return rect;
	}

	RECT WindowsWindow::getWindowRect() const {

		RECT rect = {};

		if (!GetWindowRect(this->m_hWnd, &rect)) {
			TULIP_CORE_ERROR("ERROR: Failed to get Window Rect!");
		}

		return rect;
	}

	LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		WindowsWindow* wnd = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		switch (uMsg)
		{
		case WM_CREATE:
		{
			CREATESTRUCT* pcs = reinterpret_cast<CREATESTRUCT*>(lParam);
			LONG_PTR wnd = (LONG_PTR)pcs->lpCreateParams;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, wnd);
			ShowWindow(hWnd, SW_SHOW);
		}
		break;
		case WM_CLEAR:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_MOVE:
			if (wnd->m_eventCallback != nullptr) {
				WindowMovedEvent e = WindowMovedEvent((int)GET_X_LPARAM(lParam), (int)GET_Y_LPARAM(lParam), wnd);
				wnd->m_eventCallback(e);
			}
			return 0;
		case WM_SIZE:
			if (wnd->m_eventCallback != nullptr) {
				if (wParam == SIZE_MAXIMIZED) {
					WindowMaximizeEvent e = WindowMaximizeEvent(wnd);
					wnd->m_eventCallback(e);
				} else if (wParam == SIZE_MINIMIZED) {
					WindowMinimizeEvent e = WindowMinimizeEvent(wnd);
					wnd->m_eventCallback(e);
				}

				WindowResizeEvent e = WindowResizeEvent((int)LOWORD(lParam), (int)HIWORD(lParam), wnd);
				wnd->m_eventCallback(e);
			}
			return 0;
		case WM_SHOWWINDOW:
			if (wnd->m_eventCallback != nullptr) {
				if (wParam) {
					WindowShownEvent e = WindowShownEvent(wnd);
					wnd->m_eventCallback(e);
				} else {
					WindowHiddenEvent e = WindowHiddenEvent(wnd);
					wnd->m_eventCallback(e);
				}
			}
			return 0;
		case WM_SETFOCUS:
			if (wnd->m_eventCallback != nullptr) {
				WindowFocusGainEvent e = WindowFocusGainEvent(wnd);
				wnd->m_eventCallback(e);
			}
			return 0;
		case WM_KILLFOCUS:
			if (wnd->m_eventCallback != nullptr) {
				WindowFocusLoseEvent e = WindowFocusLoseEvent(wnd);
				wnd->m_eventCallback(e);
			}
			return 0;
		case WM_KEYDOWN:
			if (wnd->m_eventCallback != nullptr) {
				KeyPressedEvent e = KeyPressedEvent(wParam);
				wnd->m_eventCallback(e);
			}
			return 0;
		case WM_MOUSEMOVE:
			if (wnd->m_eventCallback != nullptr) {
				MouseMovedEvent e = MouseMovedEvent(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				wnd->m_eventCallback(e);
			}
			return 0;
		case WM_MOUSEWHEEL:
			if (wnd->m_eventCallback != nullptr) {
				MouseScrolledEvent e = MouseScrolledEvent(GET_WHEEL_DELTA_WPARAM(wParam));
				wnd->m_eventCallback(e);
			}
			return 0;
		case WM_LBUTTONDOWN:
			if (wnd->m_eventCallback != nullptr) {
				MouseButtonDown e = MouseButtonDown(TULIP_LEFT_MOUSE_BUTTON);
				wnd->m_eventCallback(e);
			}
			return 0;
		case WM_LBUTTONUP:
			if (wnd->m_eventCallback != nullptr) {
				MouseButtonUp e = MouseButtonUp(TULIP_LEFT_MOUSE_BUTTON);
				wnd->m_eventCallback(e);
			}
			return 0;
		case WM_MBUTTONDOWN:
			if (wnd->m_eventCallback != nullptr) {
				MouseButtonDown e = MouseButtonDown(TULIP_MIDDLE_MOUSE_BUTTON);
				wnd->m_eventCallback(e);
			}
			return 0;
		case WM_MBUTTONUP:
			if (wnd->m_eventCallback != nullptr) {
				MouseButtonUp e = MouseButtonUp(TULIP_MIDDLE_MOUSE_BUTTON);
				wnd->m_eventCallback(e);
			}
			return 0;
		case WM_RBUTTONDOWN:
			if (wnd->m_eventCallback != nullptr) {
				MouseButtonDown e = MouseButtonDown(TULIP_RIGHT_MOUSE_BUTTON);
				wnd->m_eventCallback(e);
			}
			return 0;
		case WM_RBUTTONUP:
			if (wnd->m_eventCallback != nullptr) {
				MouseButtonUp e = MouseButtonUp(TULIP_RIGHT_MOUSE_BUTTON);
				wnd->m_eventCallback(e);
			}
			return 0;
		default:
			break;
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

}