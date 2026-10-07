// **************************************************************************
//  @file       WSRCHDLG.cpp
//  @brief      WSrch メインダイアログクラスの実装
//
//  @author     Iwao (https://mish.work/)
//  @date       2026-05-19
//
//  @modify
//  2026-05-18  新規作成
//  2026-05-19  幾つかの変更
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

#include "WSEngine.inc"
#include "WinStore.inc"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////
// **************************************************************************
//  クリップボードへテキストをコピー
//  作成日    :    2026-05-19
// **************************************************************************
static BOOL SetClipboardText(HWND hWnd, LPCTSTR lpszText)
{
    if (lpszText == NULL) {
        return FALSE;
    }

    if (::OpenClipboard(hWnd)) {
        ::EmptyClipboard();

        size_t nLen = ::_tcslen(lpszText);
        HGLOBAL hMem = ::GlobalAlloc(GMEM_MOVEABLE, (nLen + 1) * sizeof(TCHAR));
        
        if (hMem != NULL) {
            LPTSTR lpszMem = (LPTSTR)::GlobalLock(hMem);
            if (lpszMem != NULL) {
                ::lstrcpy(lpszMem, lpszText);
                ::GlobalUnlock(hMem);

                // Unicode か ANSI かによって形式を選択
#ifdef _UNICODE
                ::SetClipboardData(CF_UNICODETEXT, hMem);
#else
                ::SetClipboardData(CF_TEXT, hMem);
#endif
            }
        }
        ::CloseClipboard();
        return (hMem != NULL);
    }
    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// メッセージ ハンドラがありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWSrchDlg ダイアログ

CWSrchDlg::CWSrchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWSrchDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWSrchDlg)
	m_strKeyword 		= _T("");
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pSystemImageList	= NULL ;
	m_nSortCol			= -1 ;
	m_bAscending		= true ;

	}

void CWSrchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWSrchDlg)
	DDX_Control	(pDX, IDOK, 				m_btnSearch);
	DDX_Control	(pDX, IDC_EDIT_KEYWORD, 	m_editKeyword);
	DDX_Control	(pDX, IDC_COMBO_EXT, 		m_comboExt);
	DDX_Control	(pDX, IDC_LIST_RESULTS, 	m_listResults);
	DDX_Text	(pDX, IDC_EDIT_KEYWORD, 	m_strKeyword);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWSrchDlg, CDialog)
	//{{AFX_MSG_MAP(CWSrchDlg)
	ON_WM_SYSCOMMAND	()
	ON_WM_PAINT			()
	ON_WM_SIZE			()
	ON_WM_QUERYDRAGICON	()
	ON_NOTIFY			(NM_DBLCLK, 		IDC_LIST_RESULTS, OnDblclkListResults)
	ON_NOTIFY			(LVN_COLUMNCLICK, 	IDC_LIST_RESULTS, OnColumnclickListResults)
	ON_NOTIFY			(NM_RCLICK, 		IDC_LIST_RESULTS, OnRclickListResults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWSrchDlg メッセージ ハンドラ

BOOL CWSrchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニュー項目をシステム メニューへ追加します。

	// IDM_ABOUTBOX はコマンド メニューの範囲でなければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	{
		// ★追加：システムイメージリストの取得と設定
		SHFILEINFO sfi;
		HIMAGELIST hSystemImageList = (HIMAGELIST)::SHGetFileInfo(_T("C:\\"), 0, &sfi, sizeof(sfi), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
		if (hSystemImageList) {
			m_pSystemImageList = CImageList::FromHandle(hSystemImageList);
			m_listResults.SetImageList(m_pSystemImageList, LVSIL_SMALL);
			}
		}
	{
		// コンボボックス（m_comboExt）の初期値設定
		m_comboExt.ResetContent() ;
		m_comboExt.AddString(_T("*"));        // すべてのファイル
		m_comboExt.AddString(_T("cpp;hpp"));  // C++ ソース
		m_comboExt.AddString(_T("txt;doc"));  // テキスト・文書
		m_comboExt.AddString(_T("jpg;png"));  // 画像ファイル
		// 最初の項目（*）を選択状態にする
		m_comboExt.SetCurSel(0);
		}
	{
	    // リストコントロール（m_listResults）の初期設定
	    // 1. カラム（列）の追加
		m_listResults.InsertColumn(0, _T("ファイル名"), LVCFMT_LEFT, 150);
		m_listResults.InsertColumn(1, _T("更新日時"),   LVCFMT_LEFT, 130);
		m_listResults.InsertColumn(2, _T("フルパス"),   LVCFMT_LEFT, 400);
	    // 2. スタイルの設定（行全体の選択を有効にし，グリッド線を表示）
	    m_listResults.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		}
	{
		CRect rect;
		GetClientRect(&rect);
		SendMessage(WM_SIZE, SIZE_RESTORED, MAKELPARAM(rect.Width(), rect.Height()));
		}

    {
        // 最初の項目（*）を選択状態にする（デフォルト値）
        m_comboExt.SetCurSel(0);
        // ★追加：INIファイルから前回の拡張子インデックスを復元
        CWinApp* pApp = ::AfxGetApp();
        if (pApp) {
            int nSel = pApp->GetProfileInt(_T("Settings"), _T("LastExtIndex"), 0);
            if (nSel < m_comboExt.GetCount()) {
                m_comboExt.SetCurSel(nSel);
	            }
	        }
	    }
	{
	    // ウィンドウ位置の復元
	    ::RestoreWindowPosition(this);
		}

	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
	}


void CWSrchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CWSrchDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CWSrchDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWSrchDlg::OnOK() 
{
    // 1. 画面の入力値（キーワード）を変数 m_strKeyword に同期
    UpdateData(TRUE);

	{
	    // 検索実行時に現在の設定と位置を保存
	    CWinApp* pApp = ::AfxGetApp();
	    if (pApp) {
	        pApp->WriteProfileInt(_T("Settings"), _T("LastExtIndex"), m_comboExt.GetCurSel());
	        ::SaveWindowPosition(this);
		    }
		}

    if (m_strKeyword.IsEmpty()) {
        return; // キーワードが空なら何もしない
    }

	// ソート条件の決定
	CWSEngine::SORT_TYPE sort = CWSEngine::SORT_NONE;
	{
		if		(m_nSortCol == 0) 	{	sort = m_bAscending ? CWSEngine::SORT_NAME_ASC : CWSEngine::SORT_NAME_DESC;	}
		else if	(m_nSortCol == 1) 	{	sort = m_bAscending ? CWSEngine::SORT_DATE_ASC : CWSEngine::SORT_DATE_DESC;	}
		else if	(m_nSortCol == 2) 	{	sort = m_bAscending ? CWSEngine::SORT_PATH_ASC : CWSEngine::SORT_PATH_DESC;	}
		}

    // 2. コンボボックスから現在の選択（拡張子）を取得
    CString strExt;
    m_comboExt.GetWindowText(strExt);

    // 3. リストを一旦空にする
    m_listResults.DeleteAllItems();

    // 4. エンジンの準備
    CWSEngine engine;
    
    // キーワードを AND 検索用にトークナイズ（WSENGINE.INC 内の関数）
    v_tstring vKeys = TokenizeAND((LPCTSTR)m_strKeyword);

    // 5. 検索実行（日付の新しい順）
	vv_tstring vvResults = engine.Search(LPCTSTR(strExt), vKeys, sort);
	{
        
        // 描画のチラつきを抑えるためのフリーズ
        m_listResults.SetRedraw(FALSE);

        for (size_t i = 0; i < vvResults.size(); ++i) {
            v_tstring	vResult = vvResults[i];
            tstring		tsPath = vResult[0];
            
            // ファイル名だけを抽出
            TCHAR szName[MAX_PATH];
            ::lstrcpy(szName, tsPath.c_str());
            ::PathStripPath(szName);

            // ★追加：ファイルのアイコンインデックスを取得
			SHFILEINFO sfi;
			::SHGetFileInfo(tsPath.c_str(), 0, &sfi, sizeof(sfi), 
							SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES);

            // リストに行を追加（1列目：ファイル名）
			int nItem = m_listResults.InsertItem(i, szName, sfi.iIcon);

            // 2列目：更新日時（現在は仮のハイフン。後ほど実装）
            m_listResults.SetItemText(nItem, 1, vResult[1].c_str());

            // 3列目：フルパス
            m_listResults.SetItemText(nItem, 2, tsPath.c_str());
	        }

        m_listResults.SetRedraw(TRUE);
	    }

	}

void CWSrchDlg::OnDblclkListResults(NMHDR* pNMHDR, LRESULT* pResult) 
{
    // NM_ITEMACTIVATE の代わりに VC6 でも定義されている NM_LISTVIEW を使用します
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    // 1. 選択されている行と列を取得
    int nItem    = pNMListView->iItem;
    int nSubItem = pNMListView->iSubItem;
    if (nItem != -1) {
        // 2. 3列目（インデックス 2）のフルパスを取得
        CString strPath = m_listResults.GetItemText(nItem, 2);
        if (!strPath.IsEmpty()) {
            if (nSubItem == 2) {
                // --- フルパス列（3列目）がダブルクリックされた場合 ---
                // エクスプローラーで該当ファイルを選択した状態で開く
                CString strParam;
                // スペースを含むパスに対応するため、パスをダブルクォーテーションで囲みます
                strParam.Format(_T("/select,\"%s\""), (LPCTSTR)strPath);
                ::ShellExecute(NULL, _T("open"), _T("explorer.exe"), strParam, NULL, SW_SHOWNORMAL);
	            }
            else {
                // --- それ以外の列がダブルクリックされた場合 ---
                // 関連付けられたアプリでファイル自体を開く
                ::ShellExecute(m_hWnd, _T("open"), strPath, NULL, NULL, SW_SHOWNORMAL);
	            }
	        }
	    }
    *pResult = 0;
	}

void CWSrchDlg::OnSize(UINT nType, int cx, int cy) 
{
    CDialog::OnSize(nType, cx, cy);
    
    if (!::IsWindow(m_listResults.GetSafeHwnd())) {
        return;
    }

    int nMargin = 10;           // 外周余白
    int nBtnWidth = 80;         // 検索ボタンの幅
    int nComboWidth = 100;      // 拡張子コンボボックスの幅
    int nEditHeight = 24;       // エディット・ボタンの高さ
    int nComboHeight = 150;     // ★コンボボックス（ドロップダウン時を含む）の高さ
    int nSpacing = 5;           // コントロール間の隙間

    // 1. コンボボックス（拡張子選択）
    m_comboExt.MoveWindow(nMargin, nMargin, nComboWidth, nComboHeight);

    // 2. エディットボックス（キーワード入力）
    int nEditLeft = nMargin + nComboWidth + nSpacing;
    int nEditWidth = cx - (nMargin * 2) - nComboWidth - nBtnWidth - (nSpacing * 2);
    m_editKeyword.MoveWindow(nEditLeft, nMargin, nEditWidth, nEditHeight);

    // 3. 検索ボタン
    int nBtnLeft = nEditLeft + nEditWidth + nSpacing;
    m_btnSearch.MoveWindow(nBtnLeft, nMargin, nBtnWidth, nEditHeight);

    // 4. リストコントロール
    int nListTop = nMargin + nEditHeight + nSpacing;
    int nListHeight = cy - nListTop - nMargin;
    m_listResults.MoveWindow(nMargin, nListTop, cx - (nMargin * 2), nListHeight);

    // 3列目（フルパス）の幅調整
    int nCol0 = m_listResults.GetColumnWidth(0);
    int nCol1 = m_listResults.GetColumnWidth(1);
    int nNewCol2Width = cx - (nMargin * 2) - nCol0 - nCol1 - 25;
    if (nNewCol2Width > 100) {
        m_listResults.SetColumnWidth(2, nNewCol2Width);
	    }
	}

void CWSrchDlg::OnColumnclickListResults(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nCol = pNMListView->iSubItem;

    if (nCol == m_nSortCol) {
        // 同じ列をクリックした場合は昇順・降順を反転
        m_bAscending = !m_bAscending;
	    } 
	else {
        // 別の列をクリックした場合は、その列のデフォルト順を設定
        m_nSortCol = nCol;
        m_bAscending = (nCol == 1) ? false : true; // 日付なら降順、他は昇順をデフォルトに
	    }

    // 再検索を実行
    OnBtnSearch();

    *pResult = 0;
	}

BOOL CWSrchDlg::OnBtnSearch()
{
	OnOK() ;
	return	TRUE ;
	}

void CWSrchDlg::OnRclickListResults(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    int nItem = pNMListView->iItem;

    // 何も選択されていない（空欄右クリック）場合は何もしない
    if (nItem == -1) {
        *pResult = 0;
        return;
    }

    // 1. 動的にメニューを作成
    CMenu menu;
    if (menu.CreatePopupMenu()) {
        menu.AppendMenu(MF_STRING, 1001, _T("開く(&O)"));
        menu.AppendMenu(MF_STRING, 1002, _T("保存場所を開く(&P)"));
        menu.AppendMenu(MF_SEPARATOR);
        menu.AppendMenu(MF_STRING, 1003, _T("フルパスをコピー(&C)"));

        // 2. 表示位置（マウスカーソル位置）の取得
        CPoint pt;
        ::GetCursorPos(&pt);

        // 3. メニューを表示し、選択されたコマンドIDを取得
        int nCommand = (int)menu.TrackPopupMenu(
            TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, 
            pt.x, pt.y, this);

        // 4. コマンドに応じた処理の分岐
        if (nCommand > 0) {
            ExecuteContextMenuCommand(nCommand, nItem);
        }
    }

    *pResult = 0;
}

////
// **************************************************************************
//  コンテキストメニューのコマンド実行
//  作成日    :    2026-05-19
// **************************************************************************
void CWSrchDlg::ExecuteContextMenuCommand(int nCommand, int nItem)
{
    if (nItem == -1) {
        return;
    }

    // リストの3列目（インデックス 2）からフルパスを取得
    CString strPath = m_listResults.GetItemText(nItem, 2);
    if (strPath.IsEmpty()) {
        return;
    }

    switch (nCommand) {
    case 1001: // 開く(&O)
        {
            // 関連付けられたアプリでファイルを開く
            ::ShellExecute(m_hWnd, _T("open"), strPath, NULL, NULL, SW_SHOWNORMAL);
        }
        break;

    case 1002: // 保存場所を開く(&P)
        {
            // エクスプローラーで該当ファイルを選択した状態で表示
            CString strParam;
            strParam.Format(_T("/select,\"%s\""), (LPCTSTR)strPath);
            ::ShellExecute(NULL, _T("open"), _T("explorer.exe"), strParam, NULL, SW_SHOWNORMAL);
        }
        break;

    case 1003: // フルパスをコピー(&C)
        {
            // 先ほど追加した static ヘルパー関数を使用
            if (::SetClipboardText(m_hWnd, (LPCTSTR)strPath)) {
                // 必要であればステータスバー等に「コピーしました」と出すのも良いですが、
                // 今回はシンプルに実行のみとします
            }
        }
        break;

    default:
        break;
    }
}


