// **************************************************************************
//  @file       WSRCH.cpp
//  @brief      WSrch アプリケーションクラスの実装
//
//  @author     Iwao (https://mish.work/)
//  @date       2026-05-18
//
//  @modify
//  2026-05-18  新規作成
//
//  @disclaimer
//  本コードの使用により生じたいかなる損害についても著作者は責任を負いません
//  引用時は上記 URL を明記してください
//
//  (C) 2026 Iwao. All Rights Reserved.
// **************************************************************************

#include "stdafx.h"
#include "WSrch.h"
#include "WSrchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWSrchApp

BEGIN_MESSAGE_MAP(CWSrchApp, CWinApp)
	//{{AFX_MSG_MAP(CWSrchApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWSrchApp クラスの構築

CWSrchApp::CWSrchApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CWSrchApp オブジェクト

CWSrchApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWSrchApp クラスの初期化

BOOL CWSrchApp::InitInstance()
{
	AfxOleInit() ;
	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。

//#ifdef _AFXDLL
//	Enable3dControls();			// 共有 DLL 内で MFC を使う場合はここをコールしてください。
//#else
//	Enable3dControlsStatic();	// MFC と静的にリンクする場合はここをコールしてください。
//#endif
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CWSrchDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//       記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <ｷｬﾝｾﾙ> で消された時のコードを
		//       記述してください。
	}

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}
