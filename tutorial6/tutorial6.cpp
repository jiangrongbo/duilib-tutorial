#include <Windows.h>
#include "MyWnd.h" 
INT WinMain(HINSTANCE hInst,HINSTANCE hPreInst,LPSTR lpCmdLine,INT Show)
{
	CPaintManagerUI::SetInstance(hInst);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetResourcePath());
	//创建主窗口
	MyWnd* pFrame = new MyWnd();
	pFrame->Create(NULL,L"Tutorial6",UI_WNDSTYLE_FRAME,WS_EX_WINDOWEDGE);
	pFrame->CenterWindow(); 
	pFrame->ShowWindow(true); 
	CPaintManagerUI::MessageLoop();

	return 0;
}