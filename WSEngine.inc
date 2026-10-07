// **************************************************************************
//  @file       WSENGINE.INC
//  @brief      Windows Search 汎用検索エンジン
//
//  @author     Iwao ( https://mish.work/ )
//  @date       2026-05-18
//
//  @modify
//  2026-05-12  Newly created
//  2026-05-18  いろいろと変更
//
//  @disclaimer
//  本コードの使用により生じたいかなる損害についても著作者は責任を負いません
//  引用時は上記 URL を明記してください
//
//  (C) 2026 Iwao. All Rights Reserved.
// **************************************************************************

#pragma once


/////////////////////////////////////////////////////////////////////////////////////////

#include	"v_tstrng.hxx"

// 文字列をスペース（全角含む）で分割して AND 用配列に格納する
inline	v_tstring	TokenizeAND(const tstring& tsInput)
{
	v_tstring vKeys ;
    tstring tsWork = tsInput;

    // 全角スペースを半角に統一
    for (size_t i = 0; i < tsWork.length(); ++i) {
        if (tsWork[i] == _T('　')) {
            tsWork[i] = _T(' ');
            }
        }

    size_t nStart = 0;
    size_t nEnd = tsWork.find(_T(' '));
    while (true) {
        tstring tsToken = (nEnd == tstring::npos) ? tsWork.substr(nStart) : tsWork.substr(nStart, nEnd - nStart);

        if (!tsToken.empty()) {
            vKeys.push_back(tsToken);
            }

        if (nEnd == tstring::npos) {
            break;
            }
        nStart = nEnd + 1;
        nEnd = tsWork.find(_T(' '), nStart);
        }
	return	vKeys ;
	}

inline	v_tstring	TokenizeSeparator(const tstring& tsInput, TCHAR chSep) 
{
    v_tstring vTokens;
    size_t nStart = 0;
    size_t nEnd = tsInput.find(chSep);
    while (true) {
        tstring tsToken = (nEnd == tstring::npos) ? tsInput.substr(nStart) : tsInput.substr(nStart, nEnd - nStart);
        if (!tsToken.empty()) vTokens.push_back(tsToken);
        if (nEnd == tstring::npos) break;
        nStart = nEnd + 1;
        nEnd = tsInput.find(chSep, nStart);
	    }
    return vTokens;
	}

/////////////////////////////////////////////////////////////////////////////////////////


#include	"Path_Fnc.hxx"
#include	"tstring.hxx"
#include	"iVariant.hxx"

//#import	"C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "adoEOF")
#import  	                                         "msado15.dll" no_namespace rename("EOF", "adoEOF")

class CWSEngine {
public:
	// ソート条件の定義
	enum SORT_TYPE {
		SORT_NONE = 0,		// ソートなし
		SORT_DATE_DESC,		// 更新日時（新しい順）
		SORT_DATE_ASC,		// 更新日時（古い順）
		SORT_NAME_DESC,		// ファイル名（Z-A）
		SORT_NAME_ASC,		// ファイル名（A-Z）
		SORT_PATH_DESC,		// フルパス名（Z-A）
		SORT_PATH_ASC,		// フルパス名（A-Z）
		SORT_SIZE_DESC,		// サイズ（大きい順）
		SORT_SIZE_ASC,		// サイズ（小さい順）
		SORT_TYPE_DESC,		// タイプ（大きい順）
		SORT_TYPE_ASC,		// タイプ（小さい順）
		SORT_CREATE_DESC,	// 作成日時（新しい順）
		SORT_CREATE_ASC,	// 作成日時（古い順）
		};

public:
    		 CWSEngine() {}
    virtual ~CWSEngine() {}

public:
	inline vv_tstring Search(const tstring& tsExt, const v_tstring& vKeys, SORT_TYPE sort = SORT_NONE) {
	    return SearchBySQL(BuildSQL(tsExt, vKeys, sort));
		}

	inline vv_tstring SearchBySQL(const tstring& tsSQL) {
	    vv_tstring vvResults;
	    try {
	        _ConnectionPtr pConn(__uuidof(Connection));
	        tstring tsConn = _T("Provider=Search.CollatorDSO;Extended Properties='Application=Windows';");
	        pConn->Open(tsConn.c_str(), _T(""), _T(""), adConnectUnspecified);

	        _RecordsetPtr pRs = pConn->Execute(tsSQL.c_str(), NULL, adCmdText);
	        while (!pRs->adoEOF) {
	            v_tstring vRow;
	            i_VARIANT iVarUrl  = pRs->Fields->GetItem(_T("System.ItemUrl"))->Value;
	            i_VARIANT iVarDate = pRs->Fields->GetItem(_T("System.DateModified"))->Value;
	            vRow.push_back(::PathCreateFromUrl(tstring(iVarUrl)));
	            vRow.push_back(tstring(iVarDate));
	            vvResults.push_back(vRow);
	            pRs->MoveNext();
		        }
	        pRs  ->Close();
	        pConn->Close();
		    }
	    catch (_com_error &e) {
	        ::OutputDebugString(e.ErrorMessage());
	        // 失敗時は空のまま返す
		    }
	    return vvResults;
	}

public:
    // SQL 文の組み立てロジック（独立して利用可能）
    inline tstring BuildSQL(const tstring& tsExt, const v_tstring& vKeys, SORT_TYPE sort = SORT_PATH_ASC) {
        tstring tsSQL ;
	//			tsSQL += _T("SELECT System.ItemPathDisplay ");
			//	tsSQL += _T("SELECT System.ItemUrl         ");
				tsSQL += _T("SELECT System.ItemUrl, System.DateModified "); 
				tsSQL += _T("FROM SYSTEMINDEX ");
				tsSQL += _T("WHERE ");
				tsSQL += _T(" System.FileAttributes IS NOT NULL ");
	//			tsSQL += _T(" AND System.FileName LIKE '%.") + tsExt + _T("'");
	//			tsSQL += _T(" AND System.Kind <> 'email'");
	//			tsSQL += _T(" AND System.Kind <> 'email' AND System.ItemPathDisplay LIKE '%\\%'");
	//			tsSQL += _T(" AND System.Kind <> 'email' AND System.ItemUrl         LIKE '%\\%'");
	//			tsSQL += _T(" AND System.Kind <> 'email' AND System.ItemUrl         LIKE '%\\%'");
				tsSQL += _T(" AND System.ItemUrl LIKE 'file:%' ");

	    // --- 拡張子フィルタの構築 ---
	    if (!tsExt.empty() && tsExt != _T("*")) {
	        tsSQL += _T(" AND (");
	        v_tstring vExts = ::TokenizeSeparator(tsExt,_T(';')) ;
	        for (size_t i = 0; i < vExts.size(); ++i) {
	            if (i > 0) {
					tsSQL += _T(" OR ");
					}
	            // 拡張子に '*' が含まれているかチェック
	            if (vExts[i].find(_T('*')) != tstring::npos) {
	                // 'jp*' -> '%.jp%' に変換（Windows Search の LIKE は % を使用）
	                tstring sLike = vExts[i];
	                for(size_t j=0; j<sLike.length(); ++j) {
						if (sLike[j] == _T('*')) {
							sLike[j] =  _T('%');
							}
						}
	                tsSQL += _T("System.FileName LIKE '%.") + sLike + _T("'");
		            } 
				else {
	                tsSQL += _T("System.FileName LIKE '%.") + vExts[i] + _T("'");
		            }
		        }
	        tsSQL += _T(")");
		    }

	    // --- キーワード検索部分 ---
	    for (v_tstring::const_iterator it = vKeys.begin(); it != vKeys.end(); ++it) {
	        if (it->empty()) {
				continue;
				}
	        
	        // CONTAINS は便利ですが、複雑なワイルドカードは LIKE の方が確実な場合があります
	        // 'jp*' などの入力をそのまま SQL のワイルドカード '%' に変換して評価
	        tstring sKey = *it;
	        bool bHasWild = (sKey.find(_T('*')) != tstring::npos);
	        
	        if (bHasWild) {
	            for(size_t j=0; j<sKey.length(); ++j) if(sKey[j] == _T('*')) sKey[j] = _T('%');
	            tsSQL += _T(" AND System.FileName LIKE '") + sKey + _T("'");
		        } 
			else {
	            // 通常のキーワードは今まで通り CONTAINS で高速検索
	            tsSQL += _T(" AND CONTAINS(*, '\"") + (*it) + _T("*\"')");
		        }
		    }

		switch (sort) {
			case SORT_DATE_DESC:		{	tsSQL += _T(" ORDER BY System.DateModified    DESC");	}	break;
			case SORT_DATE_ASC: 		{	tsSQL += _T(" ORDER BY System.DateModified     ASC");	}	break;
			case SORT_NAME_DESC:		{	tsSQL += _T(" ORDER BY System.FileName        DESC");	}	break;
			case SORT_NAME_ASC: 		{	tsSQL += _T(" ORDER BY System.FileName         ASC");	}	break;
			case SORT_PATH_DESC:		{	tsSQL += _T(" ORDER BY System.ItemUrl         DESC");	}	break;
			case SORT_PATH_ASC: 		{	tsSQL += _T(" ORDER BY System.ItemUrl          ASC");	}	break;
			case SORT_SIZE_DESC:		{	tsSQL += _T(" ORDER BY System.Size            DESC");	}	break;
			case SORT_SIZE_ASC: 		{	tsSQL += _T(" ORDER BY System.Size             ASC");	}	break;
			case SORT_TYPE_DESC:		{	tsSQL += _T(" ORDER BY System.ItemType        DESC");	}	break;
			case SORT_TYPE_ASC: 		{	tsSQL += _T(" ORDER BY System.ItemType         ASC");	}	break;
			case SORT_CREATE_DESC:		{	tsSQL += _T(" ORDER BY System.DateCreated     DESC");	}	break;
			case SORT_CREATE_ASC: 		{	tsSQL += _T(" ORDER BY System.DateCreated      ASC");	}	break;
			default:            		{	                                                     	}	break;
			}

		#ifdef	_DEBUG
		{
		//	afxDump << tsSQL.c_str() << _T("\r\n") ;
			}
		#endif

        return tsSQL;
	    }

	};
