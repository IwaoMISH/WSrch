//	*******************************************************************************
//	Name	:	wstr_bom.hxx
//			:	tstring convert
//	Author	:	I. Nakagawa
//	Create	:	2024/11/22
//	Modify	:	2014/02/13
//	Modify	:	2024/11/22
//	*******************************************************************************

#pragma		once

#include	"tstring.hxx"

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

