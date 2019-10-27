////////////////////////////////////////////////////////////////////////
// AfxMessageBoxEx
////////////////////////////////////////////////////////////////////////
HHOOK g_HookHandle;
int g_PosX, g_PosY, g_Width, g_Height;

LRESULT CALLBACK cbHookMsgBox(int nCode, WPARAM wParam, LPARAM lParam);
int AfxMessageBoxEx(LPCSTR message , UINT nType);

LRESULT CALLBACK cbHookMsgBox (int nCode, WPARAM wParam ,LPARAM lParam )
{
	switch (nCode)
	{
		case HCBT_ACTIVATE:
		{
			CWnd* wnd = CWnd::FromHandle((HWND)wParam);
			WINDOWINFO winf;
			winf.cbSize = sizeof(winf);
			wnd->GetWindowInfo(&winf);
			// change position
			wnd->SetWindowPos(NULL, g_PosX, g_PosY, g_Width, g_Height, SWP_NOSIZE | SWP_NOZORDER);
			// unhook
			ret = UnhookWindowsHookEx(g_HookHandle);
			break;
		}
	}
	HRESULT ret;
		
	return CallNextHookEx(g_HookHandle, nCode, wParam, lParam);
}
int AfxMessageBoxEx(LPCSTR message, UINT nType, int x, int y, int cx, int cy)
{
	// set position
	g_PosX = x;
	g_PosY = y;
	g_Width = cx;
	g_Height = cy;
	// hook
	g_HookHandle = SetWindowsHookEx(WH_CBT, cbHookMsgBox, NULL, GetCurrentThreadId()); 
	return (AfxMessageBox(message, nType)); 
}
