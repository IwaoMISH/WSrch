; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CWSrchDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WSrch.h"

ClassCount=3
Class1=CWSrchApp
Class2=CWSrchDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_WSRCH_DIALOG

[CLS:CWSrchApp]
Type=0
HeaderFile=WSrch.h
ImplementationFile=WSrch.cpp
Filter=N

[CLS:CWSrchDlg]
Type=0
HeaderFile=WSrchDlg.h
ImplementationFile=WSrchDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST_RESULTS

[CLS:CAboutDlg]
Type=0
HeaderFile=WSrchDlg.h
ImplementationFile=WSrchDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WSRCH_DIALOG]
Type=1
Class=CWSrchDlg
ControlCount=5
Control1=IDC_COMBO_EXT,combobox,1344342338
Control2=IDC_EDIT_KEYWORD,edit,1350631552
Control3=IDC_LIST_RESULTS,SysListView32,1350631425
Control4=IDOK,button,1342177281
Control5=IDCANCEL,button,1073741824

