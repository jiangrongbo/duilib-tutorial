#ifndef _MYWND_H__
#define _MYWND_H__
#include "win_impl_base.hpp"
#include "MenuWnd.h"
#include <Windows.h>
class MyWnd : public WindowImplBase
{
public: 
	MyWnd()
	{
		pMenu = new MenuWnd();
		pMenu->Create(m_hWnd,L"Menu",WS_POPUP,WS_EX_TOOLWINDOW);
		pMenu->ShowWindow(false);
	}
	LPCTSTR GetWindowClassName() const
	{
		return L"MyWnd";
	}
	UINT GetClassStyle() const{
		return UI_CLASSSTYLE_FRAME|CS_DBLCLKS;
	}
	tString GetSkinFile(){
		return L"tutorial6.xml";
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
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch(uMsg)
		{
		case WM_RBUTTONDOWN:
			OnRButtonDown(wParam,lParam);
			return 0; 
		default:
			return WindowImplBase::HandleMessage(uMsg,wParam,lParam);
		}
	}
	void OnRButtonDown(WPARAM wParam, LPARAM lParam)
	{ 
		int xPos = LOWORD(lParam); 
		int yPos = HIWORD(lParam);
		POINT pt = {xPos,yPos};
		ClientToScreen(m_hWnd,&pt); 
		pMenu->ShowWindow(true);
		::SetWindowPos(pMenu->GetHWND(), NULL, pt.x, pt.y, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE); 
	} 
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//获取鼠标点击位置
		int xPos = LOWORD(lParam); 
		int yPos = HIWORD(lParam);
		//將位置转换为屏幕坐标
		POINT pt = {xPos,yPos};
		ClientToScreen(m_hWnd,&pt); 

		RECT menuWndRect = {0};
		::GetWindowRect(pMenu->GetHWND(),&menuWndRect);
		
		if(pt.x <= menuWndRect.left || pt.x >= menuWndRect.right 
			|| pt.y <= menuWndRect.top || pt.y >= menuWndRect.bottom)
		{
			pMenu->ShowWindow(false);
		}
		bHandled = FALSE;
		return 0;
	}

private:
	MenuWnd* pMenu;
	 
};
#endif