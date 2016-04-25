/*-------------------------------------------------------------------------*/
/* menus.h								   */
/* Copyright (c) 2002  Tim Edwards, Johns Hopkins University        	   */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/* Note:  underscore (_) before name denotes a color to paint the button.  */
/*	  colon (:) before name denotes a stipple, defined by the data	   */
/*		    passed to setfill().				   */
/*-------------------------------------------------------------------------*/
/* Things commented out here are reminders of future implementations. */

#include <cstddef>
#include "menus.h"
#include "prototypes.h"
#include "pixmaps.h"
#include "xcircuit.h"

#define submenu(a)	a, (sizeof (a) / sizeof(menustruct)), \
                        DoNothing, NULL
#define action(b,c)	NULL, 0, b, c  // regular action
#define setaction(b,c)	NULL, 1, b, c  // checkable action, set by default
#define ckaction(b,c)  NULL, -1, b, c  // checkable action, not set
#define toolaction(b,c) b, c
#define noaction	NULL, 0, DoNothing, NULL
#define offset(a)	Number(offsetof(XCWindowData, a))
#define sentinel        {NULL, NULL, 0, NULL, NULL}

/* Integers and constants are passed using the Number() macro -- it wraps them
   into a pointer type expected in action callbacks. */

/* Each menu must have a sentinel at the end, this is for the menu creation
   code to know where each menu ends. */

static menustruct Fonts[] = {
        {"Add New Font", action(addnewfont, NULL)},
        {" ", noaction},
        sentinel
};

static menustruct FontStyles[] = {
        {"Normal", setaction(fontstyle, Number(0))},
        {"Bold", ckaction(fontstyle, Number(1))},
        {"Italic", ckaction(fontstyle, Number(2))},
        {"BoldItalic", ckaction(fontstyle, Number(3))},
        {" ", noaction},
        {"Subscript", action(addtotext, Number(SUBSCRIPT))},
        {"Superscript", action(addtotext, Number(SUPERSCRIPT))},
        {"Normalscript", action(addtotext, Number(NORMALSCRIPT))},
        {" ", noaction},
        {"Underline", action(addtotext, Number(UNDERLINE))},
        {"Overline", action(addtotext, Number(OVERLINE))},
        {"No line", action(addtotext, Number(NOLINE))},
        sentinel
};

static menustruct FontEncodings[] = {
        {"Standard", setaction(fontencoding, Number(0))},
        {"ISO-Latin1", ckaction(fontencoding, Number(2))},
        sentinel
};

static menustruct TextSpacing[] = {
        {"Tab stop", action(addtotext, Number(TABSTOP))},
        {"Tab forward", action(addtotext, Number(TABFORWARD))},
        {"Tab backward", action(addtotext, Number(TABBACKWARD))},
        {"Carriage Return", action(addtotext, Number(RETURN))},
        {"1/2 space", action(addtotext, Number(HALFSPACE))},
        {"1/4 space", action(addtotext, Number(QTRSPACE))},
        {"Kern", action(getkern, NULL)},
        {"Character", action(addtotext, Number(SPECIAL))},
        sentinel
};

static menustruct Justifs[] = {
        {"Left Justified", setaction(sethjust, Number(NORMAL))},
        {"Center Justified", ckaction(sethjust, Number(NOTLEFT))},
        {"Right Justified", ckaction(sethjust, Number(NOTLEFT | RIGHT))},
        {" ", noaction},
        {"Top Justified", ckaction(setvjust, Number(NOTBOTTOM | TOP))},
        {"Middle Justified", ckaction(setvjust, Number(NOTBOTTOM))},
        {"Bottom Justified", setaction(setvjust, Number(NORMAL))},
        {" ", noaction},
        {"Flip Invariant", setaction(setjustbit, Number(FLIPINV))},
        sentinel
};

static menustruct BoxEditStyles[] = {
        {"Manhattan Box Edit", setaction(boxedit, Number(MANHATTAN))},
        {"Rhomboid X", ckaction(boxedit, Number(RHOMBOIDX))},
        {"Rhomboid Y", ckaction(boxedit, Number(RHOMBOIDY))},
        {"Rhomboid A", ckaction(boxedit, Number(RHOMBOIDA))},
        {"Normal", ckaction(boxedit, Number(NORMAL))},
        sentinel
};

static menustruct GridStyles[] = {
        {"Decimal Inches", ckaction(getgridtype, Number(DEC_INCH))},
        {"Fractional Inches", setaction(getgridtype, Number(FRAC_INCH))},
        {"Centimeters", ckaction(getgridtype, Number(CM))},
        {" ", noaction},
        {"Drawing Scale", action(getdscale, NULL)},
        sentinel
};

static menustruct Libraries[] = {
        {"Add New Library", action(newlibrary, NULL)},
        {" ", noaction},
        {"User Library", action(startcatalog, Number(LIBRARY))},
        sentinel
};

static menustruct Pages[] = {
        {"Add New Page", action(newpagemenu, Number(255))},
        {" ", noaction},
        {"Page 1", action(newpagemenu, Number(0))},
        {"Page 2", action(newpagemenu, Number(1))},
        {"Page 3", action(newpagemenu, Number(2))},
        {"Page 4", action(newpagemenu, Number(3))},
        {"Page 5", action(newpagemenu, Number(4))},
        {"Page 6", action(newpagemenu, Number(5))},
        {"Page 7", action(newpagemenu, Number(6))},
        {"Page 8", action(newpagemenu, Number(7))},
        {"Page 9", action(newpagemenu, Number(8))},
        {"Page 10", action(newpagemenu, Number(9))},
        sentinel
};

static menustruct BorderStyles[] = {
        {"Linewidth", action(getwwidth, NULL)},
        {" ", noaction},
        {"Solid", setaction(setline, Number(NORMAL))},
        {"Dashed", ckaction(setline, Number(DASHED))},
        {"Dotted", ckaction(setline, Number(DOTTED))},
        {"Unbordered", ckaction(setline, Number(NOBORDER))},
        {" ", noaction},
        {"Closed", ckaction(setclosure, Number(UNCLOSED))},
        {"Bounding Box", ckaction(makebbox, Number(BBOX))},
        sentinel
};

static menustruct Colors[] = {
        {"Add New Color", action(addnewcolor, NULL)},
        {" ", noaction},
        {"Inherit Color", setaction(setcolor, Number(1))},
        {"_Black", ckaction(setcolor, NULL)},
        {"_White", ckaction(setcolor, NULL)},
        sentinel
};

static menustruct Parameterize[] = {
        {"Substring", action(promptparam, NULL)},
        {"Numeric", action(startparam, Number(P_NUMERIC))},
        {"Style", action(startparam, Number(P_STYLE))},
        {"Justification", action(startparam, Number(P_JUSTIFY))},
        {"Start Angle", action(startparam, Number(P_ANGLE1))},
        {"End Angle", action(startparam, Number(P_ANGLE2))},
        {"Radius", action(startparam, Number(P_RADIUS))},
        {"Minor Axis", action(startparam, Number(P_MINOR_AXIS))},
        {"Rotation", action(startparam, Number(P_ROTATION))},
        {"Scale", action(startparam, Number(P_SCALE))},
        {"Linewidth", action(startparam, Number(P_LINEWIDTH))},
        {"Color", action(startparam, Number(P_COLOR))},
        {"Position", action(startparam, Number(P_POSITION))},
        sentinel
};

static menustruct Stipples[] = {
        {":Black",  ckaction(setfill, Number(OPAQUE | FILLED | FILLSOLID))},
        {":Gray12", ckaction(setfill, Number(OPAQUE | FILLED | STIP2 | STIP1))},
        {":Gray25", ckaction(setfill, Number(OPAQUE | FILLED | STIP2 | STIP0))},
        {":Gray37", ckaction(setfill, Number(OPAQUE | FILLED | STIP2))},
        {":Gray50", ckaction(setfill, Number(OPAQUE | FILLED | STIP0 | STIP1))},
        {":Gray62", ckaction(setfill, Number(OPAQUE | FILLED | STIP1))},
        {":Gray75", ckaction(setfill, Number(OPAQUE | FILLED | STIP0))},
        {":Gray87", ckaction(setfill, Number(OPAQUE | FILLED))},
        {":White", setaction(setfill, Number(FILLSOLID))},
        {" ", noaction},
        {"Opaque", ckaction(setopaque, Number(OPAQUE))},
        {"Transparent", setaction(setopaque, Number(NORMAL))},
        sentinel
};

static menustruct TextMenu[] = {
        {"Text Size", action(gettsize, NULL)},
        {"Font", submenu(Fonts)},
        {"Style", submenu(FontStyles)},
        {"Encoding", submenu(FontEncodings)},
        {"Insert", submenu(TextSpacing)},
        {"Justification (keypad)", submenu(Justifs)},
        {"Parameterize", action(promptparam, NULL)},
        {"Unparameterize", action(startunparam, Number(P_SUBSTRING))},
        {" ", noaction},
        {"Set LaTeX Mode", ckaction(setjustbit, Number(LATEXLABEL))},
        {" ", noaction},
        {"Make Label (t)", action(changetool, Number(XCF_Text))},
        sentinel
};

static menustruct PolyMenu[] = {
        {"Border", submenu(BorderStyles)},
        {"Fill", submenu(Stipples)},
        {"Color", submenu(Colors)},
        {" ", noaction},
        {"Object size", action(getosize, NULL)},
        {"Parameters", submenu(Parameterize)},
        {"Center Object", setaction(toggle, offset(center))},
        {"Manhattan Draw", ckaction(toggle, offset(manhatn))},
        {"Polygon Edit", submenu(BoxEditStyles)},
        sentinel
};

static menustruct FilterMenu[] = {
        {"Labels", setaction(selectfilter, Number(LABEL))},
        {"Objects", setaction(selectfilter, Number(OBJINST))},
        {"Polygons", setaction(selectfilter, Number(POLYGON))},
        {"Arcs", setaction(selectfilter, Number(ARC))},
        {"Splines", setaction(selectfilter, Number(SPLINE))},
        {"Paths", setaction(selectfilter, Number(PATH))},
        sentinel
};

static menustruct RotateMenu[] = {
        {"Flip Horizontal (f)", action(exec_or_changetool, Number(XCF_Flip_X))},
        {"Flip Vertical (F)", action(exec_or_changetool, Number(XCF_Flip_Y))},
        {" ", noaction},
        {"Rotate CW 90", action(rotatetool, Number(90))},
        {"Rotate CW 45", action(rotatetool, Number(45))},
        {"Rotate CW 30", action(rotatetool, Number(30))},
        {"Rotate CW 15 (r)", action(rotatetool, Number(15))},
        {"Rotate CW 5 (o)", action(rotatetool, Number(3))},
        {"Rotate CW 1", action(rotatetool, Number(1))},
        {" ", noaction},
        {"Rotate CCW 90", action(rotatetool, Number(-90))},
        {"Rotate CCW 45", action(rotatetool, Number(-45))},
        {"Rotate CCW 30", action(rotatetool, Number(-30))},
        {"Rotate CCW 15 (R)", action(rotatetool, Number(-15))},
        {"Rotate CCW 5 (O)", action(rotatetool, Number(-5))},
        {"Rotate CCW 1", action(rotatetool, Number(-1))},
        sentinel
};

static menustruct LineMenu[] = {
        {"Global Linewidth", action(getwirewidth, NULL)},
        {"Wire Linewidth", action(getwwidth, NULL)},
        sentinel
};

static menustruct GridMenu[] = {
        {"Grid", setaction(toggle, offset(gridon))},
        {"Axes", setaction(toggle, offset(axeson))},
        {"Grid spacing", action(getgridspace, NULL)},
        {"Grid type/display", submenu(GridStyles)},
        sentinel
};

static menustruct SnapMenu[] = {
        {"Snap-to", setaction(toggle, offset(snapto))},
        {"Snap spacing", action(getsnapspace, NULL)},
        sentinel
};

static menustruct PinConvert[] = {
        {"Normal label", action(dopintype, Number(NORMAL))},
        {"Local Pin", action(dopintype, Number(LOCAL))},
        {"Global Pin", action(dopintype, Number(GLOBAL))},
        {"Info label", action(dopintype, Number(INFO))},
        sentinel
};

static menustruct SchemaMenu[] = {
        {"Make Pin (T)", action(changetool, Number(XCF_Pin_Label))},
        {"Make Info Pin (I)", action(changetool, Number(XCF_Info_Label))},
        {"Make Global Pin (G)", action(changetool, Number(XCF_Pin_Global))},
        {"Convert Label to...", submenu(PinConvert)},
        {"Pin Visibility", action(setpinjustbit, Number(PINVISIBLE))},
/*	{"Make Object Non-Schematic", action(maketrivial, NULL)}, */
        {"Make Matching Symbol", action(dobeforeswap, NULL)},
        {"Associate with Symbol", action(startschemassoc, Number(1))},
        {"Highlight Connectivity", action(startconnect, NULL)},
        {"Auto-number Components", action(callwritenet, Number(4))},
        {" ", noaction},
        {"Write spice", action(callwritenet, Number(0))},
        {"Write flattened spice", action(callwritenet, Number(3))},
        {"Write sim", action(callwritenet, Number(1))},
        {"Write pcb", action(callwritenet, Number(2))},
        sentinel
};

static menustruct WindowMenu[] = {
        {"Zoom In (Z)", action(zoomin_call, NULL)},
        {"Zoom Out (z)", action(zoomout_call, NULL)},
        {"Full View (v)", action(zoomview, NULL)},
        {"Pan (p)", action(pantool, Number(6))},
        {"Refresh ( )", action(refresh, NULL)},
        {" ", noaction},
        {"Library Directory (L)", action(startcatalog, Number(LIBLIB))},
        {"Goto Library", submenu(Libraries)},
        {" ", noaction},
        {"Page Directory (P)", action(startcatalog, Number(PAGELIB))},
        {"Goto Page", submenu(Pages)},
        sentinel
};

static menustruct FileMenu[] = {
#ifdef XC_WIN32
        {"New window", action(win32_new_window, NULL)},
        {" ", noaction},
#endif
        {"Read Xcircuit File", action(getfile, Number(NORMAL))},
        {"Import Xcircuit PS", action(getfile, Number(IMPORT))},
        {"Import background PS", action(getfile, Number(PSBKGROUND))},
#ifdef ASG
        {"Import SPICE deck", action(getfile, Number(IMPORTSPICE))},
#endif
        {"Execute script", action(getfile, Number(SCRIPT))},
        {"Write Xcircuit PS (W)", action(outputpopup, NULL)},
        {" ", noaction},
        {"Add To Library", action(getlib, NULL)},
        {"Load New Library", action(getuserlib, NULL)},
        {"Save Library", action(savelibpopup, NULL)},
        {" ", noaction},
        {"Clear Page", action(resetbutton, Number(0))},
        {" ", noaction},
        {"Quit", action(quitcheck, NULL)},
        sentinel
};

static menustruct OptionMenu[] = {
        {"Alt Colors", ckaction(inversecolor, offset(invert))},
        {"Show Bounding box", ckaction(toggle, offset(bboxon))},
        {"Edit in place", setaction(toggle, offset(editinplace))},
        {"Show Pin Positions", ckaction(toggle, offset(pinpointon))},
        {"Antialias", ckaction(toggle, offset(antialias))},
        {"Disable Toolbar", action(dotoolbar, NULL)},
        {"Grid", submenu(GridMenu)},
        {"Snap-to", submenu(SnapMenu)},
        {"Linewidth", submenu(LineMenu)},
        {"Elements", submenu(PolyMenu)},
        {" ", noaction},
        {"Help!", action(starthelp, NULL)},
        sentinel
};

static menustruct EditMenu[] = {
        {"Undo (u)", action(undo_call, NULL)},
        {"Redo (U)", action(redo_call, NULL)},
        {" ", noaction},
        {"Delete (d)", action(exec_or_changetool, Number(XCF_Delete))},
        {"Copy (c)", action(exec_or_changetool, Number(XCF_Copy))},
        {"Edit (e)", action(exec_or_changetool, Number(XCF_Edit))},
        {"Rotate/Flip", submenu(RotateMenu)},
        {"Deselect (x)", action(startdesel, NULL)},
        {"Select filter", submenu(FilterMenu)},
        {"Push selected (>)", action(exec_or_changetool, Number(XCF_Push))},
        {"Pop hierarchy (<)", action(popobject, Number(0))},
        {" ", noaction},
        {"Make User Object (m)", action(selectsave, NULL)},
        {"Make Arc (a)", action(changetool, Number(XCF_Arc))},
        {"Make Box (b)", action(changetool, Number(XCF_Box))},
        {"Make Spline (s)", action(changetool, Number(XCF_Spline))},
        {"Join (j)", action(join_call, NULL)},
        sentinel
};

menustruct TopButtons[] = {
        {"File", submenu(FileMenu)},
        {"Edit", submenu(EditMenu)},
        {"Text", submenu(TextMenu)},
        {"Options", submenu(OptionMenu)},
        {"Window", submenu(WindowMenu)},
        {"Netlist", submenu(SchemaMenu)},
        sentinel
};

/* Toolbar buttons */
toolbarstruct ToolBar[] = {
        {"Pan",	   pn_xpm,  toolaction(pantool, Number(6)),
                "pan mode"},
        {"Wire",   w_xpm,  toolaction(changetool, Number(XCF_Wire)),
                "draw wire"},
        {"Box",    b_xpm,  toolaction(changetool, Number(XCF_Box)),
                "draw box"},
        {"Arc",    a_xpm,  toolaction(changetool, Number(XCF_Arc)),
                "draw arc"},
        {"Spline", s_xpm,  toolaction(changetool, Number(XCF_Spline)),
                "draw spline"},
        {"Text",   t_xpm,  toolaction(changetool, Number(XCF_Text)),
                "enter text"},
        {"Move",   mv_xpm, toolaction(exec_or_changetool, Number(XCF_Move)),
                "move element"},
        {"Copy",   cp_xpm, toolaction(exec_or_changetool, Number(XCF_Copy)),
                "copy element"},
        {"Edit",   e_xpm,  toolaction(exec_or_changetool, Number(XCF_Edit)),
                "edit element"},
        {"Delete", d2_xpm, toolaction(exec_or_changetool, Number(XCF_Delete)),
                "delete element"},
        {"RotP",   cw_xpm, toolaction(rotatetool, Number(15)),
                "rotate 15 degrees clockwise"},
        {"RotN",  ccw_xpm, toolaction(rotatetool, Number(-15)),
                "rotate 15 degrees counterclockwise"},
        {"HFlip",  fx_xpm, toolaction(exec_or_changetool, Number(XCF_Flip_X)),
                "flip horizontal"},
        {"VFlip",  fy_xpm, toolaction(exec_or_changetool, Number(XCF_Flip_Y)),
                "flip vertical"},
        {"Push",  pu2_xpm, toolaction(exec_or_changetool, Number(XCF_Push)),
                "push (edit object)"},
        {"Pop",   po2_xpm, toolaction(popobject, Number(0)),
                "pop (return from object edit)"},
        {"Make",   mk_xpm, toolaction(selectsave, NULL),
                "make an object from selected elements"},
        {"Join",   pz_xpm, toolaction(join_call, NULL),
                "join elements into polygon or path"},
        {"Unjoin", uj_xpm, toolaction(unjoin_call, NULL),
                "separate path into elements"},
        {"Colors", co_xpm, toolaction(color_popup, NULL),
                "set color"},
        {"Border", bd_xpm, toolaction(border_popup, NULL),
                "set border and line properties"},
        {"Fills",  fi_xpm, toolaction(fill_popup, NULL),
                "set fill properties"},
        {"Parameters", pm_xpm,  toolaction(param_popup, NULL),
                "parameterize properties"},
        {"Library",li_xpm, toolaction(changecat_call, NULL),
                "go to next library"},
        {"Libdir", yp_xpm, toolaction(startcatalog, Number(LIBLIB)),
                "go to library directory"},
        {"Pagedir",pl_xpm, toolaction(startcatalog, Number(PAGELIB)),
                "go to page directory"},
        {"ZoomI",  z4_xpm, toolaction(zoomin_call, NULL),
                "zoom in"},
        {"ZoomO",  z5_xpm, toolaction(zoomout_call, NULL),
                "zoom out"},
        {"Help",   i_xpm,  toolaction(starthelp, NULL),
                "pop up help window"},
        {NULL, NULL, NULL, NULL, NULL}
};

/*-------------------------------------------------------------------------*/