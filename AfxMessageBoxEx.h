HHOOK g_HookHandle;

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
			if ((winf.dwStyle & WS_POPUPWINDOW) == WS_POPUPWINDOW)
			{
				wnd->SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			}
			break;
		}
	}
	HRESULT ret;
	// アンインストール
	ret = UnhookWindowsHookEx(g_HookHandle);
	
	return CallNextHookEx(g_HookHandle, nCode, wParam, lParam);
}
int AfxMessageBoxEx(LPCSTR message, UINT nType)
{
	g_HookHandle = SetWindowsHookEx(WH_CBT, cbHookMsgBox, NULL, GetCurrentThreadId()); 
	return (AfxMessageBox(message, nType)); 
}
