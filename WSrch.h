// WSrch.h : WSRCH アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_WSRCH_H__CC55A51D_CC9A_4587_A7FD_4B2A6CF9A1C4__INCLUDED_)
#define AFX_WSRCH_H__CC55A51D_CC9A_4587_A7FD_4B2A6CF9A1C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CWSrchApp:
// このクラスの動作の定義に関しては WSrch.cpp ファイルを参照してください。
//

class CWSrchApp : public CWinApp
{
public:
	CWSrchApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CWSrchApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CWSrchApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_WSRCH_H__CC55A51D_CC9A_4587_A7FD_4B2A6CF9A1C4__INCLUDED_)
