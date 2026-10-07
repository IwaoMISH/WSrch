// **************************************************************************
//  @file       WINSTORE.INC
//  @brief      Utility functions for window placement (Save/Restore)
//
//  @author     Iwao (https://mish.work/)
//  @date       2026-05-19
//
//  @modify
//  2026-02-05  Newly created by AI assistant
//  2026-02-08  Added VC6 compatibility and multi-monitor safety
//  2026-02-18  default section
//  2026-05-19  Fixed VC6 build errors by adding multimon.h support
//
//  @disclaimer
//  The author is not responsible for any damage caused by using this code.
//  Please specify the above URL when quoting.
//
//  (C) 2026 Iwao. All Rights Reserved.
// **************************************************************************

#pragma once

#include <afxwin.h>

#if _MSC_VER <= 1200
    #ifndef 	COMPILE_MULTIMON_STUBS
        #define COMPILE_MULTIMON_STUBS
    #endif

    #include <multimon.h>

    #ifndef 	MONITOR_DEFAULTTONULL
        #define MONITOR_DEFAULTTONULL 0x00000000
    #endif
#endif

////
// **************************************************************************
//  Common section name for registry/ini storage
//  Create    :    2026-02-18
// **************************************************************************
static LPCTSTR const SEC_WIN_POS      = _T("WindowPos");
static LPCTSTR const SEC_WIN_POS_MAIN = _T("WindowPos") _T("\\") _T("Main");

////
// **************************************************************************
//  Save window position and state to registry
//  Create    :    2026-02-05
//  Modify    :    2026-02-08
//  Modify    :    2026-02-18  default section
// **************************************************************************
inline void SaveWindowPosition(CWnd* pWnd, LPCTSTR lpszSection = SEC_WIN_POS_MAIN)
{
    if (pWnd == NULL || !::IsWindow(pWnd->m_hWnd))    {
        return ;
	    }

    WINDOWPLACEMENT wp ;
    // ZeroMemory is essential for compatibility with VC6 and older SDKs
    ::ZeroMemory(&wp, sizeof(WINDOWPLACEMENT)) ;
    wp.length = sizeof(WINDOWPLACEMENT) ;

    if (pWnd->GetWindowPlacement(&wp))    {
        CWinApp* pApp = ::AfxGetApp() ;
        if (pApp)        {
            // Use explicit casts to int for VC6 WriteProfileInt compatibility
            pApp->WriteProfileInt(lpszSection, _T("left"),   (int)wp.rcNormalPosition.left) ;
            pApp->WriteProfileInt(lpszSection, _T("top"),    (int)wp.rcNormalPosition.top) ;
            pApp->WriteProfileInt(lpszSection, _T("right"),  (int)wp.rcNormalPosition.right) ;
            pApp->WriteProfileInt(lpszSection, _T("bottom"), (int)wp.rcNormalPosition.bottom) ;
            pApp->WriteProfileInt(lpszSection, _T("show"),   (int)wp.showCmd) ;
	        }
	    }
	}

////
// **************************************************************************
//  Restore window position and state from registry
//  Create    :    2026-02-05
//  Modify    :    2026-02-08
// **************************************************************************
inline void RestoreWindowPosition(CWnd* pWnd, LPCTSTR lpszSection = SEC_WIN_POS_MAIN)
{
    if (pWnd == NULL || !::IsWindow(pWnd->m_hWnd))    {
        return ;
	    }

    CWinApp* pApp = ::AfxGetApp() ;
    if (!pApp)    {
        return ;
	    }

    // Retrieve values with default -1 to check if registry entries exist
    int left   = pApp->GetProfileInt(lpszSection, _T("left"),   -1) ;
    int top    = pApp->GetProfileInt(lpszSection, _T("top"),    -1) ;
    int right  = pApp->GetProfileInt(lpszSection, _T("right"),  -1) ;
    int bottom = pApp->GetProfileInt(lpszSection, _T("bottom"), -1) ;
    int show   = pApp->GetProfileInt(lpszSection, _T("show"),   SW_SHOWNORMAL) ;

    if (left != -1 && top != -1 && right != -1 && bottom != -1)    {
        RECT    rc ;
        ::SetRect(&rc, left, top, right, bottom) ;

        // Check if the saved rectangle is visible on any monitor.
        // If not, the window will be shown on the primary monitor.
        HMONITOR hMonitor = ::MonitorFromRect(&rc, MONITOR_DEFAULTTONULL) ;

        WINDOWPLACEMENT wp ;
        ::ZeroMemory(&wp, sizeof(WINDOWPLACEMENT)) ;
        wp.length = sizeof(WINDOWPLACEMENT) ;

        wp.showCmd                    = (UINT)show ;
        wp.rcNormalPosition           = rc ;

        if (hMonitor != NULL)        {
            pWnd->SetWindowPlacement(&wp) ;
	        }
        else        {
            // If the saved position is off-screen, fallback to default show command.
            pWnd->ShowWindow(show) ;
	        }
	    }
	}

