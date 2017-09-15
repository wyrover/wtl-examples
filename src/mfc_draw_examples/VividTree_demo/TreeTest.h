///////////////////////////////////////////////////////////////////////////
// CTreeTestApp.h : Definition of Class CTreeTestApp
///////////////////////////////////////////////////////////////////////////
//
// Copyright(C) 2005 Jim Alsup  All rights reserved
//
// License: You may use, or derive works from this file without any
//          restrictions except those listed below.
//
//        - This original header must be kept in the derived work.
//
//        - If your derived work is distributed in any form, you must notify
//          the author via the email address above and provide a short
//          description of the product and intended audience.  Offering
//          the author a free licensed copy of the product is not required,
//          but does endear you with good karma points.
//
///////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CTreeTestApp:
// See TreeTest.cpp for the implementation of this class
//

class CTreeTestApp : public CWinApp
{
public:
    CTreeTestApp();

// Overrides
public:
    virtual BOOL InitInstance();

// Implementation

    DECLARE_MESSAGE_MAP()
};

extern CTreeTestApp theApp;