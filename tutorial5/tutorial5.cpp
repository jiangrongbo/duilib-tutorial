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
		return L"tutorial5.xml";
	}
	void Notify(TNotifyUI& msg)
	{
		if(msg.sType == L"click")
		{
			if(msg.pSender->GetName() == L"CloseBtn")
			{
				::PostQuitMessage(0);

			}else if(msg.pSender->GetName() == L"MinBtn")
			{
				::SendMessage(m_hWnd,WM_SYSCOMMAND, SC_MINIMIZE, 0);
			}
		}
	} 
	

};
INT WinMain(HINSTANCE hInst,HINSTANCE hPreInst,LPSTR lpCmdLine,INT Show)
{
	CPaintManagerUI::SetInstance(hInst);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetResourcePath());
	//创建主窗口
	MyWnd* pFrame = new MyWnd();
	pFrame->Create(NULL,L"Tutorial5",UI_WNDSTYLE_FRAME^WS_THICKFRAME,WS_EX_WINDOWEDGE);
	pFrame->CenterWindow(); 
	pFrame->ShowWindow(true);
	CPaintManagerUI::MessageLoop();
	 
	return 0;
}