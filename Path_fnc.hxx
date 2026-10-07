// **************************************************************************
//  @file       PATH_FNC.HXX
//  @brief      PathCreateFromUrl
//
//  @author     Iwao (https://mish.work/)
//  @date       2026-05-15
//
//  @modify
//  2026-05-15  Newly created
//
//  @disclaimer
//  The author is not responsible for any damage caused by using this code.
//  Please specify the above URL when quoting.
//
//  (C) 2026 Iwao. All Rights Reserved.
// **************************************************************************

#pragma		once

#include	<shlwapi.h>
#include	"tstring.hxx"

#ifndef						PathCreateFromUrl
	extern	"C"	LWSTDAPI	PathCreateFromUrlA	(LPCSTR  pszUrl, LPSTR  pszPath, LPDWORD pcchPath, DWORD dwFlags);
	extern	"C"	LWSTDAPI	PathCreateFromUrlW	(LPCWSTR pszUrl, LPWSTR pszPath, LPDWORD pcchPath, DWORD dwFlags);

	#ifdef	UNICODE
		#define				PathCreateFromUrl	PathCreateFromUrlW
	#else
		#define				PathCreateFromUrl	PathCreateFromUrlA
	#endif
#endif

#pragma	comment(lib, "shlwapi.lib")

////
//	*******************************************************************************
//	PathCreateFromUrl
//	Create	:	2026-05-15
//	*******************************************************************************
inline	tstring	PathCreateFromUrl	(const tstring& url)
{
	DWORD	dw_size = MAX_PATH ;
	tstring	dos_path ;	dos_path.resize(dw_size,0) ;
	::PathCreateFromUrl(url.c_str(),&dos_path[0],&dw_size,0) ;
	return	tstring(dos_path.c_str()) ;
	}

