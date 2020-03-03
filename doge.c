#include <Windows.h>

static HHOOK hhk;

LRESULT CALLBACK CBTProc(INT nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam, IDOK, "WTF");
		UnhookWindowsHookEx(hhk);
	}
	else
	{
		CallNextHookEx(hhk, nCode, wParam, lParam);
	}
	
	return 0;
}
 
int CBTMessageBoxIndirect(const MSGBOXPARAMSA *lpmbp)
{
	hhk = SetWindowsHookEx(WH_CBT, &CBTProc, NULL, GetCurrentThreadId());
	return MessageBoxIndirect(lpmbp);
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSGBOXPARAMSA mbp;
	
	mbp.cbSize             = sizeof(MSGBOXPARAMSA);
	mbp.hwndOwner          = NULL;
	mbp.hInstance          = GetModuleHandle(NULL);
	mbp.lpszText           = "DOGE IS HACKING YOUR COMPUTER";
	mbp.lpszCaption        = "WTF";
	mbp.dwStyle            = MB_OK | MB_USERICON;
	mbp.lpszIcon           = MAKEINTRESOURCE(1);
	mbp.dwContextHelpId    = NULL;
	mbp.lpfnMsgBoxCallback = NULL;
	mbp.dwLanguageId       = LANG_NEUTRAL;
	
	CBTMessageBoxIndirect(&mbp);
	
	return 0;
}
