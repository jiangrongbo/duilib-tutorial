#ifndef _MENUWND_H__
#define _MENUWND_H__
#include "win_impl_base.hpp"
#include <Windows.h>
class MenuWnd : public WindowImplBase
{
	LPCTSTR GetWindowClassName() const
	{
		return L"MenuWnd";
	}
	UINT GetClassStyle() const{
		return UI_CLASSSTYLE_FRAME|CS_DBLCLKS;
	}
	tString GetSkinFile(){
		return L"tutorial6_menu.xml";
	}
	void Notify(TNotifyUI& msg)
	{ 
		if(msg.sType == L"itemclick")
		{
			//响应菜单事件
			::MessageBox(NULL,L"hello",L"hello",MB_OK);
			this->ShowWindow(false);
		} 
	} 

};
#endif