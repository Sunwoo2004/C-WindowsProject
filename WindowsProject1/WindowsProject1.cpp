#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

bool InitMainWindow(HINSTANCE, int);

LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);

const int WIDTH = 800;
const int HEIGHT = 600;

HWND hwnd = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!InitMainWindow(hInstance, nCmdShow))
	{
		return 1;
	}

	MSG msg = { 0 };
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			break;
		}
	}

	return static_cast<int>(msg.wParam);
}

bool InitMainWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.lpfnWndProc = MsgProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wcex.lpszClassName = "Test1";
	wcex.lpszMenuName = NULL;
	wcex.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassEx(&wcex))
	{
		return false;
	}

	hwnd = CreateWindow("Test1", "TestWindow", WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, GetSystemMetrics(SM_CYSCREEN) / 2 - WIDTH / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - HEIGHT / 2, WIDTH, HEIGHT, (HWND)NULL, (HMENU)NULL, hInstance, (LPVOID*)NULL);
	if (!hwnd)
	{
		return false;
	}

	ShowWindow(hwnd, nCmdShow);

	return true;
}

LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CHAR:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
