#include "win_impl_base.hpp"
#include <Windows.h>
class MyWnd : public WindowImplBase
{
	LPCTSTR GetWindowClassName() const
	{
		return L"MyWnd";
	}
	UINT GetClassStyle() const{
		return UI_CLASSSTYLE_FRAME|CS_DBLCLKS;
	}
	tString GetSkinFile(){
		return L"tutorial7_3.xml";
	}
	void Notify(TNotifyUI& msg)
	{
		
	}
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_KEYDOWN:
			{
				int nVirtKey = (int) wParam;
				if(VK_ESCAPE == nVirtKey)
				{
					::PostQuitMessage(0);
				}
			}
			break;
		default:
			return WindowImplBase::HandleMessage(uMsg,wParam,lParam);
		}
		
	} 

};
INT WinMain(HINSTANCE hInst,HINSTANCE hPreInst,LPSTR lpCmdLine,INT Show)
{
	CPaintManagerUI::SetInstance(hInst);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetResourcePath());
	//创建主窗口
	MyWnd* pFrame = new MyWnd();
	pFrame->Create(NULL,L"Tutorial7",UI_WNDSTYLE_FRAME ,WS_EX_WINDOWEDGE);
	pFrame->CenterWindow(); 
	pFrame->ShowWindow(true);
	CPaintManagerUI::MessageLoop();
	 
	return 0;
}