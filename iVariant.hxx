// **************************************************************************
//  @file       IVARIANT.HXX
//  @brief      VARIANT Helper
//
//  @author     Iwao (https://mish.work/)
//  @date       2026-05-18
//
//  @modify
//  2016-05-06  Newly created
//  2026-05-12  add copy VARIANT , tstring
//  2026-05-18  modify operator tstring
//
//  @disclaimer
//  The author is not responsible for any damage caused by using this code.
//  Please specify the above URL when quoting.
//
//  (C) 2016 Iwao. All Rights Reserved.
// **************************************************************************

#pragma		once

#include	<Windows.h>
#include	<comdef.h>
#include	"tstrmbwc.hxx"

////
//	*******************************************************************************
//	VARIANT Helper
//	Create	:	2016-05-06
//	Modify	:	2026-05-12	add copy VARIANT , tstring
//	Modify	:	2026-05-18	operator tstring
//	*******************************************************************************
class	i_VARIANT	:	public	VARIANT	//	tagVARIANT
{
public:
				i_VARIANT	()						{	::VariantInit(this)	;	}
				~i_VARIANT	()						{	Clear() ;				}
public:
	HRESULT		Clear		(void)					{	return	::VariantClear(this) ;	}
public:
				i_VARIANT	(long src)				{	::VariantInit(this) ;	vt = VT_I4 ;	lVal = src ;					}
	i_VARIANT&	operator=	(long src)				{	Clear() ;				vt = VT_I4 ;	lVal = src ;	return	*this ;	}
public:
				i_VARIANT	(IDispatch*src)			{	::VariantInit(this) ;	vt = VT_DISPATCH ;	pdispVal = src ;
														if (pdispVal != NULL) {	pdispVal->AddRef();	}							}
	i_VARIANT&	operator=	(IDispatch*src)			{	Clear() ;				vt = VT_DISPATCH ;	pdispVal = src ;
														if (pdispVal != NULL) {	pdispVal->AddRef();	}
																												return	*this ;	}
public:
				i_VARIANT	(LPCTSTR src)			{	::VariantInit(this) ;	vt = VT_BSTR ;
														std::wstring	tmp = ::To_wstring(src) ;
														bstrVal = ::SysAllocString(tmp.c_str()) ;								}
	i_VARIANT&	operator=	(LPCTSTR src)			{	Clear() ;				vt = VT_BSTR ;
														std::wstring	tmp = ::To_wstring(src) ;
														bstrVal = ::SysAllocString(tmp.c_str()) ;				return	*this ;	}

public:
				i_VARIANT	(const VARIANT& src)	{	::VariantInit(this) ;
														::VariantCopy(this,(VARIANT*)&src) ;									}
	i_VARIANT&	operator=	(const VARIANT& src)	{	Clear() ;
														::VariantCopy(this,(VARIANT*)&src) ;					return	*this ;	}

public:
/*
				operator	tstring	()	const		{
		_bstr_t	b(vt == VT_BSTR ? bstrVal : NULL) ;
		return	tstring((LPCTSTR)b) ;
		}
*/
				operator	tstring()	const		{
		try {
			_variant_t var(*const_cast<tagVARIANT*>(static_cast<const tagVARIANT*>(this)), false);
			_bstr_t bstr(var);
			return tstring((LPCTSTR)bstr);
			}
		catch (...) {
			return _T("");
			}
		}

	} ;
