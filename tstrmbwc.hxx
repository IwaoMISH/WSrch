//	*******************************************************************************
//	Name	:	tstrmbwc.hxx
//			:	tstring convert
//	Author	:	I. Nakagawa
//	Create	:	2014/02/12
//	Modify	:	2014/06/12		Add GetS_Width
//	Modify	:	2020/03/05		change include
//	Modify	:	2024/11/22
//	*******************************************************************************

#pragma		once

#include	<cstdlib>
#include	<cstring>
#ifdef		_MSC_VER
#include	<mbctype.h>		//	for _KANJI_CP
#ifdef		_AFXDLL
#include	<Afx.h>
#else
#include	<Windows.h>
#endif
#endif
#ifndef		_KANJI_CP
#define		_KANJI_CP	932
#endif
#include	"tstring.hxx"

////
//	*******************************************************************************
//	MultiByte	->	WideChar
//	Create	:	2014/02/12
//	*******************************************************************************
inline	size_t	MBstoWCs	(wchar_t* wcStr,const size_t wcSizeW,const char* mbStr,const size_t mbCount)
{
	#ifdef		_MSC_VER
	size_t	cnvSize = 0 ;
	{
		cnvSize =	::MultiByteToWideChar(_KANJI_CP,	0,			mbStr,	int(mbCount),
											wcStr,	int(wcSizeW)) ;
		cnvSize-- ;
		}
	return	cnvSize ;
	#else
	{
		return	::mbstowcs(wcStr,mbStr,wcSizeW) ;
		}
	#endif
	}

////
//	*******************************************************************************
//	WideChar	->	MultiByte
//	Create	:	2014/02/12
//	*******************************************************************************
inline	size_t	WCstoMBs	(char* mbStr,const size_t mbSizeB,const wchar_t* wcStr,const size_t mbCount)
{
	#ifdef		_MSC_VER
	size_t	cnvSize = 0 ;
	{
		char	defChar[] = "__" ;
		BOOL	defUse = FALSE ;
		cnvSize = 	::WideCharToMultiByte(_KANJI_CP,	0,	wcStr,	-1,
											mbStr,				int(mbSizeB),	defChar,&defUse) ;
		}
	return	cnvSize ;
	#else
	{
		return	::wcstombs(mbStr,wcStr,mbSizeB) ;
		}
	#endif
	}

////
//	*******************************************************************************
//	->	WideChar
//	Create	:	2014/02/12
//	*******************************************************************************
inline	std::wstring	ts_toWCs	(const char* m_Str)
{
	std::wstring	wcStr ;
	wcStr.resize(::strlen(m_Str)+1,0) ;
	MBstoWCs(&wcStr[0],wcStr.size(),m_Str,::strlen(m_Str)) ;
	return	wcStr.c_str() ;
	}

////
//	*******************************************************************************
//	->	MultiByte
//	Create	:	2014/02/12
//	*******************************************************************************
inline	std::string		ts_toMBs	(const wchar_t* w_Str)
{
	std::string		mbStr ;
	mbStr.resize((::wcslen(w_Str)+1)*3,0) ;
	WCstoMBs(&mbStr[0],mbStr.size(),w_Str,::wcslen(w_Str)) ;
	return	mbStr.c_str() ;
	}

////
//	*******************************************************************************
//	Xxxx	->	Xxxx	Copy
//	Create	:	2014/02/12
//	*******************************************************************************
inline	std::wstring	ts_toWCs	(const wchar_t* w_Str)
{
	std::wstring	wcStr = w_Str ;
	return	wcStr ;
	}

inline	std::string		ts_toMBs	(const char* m_Str)
{
	std::string		mbStr = m_Str ;
	return	mbStr ;
	}

////
//	*******************************************************************************
//	TSTR	->
//	Create	:	2014/02/12
//	*******************************************************************************
inline	std::wstring	To_wstring	(LPCTSTR str)
{
	return	::ts_toWCs(str) ;
	}

inline	std::string		To__string	(LPCTSTR str)
{
	return	::ts_toMBs(str) ;
	}

////
//	*******************************************************************************
//	tstring	->
//	Create	:	2018/04/06
//	*******************************************************************************
inline	std::wstring	To_wstring	(c_tstring& str)	{	return	::To_wstring(str.c_str()) ;		}
inline	std::string		To__string	(c_tstring& str)	{	return	::To__string(str.c_str()) ;		}

////
//	*******************************************************************************
//	->	tstring
//	Create	:	2014/02/12
//	*******************************************************************************
inline	tstring	To_tstring	(const char* m_Str)
{
	tstring	tstr ;
	#ifdef	_UNICODE
		tstr = ::ts_toWCs(m_Str) ;
	#else
		tstr = ::ts_toMBs(m_Str) ;
	#endif
	return	tstr ;
	}
inline	tstring	To_tstring	(const wchar_t* w_Str)
{
	tstring	tstr ;
	#ifdef	_UNICODE
		tstr = ::ts_toWCs(w_Str) ;
	#else
		tstr = ::ts_toMBs(w_Str) ;
	#endif
	return	tstr ;
	}

/*
inline	tstring	To_tstring	(LPCTSTR str)
{
	tstring	tstr ;
	#ifdef	_UNICODE
		tstr = ::To_wstring(str) ;
	#else
		tstr = ::To__string(str) ;
	#endif
	return	tstr ;
	}
*/

#ifdef		_DEBUG
#else
#include	"wstr_bom.hxx"
#endif

/*
////
#define	UNICODE_BOM		L'\xfeff'
//	*******************************************************************************
//	wstring		Add BOM
//	Create	:	2014/02/13
//	*******************************************************************************
inline	std::wstring	WString_Del_BOM	(const std::wstring w_str)
{
	std::wstring	wStr = w_str ;
	for (std::wstring::size_type index=0 ; index<w_str.size() ; index++) {
		wchar_t	wc = w_str[index] ;
		if (wc == UNICODE_BOM)	{	continue ;	}
		wStr = w_str.substr(index) ;
		break ;
		}
	return	wStr ;
	}

//	*******************************************************************************
//	wstring		Del BOM
//	Create	:	2014/02/13
//	*******************************************************************************
inline	std::wstring	WString_Add_BOM	(const std::wstring w_str)
{
	std::wstring	wStr = ::WString_Del_BOM(w_str) ;
	wStr = UNICODE_BOM + wStr ;
	return	wStr ;
	}
*/


