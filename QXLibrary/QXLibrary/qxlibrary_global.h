#pragma once



#include <QtCore/qglobal.h>

#include <QFile>
#include <QtWidgets/QtWidgets>
//高版本下要加
//Qt5WindowsUIAutomationSupport.lib

#ifdef WIN32
#include <Qt4Qt5/Qsci/qsciscintilla.h>
#include <QtUiTools/QUiLoader>
#include "../../../../../../xcross/xcross/xnl.h"
#include "../../../../../thirds/qtPropertyBrowser/QtPropertyBrowser-master/src/qtvariantproperty.h"
#include "../../../../../thirds/qtPropertyBrowser/QtPropertyBrowser-master/src/qtvariantproperty.h"
#include "../../../../../thirds/qtPropertyBrowser/QtPropertyBrowser-master/src/qtpropertymanager.h"
#include "../../../../../thirds/qtPropertyBrowser/QtPropertyBrowser-master/src/qteditorfactory.h"
#include "../../../../../thirds/qtPropertyBrowser/QtPropertyBrowser-master/src/qttreepropertybrowser.h"
#elif defined(__linux__)
#include <Qt4Qt5/Qsci/qsciscintilla.h>
#include <QtUiTools/QUiLoader>
#include "../../../../../../xcross/xcross/xnl.h"
#include "../../../../../thirds/qtPropertyBrowser/QtPropertyBrowser-master/src/qtvariantproperty.h"
#include "../../../../../thirds/qtPropertyBrowser/QtPropertyBrowser-master/src/qtpropertymanager.h"
#include "../../../../../thirds/qtPropertyBrowser/QtPropertyBrowser-master/src/qteditorfactory.h"
#include "../../../../../thirds/qtPropertyBrowser/QtPropertyBrowser-master/src/qttreepropertybrowser.h"
#elif defined(__APPLE__)
#include <QtUiTools/QUiLoader>
#include "../../../../../xcross/xnl.h"
#include "../../../../../thirds/qScintilla_gpl-2.10.7/QScintilla_gpl-2.10.7/Qt4Qt5/Qsci/qsciscintilla.h"
#include "../../../../../thirds/qtPropertyBrowser/QtPropertyBrowser-master/src/qtvariantproperty.h"
#include "../../../../../thirds/qtPropertyBrowser/QtPropertyBrowser-master/src/qtpropertymanager.h"
#include "../../../../../thirds/qtPropertyBrowser/QtPropertyBrowser-master/src/qteditorfactory.h"
#include "../../../../../thirds/qtPropertyBrowser/QtPropertyBrowser-master/src/qttreepropertybrowser.h"
#endif

/*#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG  
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)  
#endif  */

extern XNLEnv * gs_env ;
extern XContext * ui_thread;
extern bool ui_release;
extern Qt::HANDLE ui_thread_id;

class XThread {
	XContext * thread;
	bool release;
public:

	XThread() {
		release = 0;
		if (QThread::currentThreadId() == ui_thread_id) {
			thread = ui_thread;
			//gs_env->throwNativeException(ui_thread, "Current thread is not the UI thread");
		}else {
			thread = gs_env->getContext(&release);
		}
	}

	~XThread() {
		if (release) {
			gs_env->releaseContext(thread);
		}
	}

	XContext * getThread() {
		return thread;
	}
};

#include <QtWidgets/QApplication>
#include "qtype.h"

#ifndef BUILD_STATIC
# if defined(QXLIBRARY_LIB)
#  define QXLIBRARY_EXPORT Q_DECL_EXPORT
# else
#  define QXLIBRARY_EXPORT Q_DECL_IMPORT
# endif
#else
# define QXLIBRARY_EXPORT
#endif



#ifndef WIN32
template<class T>
size_t _countof_heaper(T  arr_[], size_t t){    return t / sizeof(T); }
#define _countof(a) _countof_heaper(a, sizeof(a))
#endif
enum QXProId {
	OPACITY = 0,
	VISIBLE = 1,
	MAXIMIZED = 2,
	MINIMIZED = 3,
	ENABLED = 4,
	MINIMUMHEIGHT = 5,
	ACTIVED = 6,
	MAXIMUMHEIGHT = 7,
	MINIMUMWIDTH = 8,
	MAXIMUMWIDTH = 9,
	WIDTH = 10,
	HEIGHT = 11,
	FULLSCREEN = 12,
	HIDDEN = 13,
	MODAL = 14,
	WINDOW = 15,
	RESIZE = 16,
	SCROLL = 17,
	FIXEDHEIGHT = 18,
	FIXEDSIZE = 19,
	FIXEDWIDTH = 20,
	PALETTE = 21,
	STYLE = 22,
	CLOSE = 23,
	HIDE = 24,
	LOWER = 25,
	RAISE = 26,
	UPDATE = 27,
	WINDOWTITLE = 28,
	SHOW = 29,
	SHOWFULLSCREEN = 30,
	SHOWMAX = 31,
	SHOWMIN = 32,
	SHOWNORMAL = 33,
	FLATING = 34,
	TITLEBAR = 35,
	DOCKWIDGETFEATURE = 36,
	REPAINT = 37,
	SCICMD = 38,
	SCIFONT = 39,
	FONTSETFAMILY = 40,
	FONTPTSIZE = 41,
	FONTPXSIZE = 42,
	FONTCTOR = 43,
	MENUBAR = 44,
	ADDACTION = 45,
	ADDMENU = 46,
	ADDSEP = 47,
	INSSEP = 48,
	INSMENU = 49,
	MENUBAR_CLR = 50,
	ISDEFUP = 51,
	ISNAMBR = 52,
	SETMENU = 53,
	SETSEP = 54,
	ISSEP = 55,
	SETSHRCUT = 56,
	SETTEXT = 57,
	GETTEXT = 58,
	GETMENU = 59,
	PARENTWIDGET = 60,
	TRIGGER = 61,
	CHECKED = 62,
	ADDACT = 63,
	MDIMODE = 64,
	X_POS = 65,
	Y_POS = 66,
	MOVE = 67,
	SETWIDGET = 68,
	GETWIDGET = 69,
	SUBSETWIDGET = 70,
	SUBGETWIDGET = 71,
	MDISETSCROLLH = 72,
	MDISETSCROLLV = 73,
	CENTRALWIDGET = 74,
	TREEWIDGETADD = 75,
	TREEWIDGETINST = 76,
	TREEWIDGETGETSEL = 77,
	OPEN = 78,
	SAVE = 79,
	SETITEMTEXT = 80,
	SETITEMCOLOR = 81,
	SETBACKCOLOR = 82,
	SETCOLUMNS = 83,
	TREEWIDGETCLEAR = 84,
	SETCOLUMBWIDTH = 85,
	SETTAG = 86,
	GETTAG = 87,
	XNOTIFY = 88,
	NATIVEFINALIZE = 89,
	FOLDER = 90,
	LINEEDITSETTEXT = 91,
	LINEEDITGETTEXT = 92,
	QSCIGETTEXT = 93,
	QSCIGETSELTXT = 94,
	REMSUBWIN = 95,
	ADDSUBWIN = 96,
	MESSAGEBOXWAR = 97,
	MESSAGEBOXERR = 98,
	MESSAGEBOXINF = 99,
	MESSAGEBOXABT = 100,
	MESSAGEBOXQUE = 101,
	CURRENTSUBWIN = 102,
	WINDOWFLAG = 103,
	SETWINDOWFLAG = 104,
	CASCADESUBWIN = 105,
	TILESUBWIN = 106,
	SETACTSUBWIN = 107,
	SCIFINDFIRST = 108,
	COMBOGETTEXT = 109,
	COMBOSETTEXT = 110,
	SCIFINDNEXT = 111,
	PROPADDPROPERTY = 112,
	ADDPROPERTY = 113,
	SETMGRFACTORY = 114,
	SPWVM = 115,
	SRID = 116,
	ADDSUBPROPERTY = 117,
	PROPSETENUM = 118,
	PEORENUMVALUE = 119,
	PROPSETARRT = 120,
	PROPSETARRTSZMAX = 121,
	PROPSETARRTSZMIN = 122,
	PROPSETARRTPTMAX = 123,

	PROPSETARRTPTMIN = 124,
	PROPSETARRTRC = 125,
	PROPSETVALUEPT = 126,
	PROPSETVALUESZ = 127,
	PROPSETVALUERC = 128,
	PROPATTRCONST = 129,
	PROPATTRSSTEP = 130,
	PROPATTRDECIM = 131,
	PROPATTRENUMI = 132,
	PROPATTRENUMN = 133,
	PROPATTRFLAGN = 134,
	PROPATTRMAXIM = 135,
	PROPATTRMINIM = 136,
	PROPATTRREGEX = 137,
	PROPATTRECHOM = 138,
	PROPSETVALUE = 139,
	PROPADDPROPERTYGROUP = 140,
	PROPADDPROPERTYENUM = 141,
	PROPADDPROPERTYFLAG = 142,
	TREEPROPCLEAR = 143,
	PROPGETVALUE = 144,
	COMBOBOXADD = 145,
	COMBOBOXSETID = 146,
	COMBOBOXGETID = 147,
	SETFOCUS = 148,
	TRGETITEMTEXT = 149,
	QSCIGETRANGE = 150,
	LBLSETTEXT = 151,
	LBLGETTEXT = 152,
	CHKSETCHECK = 153,
	CHKGETCHECK = 154,
	GETVIEWPORT = 155,
	ADDDEFACTION = 156,
	SETCONTEXTMENUPOLICY = 157,
	ACTSETTEXT = 158,
	ACTGETTEXT = 159,
	ACTENABLED = 160,
	TREEWIDGETREM = 161,
	WINDOWICON = 162,
	ADDWIDGET = 163,
	INSERTWIDGET = 164,
	ADDPERWIDGET = 165,
	INSERTPERWIDGET = 166,
	REMOVEWIDGET = 167,
	SIZEGRIPENABLED = 168,
	CURRENTMESSAGE = 169,
	STATUSBAR = 170,
	SHOWMESSAGE = 171,
	QPMININUM = 172,
	QPMAXINUM = 173,
	QPVALUE = 174,
	QPTEXT = 175,
	QPVISIBLE = 176,
	QPALIGN = 177,
	QPORIENTATION = 178,
	QPINVERTAPPEAR = 179,
	QPTEXTDIR = 180,
	QPFORMAT = 181,
	QPRESET = 182,
	QPRANGE = 183,
	STYLESHEET = 184,
	PALETTECOLOR = 185,
	TRCOLUMNSHOW = 186,
	TRSELECTMODE = 187,
	TRAUTORESIZE = 188,
	TRHEADERWIDTH = 189,
	TRSORTENABLE = 190,
	TRELIDMODE = 191,
	TREESETCURITEM = 192,
	TREEGETCURROW = 193,
	TREEGETCURCOL = 194,
	TREESETCURROW = 195,
	TREESETCURCOL = 196,
	TREEGETCOUNT = 197,
	TREEGETSELITEM = 198,
	TREEITEMFLAG = 199,
	TREEITEMGETFLAG = 200,
	TREEITEMPARENT = 201,
	DELLOCBUFFER = 202,
	BUFFERSETDATA = 203,
	OPENBUFFER = 204,
	DELLOCICON = 205,
	DELLOCBYTEARRAY = 206,
	SAVESTATE = 207,
	LOADSTATE = 208,
	TRSCROLLBOTTOM = 209,
	TRIEMCLEARCHILD = 210,
	TRIEMSETEXPAND = 211,
	TRIEMSETHIDDEN = 212,
	MAPPOINT = 213,
	TRITEMSETCHECK = 214,
	TRITEMGETCHECK = 215,
	TREEGETCHILDREN = 216,
	SETITEMICON = 217,
	SETPEN = 218,
	SETBRUSH = 219,
	QXPAINTDRAWLINE = 220,
	SETBKBRUSH = 221,
	QXPAINTOPACITY = 222,
	QXPAINTBGMMODE = 223,
	IMGLOAD = 224,
	DELETEIMAGE = 225,
	DRAWIMAGE = 226,
	IMGWIDTH = 227,
	IMGHEIGHT = 228,
	IMGFORMAT = 229,
	IMGGETDATA = 230,
	QXPAINTDRAWRECT = 231,
	FILLRECT = 232,
	DRAWTEXT = 233,
	PAINTERSETFONT = 234,
	LOADFONT = 235,
	SETAPPFONT = 236,
	MATRIXDTOR = 237,
	PAINTERSAVE = 238,
	PAINTERRESTORE = 239,
	PAINTRESETMATRIX = 240,
	PAINTRESETTRANSFORM = 241,
	MATRIXMAPPOINT = 242,
	MATRIXTRANSLATE = 243,
	MATRIXSCALE = 244,
	MATRIXSHEAR = 245,
	MATRIXROTATE = 246,
	MATRIXMUL = 247,
	PAINTERGETMATRIX = 248,
	PAINTSETMATRIX = 249,
	COMBOXCLR = 250,
	BUTTONSETTEXT = 251,
	ROUNDRECT = 252,
	ROUNDEDRECT = 253,
	SETATTRIBUTE = 254,
	SETRENDERHINT = 255,
	MEASURETEXT = 256,
	PAINTERGETFCONT = 257,
	PAINTERFROMIMG = 258,
	DELLOCPAINTER = 259,
	DRAWELLIPSE	=	260,
	SCREENPOSITION = 261,
	SCREENSIZE = 262,
	SCREENCOUNT = 263,
	CURRENTSCREEN = 264,
	DELETEWIDGET = 265,
	TOOLBARADDWIDGET = 266,
	TOOLBARINSWIDGET = 267,
	OPENURL = 268,
	SETSTYLESHEET = 269,
	SETCOMPOSITIONMODE = 270,
	GETSTYLESHEEY = 271,
	FSWADDFILE = 272,
	FSWREMFILE = 273,
	SETCURSOR = 274,
	LOADTRANSLATE = 275,
    OPENLOCAL = 276,
	HASFOCUS = 277,
	GETTOPITEM = 278,
	TREEGETTOPITEMS = 279,
	TABLESETITEM = 280,
	TABLEREMOVEROW = 281,
	TABLEREMOVECOLUMN = 282,
	TABLESETCOLUMNCNT = 283,
	TABLESETROWCNT = 284,
	TABLESELECTROW = 285,
	TABLEITEMFLAG = 286,
	TABLESETTAG = 287,
	TABLEGETTAG = 288,
	TABLESETVHRM = 289,
	TABLESETVHDSS = 290,
	TABLESETSM = 291,
	TABLESETSB = 292,
	TABLESETET = 293,
	TABLESETHHFH = 294,
	TABLESETHHLS = 295,
	TABLESETSG = 296,
	TABLESETVHV = 297,
	TABLESETHHRS = 298,
	SETTABHHCOLUMNS = 299,
	SETTABVHCOLUMNS = 300,
	TABLEGETTEXTBYRC = 301,
	TABLEGETTEXTBYITEM = 302,
	TABLECLEAR = 303,
	TABLECLEARCONTENT = 304,
	TABLEGETSELITEM = 305,
	TABLEGETSELRANGE = 306,
	TABLEGETITEM	=	307,
	SETTABLEITEMTEXT = 308,
	SETTABLEITEMICON = 309,
	SETTABLEITEMCOLOR = 310,
	SETTABLEITEMBACKCOLOR = 311,
	TABITEMGETCHECK = 312,
	TABITEMSETCHECK = 313,
	TABITEMGETFLAG = 314,
	TABLESETCELLWIDGET = 315,
    TABLEGETCELLWIDGET = 316,
    SETFOCUSPOLICY = 317
};

extern XNLEnv * gs_env;
XNLEXPORT void nativeFinalize(XObject * xobj);

class XObjectData
	: public QObjectUserData {
private:
	XObject * object;
	XObject * tag;
public:



	XObjectData() {
		object = NULL;
		tag = NULL;
	}

	virtual ~XObjectData() {
		detach();
		detachTag();
	}

	void detach() {
		if (object != NULL) {
			nativeFinalize(object);
			gs_env->dereferenceObject(object);
			object = NULL;
		}
	}

	void detachTag() {
		if (tag != NULL) {
			gs_env->dereferenceObject(tag);
			tag = NULL;
		}
	}
	void setObject(XObject * obj) {
		detach();

		if (obj != NULL) {
			object = gs_env->referenceObject(obj);
		}
	}
	XObject * getObject() {
		return object;
	}
	XObject * getTag() {
		return tag;
	}
	void setTag(XObject * obj) {
		detachTag();

		if (obj != NULL) {
			tag = gs_env->referenceObject(obj);
		}
	}
};

struct  XIDENT
{
	const char * path;
	int methodId;
};

struct megInfo {
	const char * name;
	int id;
};

extern XIDENT  methods[];

#define TRIGGER_ID		220
#define ITEMPRESS_ID	221
#define ITEMCLK_ID		222
#define ITEMDBCLK_ID	223
#define ITEMACTIVE_ID	224
#define ITEMENTER_ID	225
#define ITEMCHANGE_ID	226
#define ITEMEXPAND_ID	227
#define ITEMCOLLPA_ID	228
#define ITEMCURCHA_ID	229
#define ITEMSELCHA_ID	230
#define NOTIFY_ID		231
#define FINALIZE_ID		232
#define BTNCLICK_ID		233
#define TOGGLE_ID		234
#define ONCHECK_ID		235
#define ONPRESS_ID		236
#define ONRELEASE_ID	237

#define ONFINISH_ID	238
#define ONACCEPT_ID	239
#define ONREJECT_ID	240

#define SCEN_CHANGE_ID  241
#define ON_CALLTIPCLICK_ID  242
#define ON_CHARADDED_ID  243
#define ON_DOUBLECLICK_ID  244
#define ON_DWELLEND_ID  245
#define ON_DWELLSTART_ID  246
#define ON_FOCUSIN_ID  247
#define ON_FOCUSOUT_ID  248
#define ON_HOTSPOTCLICK_ID  249
#define ON_HOTSPOTDOUBLECLICK_ID  250
#define ON_HOTSPOTRELEASECLICK_ID  251
#define ON_INDICATORCLICK_ID  252
#define ON_INDICATORRELEASE_ID  253
#define ON_MACRORECORD_ID  254
#define ON_MARGINCLICK_ID  255
#define ON_MARGINRIGHTCLICK_ID  256
#define ON_MODIFIED_ID  257
#define ON_MODIFYATTEMPTRO_ID  258
#define ON_NEEDSHOWN_ID  259
#define ON_PAINTED_ID  260
#define ON_SAVEPOINTLEFT_ID  261
#define ON_SAVEPOINTREACHED_ID  262
#define ON_STYLENEEDED_ID  263
#define ON_UPDATEUI_ID  264
#define ON_USERLISTSELECTION_ID  265
#define ON_USERLISTSELECTION_ID1  266
#define ON_ZOOM_ID  267
#define ON_SELCHANGED_ID  268 
#define ON_AUTOCCANCELLED_ID 269 
#define ON_AUTOCCHARDELETED_ID 270 
#define ON_AUTOCCOMPLETED_ID 271 
#define ON_AUTOCSELECTION_ID 272 
#define ON_AUTOCSELECTION_ID_1 273 

#define ON_EDITCHANGE 274
#define ON_EDITEDITED 275
#define ON_EDITPOSCHANGE 276
#define ON_EDITRETURN 277
#define ON_EDITFINISH 278
#define ON_EDITSELCHANGE 279

#define ON_CURTEXTCHANGE 280
#define ON_ACTIVATED 281
#define ON_SELCHANGE 282

#define ON_FILECHANGE 283
#define ON_DIRCHANGE 284

#define ON_CELLCHANGE 285
#define ON_CELLITEMCHANGE 286

#define ON_CELLPRESS 287
#define ON_CELLITEMPRESS 288

#define ON_CELLCLICK 289
#define ON_CELLITEMCLICK 290

#define ON_CELLDBCLICK 291
#define ON_CELLITEMDBCLICK 292

#define ON_CELLENTER 293
#define ON_CELLITEMENTER 294

#define ON_CELLACTIVE 295
#define ON_CELLITEMACTIVE 296
