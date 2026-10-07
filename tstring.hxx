//	*******************************************************************************
//	Name	:	tstring.hxx
//			:	Define "tstring"
//	Author	:	I. Nakagawa
//	Create	:	2012/07/10
//	Modify	:	2013/09/02
//	Modify	:	2019/10/23
//	Modify	:	2024/07/01	add disable 4786
//	*******************************************************************************

#pragma		once

//#if	_MSC_VER == 1200
//	#ifdef	_UNICODE
	//	#include	<Afx.h>
	//	#pragma	message	("VC6 _UNICODE  -----  include <Afx.h>  -----")
//	#endif
//#endif

#ifdef		_MSC_VER
	#pragma	warning	(disable	:	4786	)
#endif
#include	<string>

#ifdef		_MSC_VER
	#include	<tchar.h>
//	http://marupeke296.com/TIPS_No14_tstring.html
	typedef		std::basic_string <TCHAR,std::char_traits<TCHAR>,std::allocator<TCHAR> >	tstring ;
#else
	typedef		std::basic_string <char, std::char_traits<char>, std::allocator<char>  >	tstring ;
#endif

	typedef		const	tstring								c_tstring ;

#ifdef		_MSC_VER
//	(VS8)\VC\PlatformSDK\Include\WTypes.h
	typedef				TCHAR*								LPTSTR  ;
	typedef		const	TCHAR*								LPCTSTR ;
#else
	typedef				char*								LPTSTR  ;
	typedef		const	char*								LPCTSTR ;
	typedef				char*								LPSTR  ;
	typedef		const	char*								LPCSTR ;
	typedef				wchar_t*							LPWSTR  ;
	typedef		const	wchar_t*							LPCWSTR ;
#endif

