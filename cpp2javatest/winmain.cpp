#define CPP2JAVALIB_LIBPATH "../cpp2javalib/"
#include "../cpp2javalib/cpp2javalib.h"
#include "../cpp2javalib/AppletViewer.h"
#include "JavaTest.h"
#include <Windows.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	AppletViewer a(hInstance, hPrevInstance, lpCmdLine, nCmdShow, &JavaTest(), 640, 480);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	JavaTest* test = new JavaTest();
	test->Test();
	delete test;
//    AppletViewer a(hInstance, hPrevInstance, lpCmdLine, nCmdShow, &JavaDF2(), 640, 480);
	return 0;
}
