; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVanillaSkyDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "VanillaSky.h"

ClassCount=4
Class1=CVanillaSkyApp
Class2=CVanillaSkyDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_VANILLASKY_DIALOG
Class4=CSkyMenu
Resource4=IDR_MENU1

[CLS:CVanillaSkyApp]
Type=0
HeaderFile=VanillaSky.h
ImplementationFile=VanillaSky.cpp
Filter=N
LastObject=CVanillaSkyApp

[CLS:CVanillaSkyDlg]
Type=0
HeaderFile=VanillaSkyDlg.h
ImplementationFile=VanillaSkyDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CVanillaSkyDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=VanillaSkyDlg.h
ImplementationFile=VanillaSkyDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDOK

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_VANILLASKY_DIALOG]
Type=1
Class=CVanillaSkyDlg
ControlCount=1
Control1=IDC_STATICCOUNT,static,1342308354

[MNU:IDR_MENU1]
Type=1
Class=CSkyMenu
Command1=IDD_ABOUTBOX
Command2=IDM_ABOUTBOX
CommandCount=2

[CLS:CSkyMenu]
Type=0
HeaderFile=SkyMenu.h
ImplementationFile=SkyMenu.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSkyMenu

