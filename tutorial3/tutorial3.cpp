#include <Windows.h>
#include "../DuiLib/StdAfx.h" 
using namespace DuiLib;
class CMyWnd : public CWindowWnd,public INotifyUI
{
public:
	CMyWnd(){}
	LPCTSTR GetWindowClassName() const
	{
		return L"MyWnd";
	}
	UINT GetClassStyle() const{
		return UI_CLASSSTYLE_FRAME|CS_DBLCLKS;
	}
	void Notify(TNotifyUI& msg)
	{
		if(msg.sType == L"click")
		{
			if(msg.pSender->GetName() == L"CloseBtn")
			{
				if(IDOK == ::MessageBox(m_hWnd,L"退出程序？",L"提示信息",MB_OKCANCEL))
				{
					::PostQuitMessage(0);
				}
			}
		}
	}
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch(uMsg)
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
		case WM_CREATE:
			{
				m_PaintMgr.Init(m_hWnd); 
				//从xml中加载界面
				CDialogBuilder builder;
				m_pRoot = builder.Create(L"tutorial3.xml",(UINT)0,NULL,&m_PaintMgr);

				m_PaintMgr.AttachDialog(m_pRoot); 
				m_PaintMgr.AddNotifier(this);
			}
			break;  
		case WM_DESTROY:
			::PostQuitMessage(0);
			break;
		} 
		LRESULT lRes=0;
		if(m_PaintMgr.MessageHandler(uMsg,wParam,lParam,lRes)) return lRes;
		return CWindowWnd::HandleMessage(uMsg,wParam,lParam);
	}

	~CMyWnd(){
		delete m_pRoot;
	}
private:
	CPaintManagerUI m_PaintMgr; 
	CControlUI* m_pRoot;
};
INT WinMain(HINSTANCE hInst,HINSTANCE hPreInst,LPSTR lpCmdLine,INT Show)
{
	CPaintManagerUI::SetInstance(hInst);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetResourcePath());
	//创建主窗口
	CMyWnd* pFrame = new CMyWnd();
	pFrame->Create(NULL,L"Tutorial3",UI_WNDSTYLE_FRAME,WS_EX_WINDOWEDGE);
	pFrame->CenterWindow();
	pFrame->ShowWindow(true); 
	CPaintManagerUI::MessageLoop(); 
	delete pFrame;
	return 0;
}