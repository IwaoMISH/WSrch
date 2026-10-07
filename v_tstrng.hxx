//	*******************************************************************************
//	Name	:	v_tstrng.hxx
//			:	define vector<tstring>
//	Author	:	I. Nakagawa
//	Create	:	2013/03/06
//	Modify	:	2014/06/20
//	*******************************************************************************

#pragma		once

#include	"tstring.hxx"
#include	"i_vector.hxx"

typedef				std::vector<tstring>		  v_tstring ;
typedef		const	std::vector<tstring>		c_v_tstring ;

typedef				std::vector<v_tstring>		  vv_tstring ;
typedef		const	std::vector<v_tstring>		c_vv_tstring ;

