// **************************************************************************
//  @file       WSRCHDLG.H
//  @brief      WSrch メインダイアログクラス
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

#if !defined(AFX_WSRCHDLG_H__34481E84_7F79_43F5_8EEF_CBD15D6812BE__INCLUDED_)
#define AFX_WSRCHDLG_H__34481E84_7F79_43F5_8EEF_CBD15D6812BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWSrchDlg ダイアログ

class CWSrchDlg : public CDialog
{
// 構築
public:
	void ExecuteContextMenuCommand(int nCommand, int nItem);
	BOOL OnBtnSearch(void);
	CWSrchDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CWSrchDlg)
	enum { IDD = IDD_WSRCH_DIALOG };
	CButton		m_btnSearch;
	CEdit		m_editKeyword;
	CComboBox	m_comboExt;
	CListCtrl	m_listResults;
	CString		m_strKeyword;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CWSrchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON	m_hIcon;


	CImageList* m_pSystemImageList;	// システムイメージリスト用
	// ソート状態管理用
	int		m_nSortCol;				// 現在のソート列番号 (0:名前, 1:日付, 2:パス)
	bool	m_bAscending;			// 昇順なら true, 降順なら false


	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CWSrchDlg)
	virtual BOOL OnInitDialog				();
	afx_msg void OnSysCommand				(UINT nID, LPARAM lParam);
	afx_msg void OnSize						(UINT nType, int cx, int cy);
	afx_msg void OnPaint					();
	afx_msg HCURSOR OnQueryDragIcon			();
	virtual void OnOK						();
	afx_msg void OnDblclkListResults		(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListResults	(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListResults		(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_WSRCHDLG_H__34481E84_7F79_43F5_8EEF_CBD15D6812BE__INCLUDED_)
