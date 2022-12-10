#include "tulippch.h"
#include "windowsWindow.h"
#include <logging\logger.h>

namespace tulip {
	WindowsWindow::WindowsWindow(const int& width, const int& height, const std::string& title, const int& posX, const int& posY) {
		m_shouldClose = false;

		m_hInstance = GetModuleHandle(nullptr);
		m_wndClassName.assign(title.begin(), title.end());

		WNDCLASS wndClass = {};
		wndClass.lpszClassName = m_wndClassName.c_str();
		wndClass.hInstance = this->m_hInstance;
		wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.lpfnWndProc = windowProc; //fix later

		RegisterClass(&wndClass);

		DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_OVERLAPPEDWINDOW | WS_SYSMENU;

		RECT rect;
		rect.left = posX;
		rect.top = posY;
		rect.right = posX+ width;
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
			NULL
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

		ShowWindow(m_hWnd, SW_SHOW);

	}

	WindowsWindow::~WindowsWindow() {

		ReleaseDC(this->m_hWnd, this->m_deviceContext);
		wglDeleteContext(this->m_glHandle);

		UnregisterClass(this->m_wndClassName.c_str(), this->m_hInstance);

	}

	void WindowsWindow::update() {
		this->m_shouldClose = !processMessages();
		SwapBuffers(this->m_deviceContext);
	}

	bool WindowsWindow::shouldClose() {
		return m_shouldClose;
	}

	int WindowsWindow::getWidth() const {
		RECT rect = this->getRect();
		return rect.right - rect.left;
	}

	int WindowsWindow::getHeight() const {
		RECT rect = this->getRect();
		return rect.bottom - rect.top;
	}

	int WindowsWindow::getPosX() const {
		RECT rect = this->getRect();
		return rect.left;
	}

	int WindowsWindow::getPosY() const {
		RECT rect = this->getRect();
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
		RECT rect = this->getRect();
		SetWindowPos(this->m_hWnd, HWND_TOPMOST, rect.left, rect.top, w, rect.bottom - rect.top, SWP_NOMOVE);
	}

	void WindowsWindow::setHeight(const int& h) {
		RECT rect = this->getRect();
		SetWindowPos(this->m_hWnd, HWND_TOPMOST, rect.left, rect.top, rect.right - rect.left, h, SWP_NOMOVE);
	}

	void WindowsWindow::setPosX(const int& x) {
		RECT rect = this->getRect();
		SetWindowPos(this->m_hWnd, HWND_TOPMOST, x, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOSIZE);
	}

	void WindowsWindow::setPosY(const int& y) {
		RECT rect = this->getRect();
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

		while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {
			
			if (msg.message == WM_QUIT) {
				return false;
			}
		
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return true;
	}

	RECT WindowsWindow::getRect() const {

		RECT rect = {};

		if (!GetWindowRect(this->m_hWnd, &rect)) {
			std::cout << "Error" << std::endl;
		}

		return rect;
	}

	LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		
		switch (uMsg)
		{
		case WM_CLEAR:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			break;
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		
		return LRESULT();
	}

}