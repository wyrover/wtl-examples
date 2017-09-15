//
// StyleEnum.h: enumerated types for the Style Toolkit
//
// Author:  Darren Sessions
//
// History
//     Version 1.1 - 2008 August 1
//     - More features added
//
//     Version 1.0 - 2008 June 24
//     - Initial public release
//
// License:
//     This software is released under the Code Project Open License (CPOL),
//     which may be found here:  http://www.codeproject.com/info/eula.aspx
//     You are free to use this software in any way you like, except that you
//     may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

enum LayerTypes {
    // fill types
    SOLID           = 0,
    RADIAL,
    BIGRAD,
    TRIGRAD,
    WRAP,

    // special case types
    IMAGE,
    STRING,
    EFFECTSTRING,
    REGIONBLUR,
    SETSMOOTH,
    RESTORESMOOTH,
    APPLYXFORM,

    // some edge functions
    TOP_EDGE,
    LEFT_EDGE,
    RIGHT_EDGE,
    BOTTOM_EDGE,
    TOP_EDGE_BEVEL,
    LEFT_EDGE_BEVEL,
    RIGHT_EDGE_BEVEL,
    BOTTOM_EDGE_BEVEL,

    // region and clip types
    CREATERGN,
    COMBINEMOD,
    COMBINENEW,
    APPLYCLIP,
    RESTORECLIP
};

// border styles
enum LayerShapes {
    UNDEFINED   = 0,
    RECTANGLE,
    ROUNDRECT,
    ELLIPSE,
    TRANSITION
};

// gradient styles, these map to GDI+ LinearGradientMode
enum GradientStyles {
    HORIZ   = 0,    // horizontal gradient
    VERT    = 1,    // vertical gradient
    DIAGF   = 2,    // forward diagonal gradient = ul -> br
    DIAGB   = 3     // backward diagonal gradient = ur -> bl
};

// font styles, these map to GDI+ FontStyle
enum FontStyles {
    FONT_REG        = 0,
    FONT_BOLD       = 1,
    FONT_ITALIC     = 2,
    FONT_BOLDITALIC = 3,
    FONT_UNDERLINE  = 4,
    FONT_STRIKEOUT  = 8
};

// clip types, these map to GDI+ CombineMode
enum ClipTypes {
    REPLACE         = 0,
    INTERSECT       = 1,
    UNION           = 2,
    XOR             = 3,
    EXCLUDE         = 4,
    COMPLEMENT      = 5
};

// string alignment modes, the first 3 map to GDI+ StringAlignment
enum StringAlign {
    ALIGN_NEAR              = 0,        // StringAlignmentNear = 0,
    ALIGN_CENTER            = 1,        // StringAlignmentCenter = 1,
    ALIGN_FAR               = 2,        // StringAlignmentFar = 2
};

// wrap modes, these map to GDI+ WrapMode
enum WrapModes {
    TILE    = 0,
    FLIPX   = 1,
    FLIPY   = 2,
    FLIPXY  = 3,
    CLAMP   = 4
};

// smoothing modes, these map to GDI+ SmoothingMode
enum SmoothModes {
    INVALID     = -1,
    DEFAULT     = 0,
    HIGHSPEED   = 1,
    HIGHQUALITY = 2,
    NONE        = 3,
    ANTIALIAS   = 4,
};

// transformations
enum LayerXForms {
    NOXFORM     = 0,
    LIGHTEN,
    GRAYSCALE
};

enum StringEffects {
    OUTLINE,
};
