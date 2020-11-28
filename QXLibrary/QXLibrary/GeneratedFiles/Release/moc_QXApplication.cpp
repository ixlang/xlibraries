/****************************************************************************
** Meta object code from reading C++ file 'QXApplication.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QXApplication.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QXApplication.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QXApplication_t {
    QByteArrayData data[1];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QXApplication_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QXApplication_t qt_meta_stringdata_QXApplication = {
    {
QT_MOC_LITERAL(0, 0, 13) // "QXApplication"

    },
    "QXApplication"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QXApplication[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void QXApplication::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject QXApplication::staticMetaObject = {
    { &QApplication::staticMetaObject, qt_meta_stringdata_QXApplication.data,
      qt_meta_data_QXApplication,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QXApplication::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QXApplication::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QXApplication.stringdata0))
        return static_cast<void*>(const_cast< QXApplication*>(this));
    return QApplication::qt_metacast(_clname);
}

int QXApplication::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QApplication::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ActionReceiver_t {
    QByteArrayData data[167];
    char stringdata0[2276];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ActionReceiver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ActionReceiver_t qt_meta_stringdata_ActionReceiver = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ActionReceiver"
QT_MOC_LITERAL(1, 15, 15), // "ActionTriggered"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 3), // "act"
QT_MOC_LITERAL(4, 36, 13), // "tritemPressed"
QT_MOC_LITERAL(5, 50, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(6, 67, 4), // "item"
QT_MOC_LITERAL(7, 72, 6), // "column"
QT_MOC_LITERAL(8, 79, 13), // "tritemClicked"
QT_MOC_LITERAL(9, 93, 19), // "tritemDoubleClicked"
QT_MOC_LITERAL(10, 113, 15), // "tritemActivated"
QT_MOC_LITERAL(11, 129, 13), // "tritemEntered"
QT_MOC_LITERAL(12, 143, 13), // "tritemChanged"
QT_MOC_LITERAL(13, 157, 14), // "tritemExpanded"
QT_MOC_LITERAL(14, 172, 15), // "tritemCollapsed"
QT_MOC_LITERAL(15, 188, 20), // "trcurrentItemChanged"
QT_MOC_LITERAL(16, 209, 7), // "current"
QT_MOC_LITERAL(17, 217, 8), // "previous"
QT_MOC_LITERAL(18, 226, 22), // "tritemSelectionChanged"
QT_MOC_LITERAL(19, 249, 10), // "btnclicked"
QT_MOC_LITERAL(20, 260, 7), // "checked"
QT_MOC_LITERAL(21, 268, 10), // "btntoggled"
QT_MOC_LITERAL(22, 279, 10), // "btnpressed"
QT_MOC_LITERAL(23, 290, 11), // "btnreleased"
QT_MOC_LITERAL(24, 302, 8), // "onFinish"
QT_MOC_LITERAL(25, 311, 3), // "res"
QT_MOC_LITERAL(26, 315, 17), // "onEditTextChanged"
QT_MOC_LITERAL(27, 333, 3), // "str"
QT_MOC_LITERAL(28, 337, 11), // "onActivated"
QT_MOC_LITERAL(29, 349, 5), // "index"
QT_MOC_LITERAL(30, 355, 16), // "onfswFileChanged"
QT_MOC_LITERAL(31, 372, 4), // "path"
QT_MOC_LITERAL(32, 377, 21), // "onfswDirectoryChanged"
QT_MOC_LITERAL(33, 399, 21), // "onCurrentIndexChanged"
QT_MOC_LITERAL(34, 421, 8), // "onAccept"
QT_MOC_LITERAL(35, 430, 8), // "onReject"
QT_MOC_LITERAL(36, 439, 15), // "QSCN_SELCHANGED"
QT_MOC_LITERAL(37, 455, 3), // "yes"
QT_MOC_LITERAL(38, 459, 19), // "slotGetCallbackData"
QT_MOC_LITERAL(39, 479, 24), // "LimeReport::CallbackInfo"
QT_MOC_LITERAL(40, 504, 4), // "info"
QT_MOC_LITERAL(41, 509, 9), // "QVariant&"
QT_MOC_LITERAL(42, 519, 4), // "data"
QT_MOC_LITERAL(43, 524, 13), // "slotChangePos"
QT_MOC_LITERAL(44, 538, 39), // "LimeReport::CallbackInfo::Cha..."
QT_MOC_LITERAL(45, 578, 4), // "type"
QT_MOC_LITERAL(46, 583, 5), // "bool&"
QT_MOC_LITERAL(47, 589, 6), // "result"
QT_MOC_LITERAL(48, 596, 18), // "SCN_AUTOCCANCELLED"
QT_MOC_LITERAL(49, 615, 20), // "SCN_AUTOCCHARDELETED"
QT_MOC_LITERAL(50, 636, 18), // "SCN_AUTOCCOMPLETED"
QT_MOC_LITERAL(51, 655, 11), // "const char*"
QT_MOC_LITERAL(52, 667, 9), // "selection"
QT_MOC_LITERAL(53, 677, 8), // "position"
QT_MOC_LITERAL(54, 686, 2), // "ch"
QT_MOC_LITERAL(55, 689, 6), // "method"
QT_MOC_LITERAL(56, 696, 18), // "SCN_AUTOCSELECTION"
QT_MOC_LITERAL(57, 715, 11), // "SCEN_CHANGE"
QT_MOC_LITERAL(58, 727, 16), // "SCN_CALLTIPCLICK"
QT_MOC_LITERAL(59, 744, 9), // "direction"
QT_MOC_LITERAL(60, 754, 13), // "SCN_CHARADDED"
QT_MOC_LITERAL(61, 768, 9), // "charadded"
QT_MOC_LITERAL(62, 778, 15), // "SCN_DOUBLECLICK"
QT_MOC_LITERAL(63, 794, 4), // "line"
QT_MOC_LITERAL(64, 799, 9), // "modifiers"
QT_MOC_LITERAL(65, 809, 12), // "SCN_DWELLEND"
QT_MOC_LITERAL(66, 822, 1), // "x"
QT_MOC_LITERAL(67, 824, 1), // "y"
QT_MOC_LITERAL(68, 826, 14), // "SCN_DWELLSTART"
QT_MOC_LITERAL(69, 841, 11), // "SCN_FOCUSIN"
QT_MOC_LITERAL(70, 853, 12), // "SCN_FOCUSOUT"
QT_MOC_LITERAL(71, 866, 16), // "SCN_HOTSPOTCLICK"
QT_MOC_LITERAL(72, 883, 22), // "SCN_HOTSPOTDOUBLECLICK"
QT_MOC_LITERAL(73, 906, 23), // "SCN_HOTSPOTRELEASECLICK"
QT_MOC_LITERAL(74, 930, 18), // "SCN_INDICATORCLICK"
QT_MOC_LITERAL(75, 949, 20), // "SCN_INDICATORRELEASE"
QT_MOC_LITERAL(76, 970, 15), // "SCN_MACRORECORD"
QT_MOC_LITERAL(77, 986, 3), // "msg"
QT_MOC_LITERAL(78, 990, 6), // "wparam"
QT_MOC_LITERAL(79, 997, 6), // "lparam"
QT_MOC_LITERAL(80, 1004, 15), // "SCN_MARGINCLICK"
QT_MOC_LITERAL(81, 1020, 6), // "margin"
QT_MOC_LITERAL(82, 1027, 20), // "SCN_MARGINRIGHTCLICK"
QT_MOC_LITERAL(83, 1048, 12), // "SCN_MODIFIED"
QT_MOC_LITERAL(84, 1061, 7), // "modType"
QT_MOC_LITERAL(85, 1069, 4), // "text"
QT_MOC_LITERAL(86, 1074, 6), // "length"
QT_MOC_LITERAL(87, 1081, 10), // "linesAdded"
QT_MOC_LITERAL(88, 1092, 12), // "foldLevelNow"
QT_MOC_LITERAL(89, 1105, 13), // "foldLevelPrev"
QT_MOC_LITERAL(90, 1119, 5), // "token"
QT_MOC_LITERAL(91, 1125, 20), // "annotationLinesAdded"
QT_MOC_LITERAL(92, 1146, 19), // "SCN_MODIFYATTEMPTRO"
QT_MOC_LITERAL(93, 1166, 13), // "SCN_NEEDSHOWN"
QT_MOC_LITERAL(94, 1180, 11), // "SCN_PAINTED"
QT_MOC_LITERAL(95, 1192, 17), // "SCN_SAVEPOINTLEFT"
QT_MOC_LITERAL(96, 1210, 20), // "SCN_SAVEPOINTREACHED"
QT_MOC_LITERAL(97, 1231, 15), // "SCN_STYLENEEDED"
QT_MOC_LITERAL(98, 1247, 12), // "SCN_UPDATEUI"
QT_MOC_LITERAL(99, 1260, 7), // "updated"
QT_MOC_LITERAL(100, 1268, 21), // "SCN_USERLISTSELECTION"
QT_MOC_LITERAL(101, 1290, 8), // "SCN_ZOOM"
QT_MOC_LITERAL(102, 1299, 13), // "tetextChanged"
QT_MOC_LITERAL(103, 1313, 23), // "tecursorPositionChanged"
QT_MOC_LITERAL(104, 1337, 18), // "teselectionChanged"
QT_MOC_LITERAL(105, 1356, 12), // "etextChanged"
QT_MOC_LITERAL(106, 1369, 11), // "etextEdited"
QT_MOC_LITERAL(107, 1381, 22), // "ecursorPositionChanged"
QT_MOC_LITERAL(108, 1404, 1), // "a"
QT_MOC_LITERAL(109, 1406, 1), // "b"
QT_MOC_LITERAL(110, 1408, 14), // "ereturnPressed"
QT_MOC_LITERAL(111, 1423, 16), // "eeditingFinished"
QT_MOC_LITERAL(112, 1440, 11), // "oncellPress"
QT_MOC_LITERAL(113, 1452, 3), // "row"
QT_MOC_LITERAL(114, 1456, 18), // "onPreviewRequested"
QT_MOC_LITERAL(115, 1475, 9), // "QPrinter*"
QT_MOC_LITERAL(116, 1485, 7), // "printer"
QT_MOC_LITERAL(117, 1493, 15), // "oncellItemPress"
QT_MOC_LITERAL(118, 1509, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(119, 1527, 11), // "oncellClick"
QT_MOC_LITERAL(120, 1539, 15), // "oncellItemClick"
QT_MOC_LITERAL(121, 1555, 13), // "oncellDBClick"
QT_MOC_LITERAL(122, 1569, 17), // "oncellItemDBClick"
QT_MOC_LITERAL(123, 1587, 11), // "oncellEnter"
QT_MOC_LITERAL(124, 1599, 15), // "oncellItemEnter"
QT_MOC_LITERAL(125, 1615, 12), // "oncellActive"
QT_MOC_LITERAL(126, 1628, 16), // "oncellItemActive"
QT_MOC_LITERAL(127, 1645, 13), // "oncellChanged"
QT_MOC_LITERAL(128, 1659, 17), // "oncellItemChanged"
QT_MOC_LITERAL(129, 1677, 17), // "eselectionChanged"
QT_MOC_LITERAL(130, 1695, 14), // "onValueChanged"
QT_MOC_LITERAL(131, 1710, 11), // "QtProperty*"
QT_MOC_LITERAL(132, 1722, 8), // "property"
QT_MOC_LITERAL(133, 1731, 3), // "val"
QT_MOC_LITERAL(134, 1735, 18), // "onAttributeChanged"
QT_MOC_LITERAL(135, 1754, 9), // "attribute"
QT_MOC_LITERAL(136, 1764, 13), // "renderStarted"
QT_MOC_LITERAL(137, 1778, 18), // "renderPageFinished"
QT_MOC_LITERAL(138, 1797, 17), // "renderedPageCount"
QT_MOC_LITERAL(139, 1815, 14), // "renderFinished"
QT_MOC_LITERAL(140, 1830, 25), // "qtabwidget_currentChanged"
QT_MOC_LITERAL(141, 1856, 28), // "qtabwidget_tabCloseRequested"
QT_MOC_LITERAL(142, 1885, 24), // "qtabwidget_tabBarClicked"
QT_MOC_LITERAL(143, 1910, 30), // "qtabwidget_tabBarDoubleClicked"
QT_MOC_LITERAL(144, 1941, 22), // "qtabbar_currentChanged"
QT_MOC_LITERAL(145, 1964, 25), // "qtabbar_tabCloseRequested"
QT_MOC_LITERAL(146, 1990, 16), // "qtabbar_tabMoved"
QT_MOC_LITERAL(147, 2007, 4), // "from"
QT_MOC_LITERAL(148, 2012, 2), // "to"
QT_MOC_LITERAL(149, 2015, 21), // "qtabbar_tabBarClicked"
QT_MOC_LITERAL(150, 2037, 27), // "qtabbar_tabBarDoubleClicked"
QT_MOC_LITERAL(151, 2065, 19), // "slider_valueChanged"
QT_MOC_LITERAL(152, 2085, 5), // "value"
QT_MOC_LITERAL(153, 2091, 20), // "slider_sliderPressed"
QT_MOC_LITERAL(154, 2112, 18), // "slider_sliderMoved"
QT_MOC_LITERAL(155, 2131, 21), // "slider_sliderReleased"
QT_MOC_LITERAL(156, 2153, 19), // "slider_rangeChanged"
QT_MOC_LITERAL(157, 2173, 3), // "min"
QT_MOC_LITERAL(158, 2177, 3), // "max"
QT_MOC_LITERAL(159, 2181, 22), // "slider_actionTriggered"
QT_MOC_LITERAL(160, 2204, 6), // "action"
QT_MOC_LITERAL(161, 2211, 17), // "ondateTimeChanged"
QT_MOC_LITERAL(162, 2229, 8), // "dateTime"
QT_MOC_LITERAL(163, 2238, 13), // "ontimeChanged"
QT_MOC_LITERAL(164, 2252, 4), // "time"
QT_MOC_LITERAL(165, 2257, 13), // "ondateChanged"
QT_MOC_LITERAL(166, 2271, 4) // "date"

    },
    "ActionReceiver\0ActionTriggered\0\0act\0"
    "tritemPressed\0QTreeWidgetItem*\0item\0"
    "column\0tritemClicked\0tritemDoubleClicked\0"
    "tritemActivated\0tritemEntered\0"
    "tritemChanged\0tritemExpanded\0"
    "tritemCollapsed\0trcurrentItemChanged\0"
    "current\0previous\0tritemSelectionChanged\0"
    "btnclicked\0checked\0btntoggled\0btnpressed\0"
    "btnreleased\0onFinish\0res\0onEditTextChanged\0"
    "str\0onActivated\0index\0onfswFileChanged\0"
    "path\0onfswDirectoryChanged\0"
    "onCurrentIndexChanged\0onAccept\0onReject\0"
    "QSCN_SELCHANGED\0yes\0slotGetCallbackData\0"
    "LimeReport::CallbackInfo\0info\0QVariant&\0"
    "data\0slotChangePos\0"
    "LimeReport::CallbackInfo::ChangePosType\0"
    "type\0bool&\0result\0SCN_AUTOCCANCELLED\0"
    "SCN_AUTOCCHARDELETED\0SCN_AUTOCCOMPLETED\0"
    "const char*\0selection\0position\0ch\0"
    "method\0SCN_AUTOCSELECTION\0SCEN_CHANGE\0"
    "SCN_CALLTIPCLICK\0direction\0SCN_CHARADDED\0"
    "charadded\0SCN_DOUBLECLICK\0line\0modifiers\0"
    "SCN_DWELLEND\0x\0y\0SCN_DWELLSTART\0"
    "SCN_FOCUSIN\0SCN_FOCUSOUT\0SCN_HOTSPOTCLICK\0"
    "SCN_HOTSPOTDOUBLECLICK\0SCN_HOTSPOTRELEASECLICK\0"
    "SCN_INDICATORCLICK\0SCN_INDICATORRELEASE\0"
    "SCN_MACRORECORD\0msg\0wparam\0lparam\0"
    "SCN_MARGINCLICK\0margin\0SCN_MARGINRIGHTCLICK\0"
    "SCN_MODIFIED\0modType\0text\0length\0"
    "linesAdded\0foldLevelNow\0foldLevelPrev\0"
    "token\0annotationLinesAdded\0"
    "SCN_MODIFYATTEMPTRO\0SCN_NEEDSHOWN\0"
    "SCN_PAINTED\0SCN_SAVEPOINTLEFT\0"
    "SCN_SAVEPOINTREACHED\0SCN_STYLENEEDED\0"
    "SCN_UPDATEUI\0updated\0SCN_USERLISTSELECTION\0"
    "SCN_ZOOM\0tetextChanged\0tecursorPositionChanged\0"
    "teselectionChanged\0etextChanged\0"
    "etextEdited\0ecursorPositionChanged\0a\0"
    "b\0ereturnPressed\0eeditingFinished\0"
    "oncellPress\0row\0onPreviewRequested\0"
    "QPrinter*\0printer\0oncellItemPress\0"
    "QTableWidgetItem*\0oncellClick\0"
    "oncellItemClick\0oncellDBClick\0"
    "oncellItemDBClick\0oncellEnter\0"
    "oncellItemEnter\0oncellActive\0"
    "oncellItemActive\0oncellChanged\0"
    "oncellItemChanged\0eselectionChanged\0"
    "onValueChanged\0QtProperty*\0property\0"
    "val\0onAttributeChanged\0attribute\0"
    "renderStarted\0renderPageFinished\0"
    "renderedPageCount\0renderFinished\0"
    "qtabwidget_currentChanged\0"
    "qtabwidget_tabCloseRequested\0"
    "qtabwidget_tabBarClicked\0"
    "qtabwidget_tabBarDoubleClicked\0"
    "qtabbar_currentChanged\0qtabbar_tabCloseRequested\0"
    "qtabbar_tabMoved\0from\0to\0qtabbar_tabBarClicked\0"
    "qtabbar_tabBarDoubleClicked\0"
    "slider_valueChanged\0value\0"
    "slider_sliderPressed\0slider_sliderMoved\0"
    "slider_sliderReleased\0slider_rangeChanged\0"
    "min\0max\0slider_actionTriggered\0action\0"
    "ondateTimeChanged\0dateTime\0ontimeChanged\0"
    "time\0ondateChanged\0date"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ActionReceiver[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
     104,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  534,    2, 0x08 /* Private */,
       4,    2,  537,    2, 0x08 /* Private */,
       8,    2,  542,    2, 0x08 /* Private */,
       9,    2,  547,    2, 0x08 /* Private */,
      10,    2,  552,    2, 0x08 /* Private */,
      11,    2,  557,    2, 0x08 /* Private */,
      12,    2,  562,    2, 0x08 /* Private */,
      13,    1,  567,    2, 0x08 /* Private */,
      14,    1,  570,    2, 0x08 /* Private */,
      15,    2,  573,    2, 0x08 /* Private */,
      18,    0,  578,    2, 0x08 /* Private */,
      19,    1,  579,    2, 0x08 /* Private */,
      21,    1,  582,    2, 0x08 /* Private */,
      22,    0,  585,    2, 0x08 /* Private */,
      23,    0,  586,    2, 0x08 /* Private */,
      24,    1,  587,    2, 0x08 /* Private */,
      26,    1,  590,    2, 0x08 /* Private */,
      28,    1,  593,    2, 0x08 /* Private */,
      30,    1,  596,    2, 0x08 /* Private */,
      32,    1,  599,    2, 0x08 /* Private */,
      33,    1,  602,    2, 0x08 /* Private */,
      34,    0,  605,    2, 0x08 /* Private */,
      35,    0,  606,    2, 0x08 /* Private */,
      36,    1,  607,    2, 0x08 /* Private */,
      38,    2,  610,    2, 0x08 /* Private */,
      43,    2,  615,    2, 0x08 /* Private */,
      48,    0,  620,    2, 0x08 /* Private */,
      49,    0,  621,    2, 0x08 /* Private */,
      50,    4,  622,    2, 0x08 /* Private */,
      56,    4,  631,    2, 0x08 /* Private */,
      56,    2,  640,    2, 0x08 /* Private */,
      57,    0,  645,    2, 0x08 /* Private */,
      58,    1,  646,    2, 0x08 /* Private */,
      60,    1,  649,    2, 0x08 /* Private */,
      62,    3,  652,    2, 0x08 /* Private */,
      65,    3,  659,    2, 0x08 /* Private */,
      68,    3,  666,    2, 0x08 /* Private */,
      69,    0,  673,    2, 0x08 /* Private */,
      70,    0,  674,    2, 0x08 /* Private */,
      71,    2,  675,    2, 0x08 /* Private */,
      72,    2,  680,    2, 0x08 /* Private */,
      73,    2,  685,    2, 0x08 /* Private */,
      74,    2,  690,    2, 0x08 /* Private */,
      75,    2,  695,    2, 0x08 /* Private */,
      76,    3,  700,    2, 0x08 /* Private */,
      80,    3,  707,    2, 0x08 /* Private */,
      82,    3,  714,    2, 0x08 /* Private */,
      83,   10,  721,    2, 0x08 /* Private */,
      92,    0,  742,    2, 0x08 /* Private */,
      93,    2,  743,    2, 0x08 /* Private */,
      94,    0,  748,    2, 0x08 /* Private */,
      95,    0,  749,    2, 0x08 /* Private */,
      96,    0,  750,    2, 0x08 /* Private */,
      97,    1,  751,    2, 0x08 /* Private */,
      98,    1,  754,    2, 0x08 /* Private */,
     100,    4,  757,    2, 0x08 /* Private */,
     100,    2,  766,    2, 0x08 /* Private */,
     101,    0,  771,    2, 0x08 /* Private */,
     102,    0,  772,    2, 0x08 /* Private */,
     103,    0,  773,    2, 0x08 /* Private */,
     104,    0,  774,    2, 0x08 /* Private */,
     105,    1,  775,    2, 0x08 /* Private */,
     106,    1,  778,    2, 0x08 /* Private */,
     107,    2,  781,    2, 0x08 /* Private */,
     110,    0,  786,    2, 0x08 /* Private */,
     111,    0,  787,    2, 0x08 /* Private */,
     112,    2,  788,    2, 0x08 /* Private */,
     114,    1,  793,    2, 0x08 /* Private */,
     117,    1,  796,    2, 0x08 /* Private */,
     119,    2,  799,    2, 0x08 /* Private */,
     120,    1,  804,    2, 0x08 /* Private */,
     121,    2,  807,    2, 0x08 /* Private */,
     122,    1,  812,    2, 0x08 /* Private */,
     123,    2,  815,    2, 0x08 /* Private */,
     124,    1,  820,    2, 0x08 /* Private */,
     125,    2,  823,    2, 0x08 /* Private */,
     126,    1,  828,    2, 0x08 /* Private */,
     127,    2,  831,    2, 0x08 /* Private */,
     128,    1,  836,    2, 0x08 /* Private */,
     129,    0,  839,    2, 0x08 /* Private */,
     130,    2,  840,    2, 0x08 /* Private */,
     130,    2,  845,    2, 0x08 /* Private */,
     134,    3,  850,    2, 0x08 /* Private */,
     136,    0,  857,    2, 0x08 /* Private */,
     137,    1,  858,    2, 0x08 /* Private */,
     139,    0,  861,    2, 0x08 /* Private */,
     140,    1,  862,    2, 0x08 /* Private */,
     141,    1,  865,    2, 0x08 /* Private */,
     142,    1,  868,    2, 0x08 /* Private */,
     143,    1,  871,    2, 0x08 /* Private */,
     144,    1,  874,    2, 0x08 /* Private */,
     145,    1,  877,    2, 0x08 /* Private */,
     146,    2,  880,    2, 0x08 /* Private */,
     149,    1,  885,    2, 0x08 /* Private */,
     150,    1,  888,    2, 0x08 /* Private */,
     151,    1,  891,    2, 0x08 /* Private */,
     153,    0,  894,    2, 0x08 /* Private */,
     154,    1,  895,    2, 0x08 /* Private */,
     155,    0,  898,    2, 0x08 /* Private */,
     156,    2,  899,    2, 0x08 /* Private */,
     159,    1,  904,    2, 0x08 /* Private */,
     161,    1,  907,    2, 0x08 /* Private */,
     163,    1,  910,    2, 0x08 /* Private */,
     165,    1,  913,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Bool, QMetaType::QObjectStar,    3,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5,   16,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   37,
    QMetaType::Void, 0x80000000 | 39, 0x80000000 | 41,   40,   42,
    QMetaType::Void, 0x80000000 | 44, 0x80000000 | 46,   45,   47,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 51, QMetaType::Int, QMetaType::Int, QMetaType::Int,   52,   53,   54,   55,
    QMetaType::Void, 0x80000000 | 51, QMetaType::Int, QMetaType::Int, QMetaType::Int,   52,   53,   54,   55,
    QMetaType::Void, 0x80000000 | 51, QMetaType::Int,   52,   53,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   59,
    QMetaType::Void, QMetaType::Int,   61,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   53,   63,   64,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   53,   66,   67,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   53,   66,   67,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   53,   64,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   53,   64,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   53,   64,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   53,   64,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   53,   64,
    QMetaType::Void, QMetaType::UInt, QMetaType::ULong, QMetaType::VoidStar,   77,   78,   79,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   53,   64,   81,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   53,   64,   81,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 51, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   53,   84,   85,   86,   87,   63,   88,   89,   90,   91,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   53,   86,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   53,
    QMetaType::Void, QMetaType::Int,   99,
    QMetaType::Void, 0x80000000 | 51, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 51, QMetaType::Int,   85,   86,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  108,  109,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  113,    7,
    QMetaType::Void, 0x80000000 | 115,  116,
    QMetaType::Void, 0x80000000 | 118,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  113,    7,
    QMetaType::Void, 0x80000000 | 118,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  113,    7,
    QMetaType::Void, 0x80000000 | 118,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  113,    7,
    QMetaType::Void, 0x80000000 | 118,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  113,    7,
    QMetaType::Void, 0x80000000 | 118,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  113,    7,
    QMetaType::Void, 0x80000000 | 118,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 131, QMetaType::Int,  132,  133,
    QMetaType::Void, 0x80000000 | 131, QMetaType::QVariant,  132,  133,
    QMetaType::Void, 0x80000000 | 131, QMetaType::QString, QMetaType::QVariant,  132,  135,  133,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  138,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  147,  148,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Int,  152,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   53,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  157,  158,
    QMetaType::Void, QMetaType::Int,  160,
    QMetaType::Void, QMetaType::QDateTime,  162,
    QMetaType::Void, QMetaType::QTime,  164,
    QMetaType::Void, QMetaType::QDate,  166,

       0        // eod
};

void ActionReceiver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ActionReceiver *_t = static_cast<ActionReceiver *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->ActionTriggered((*reinterpret_cast< QObject*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->tritemPressed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->tritemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->tritemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->tritemActivated((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->tritemEntered((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->tritemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->tritemExpanded((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 8: _t->tritemCollapsed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 9: _t->trcurrentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 10: _t->tritemSelectionChanged(); break;
        case 11: _t->btnclicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->btntoggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->btnpressed(); break;
        case 14: _t->btnreleased(); break;
        case 15: _t->onFinish((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->onEditTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: _t->onActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->onfswFileChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: _t->onfswDirectoryChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: _t->onCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->onAccept(); break;
        case 22: _t->onReject(); break;
        case 23: _t->QSCN_SELCHANGED((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->slotGetCallbackData((*reinterpret_cast< LimeReport::CallbackInfo(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 25: _t->slotChangePos((*reinterpret_cast< const LimeReport::CallbackInfo::ChangePosType(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 26: _t->SCN_AUTOCCANCELLED(); break;
        case 27: _t->SCN_AUTOCCHARDELETED(); break;
        case 28: _t->SCN_AUTOCCOMPLETED((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 29: _t->SCN_AUTOCSELECTION((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 30: _t->SCN_AUTOCSELECTION((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 31: _t->SCEN_CHANGE(); break;
        case 32: _t->SCN_CALLTIPCLICK((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->SCN_CHARADDED((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: _t->SCN_DOUBLECLICK((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 35: _t->SCN_DWELLEND((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 36: _t->SCN_DWELLSTART((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 37: _t->SCN_FOCUSIN(); break;
        case 38: _t->SCN_FOCUSOUT(); break;
        case 39: _t->SCN_HOTSPOTCLICK((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 40: _t->SCN_HOTSPOTDOUBLECLICK((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 41: _t->SCN_HOTSPOTRELEASECLICK((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 42: _t->SCN_INDICATORCLICK((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 43: _t->SCN_INDICATORRELEASE((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 44: _t->SCN_MACRORECORD((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< ulong(*)>(_a[2])),(*reinterpret_cast< void*(*)>(_a[3]))); break;
        case 45: _t->SCN_MARGINCLICK((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 46: _t->SCN_MARGINRIGHTCLICK((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 47: _t->SCN_MODIFIED((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const char*(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8])),(*reinterpret_cast< int(*)>(_a[9])),(*reinterpret_cast< int(*)>(_a[10]))); break;
        case 48: _t->SCN_MODIFYATTEMPTRO(); break;
        case 49: _t->SCN_NEEDSHOWN((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 50: _t->SCN_PAINTED(); break;
        case 51: _t->SCN_SAVEPOINTLEFT(); break;
        case 52: _t->SCN_SAVEPOINTREACHED(); break;
        case 53: _t->SCN_STYLENEEDED((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 54: _t->SCN_UPDATEUI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 55: _t->SCN_USERLISTSELECTION((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 56: _t->SCN_USERLISTSELECTION((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 57: _t->SCN_ZOOM(); break;
        case 58: _t->tetextChanged(); break;
        case 59: _t->tecursorPositionChanged(); break;
        case 60: _t->teselectionChanged(); break;
        case 61: _t->etextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 62: _t->etextEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 63: _t->ecursorPositionChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 64: _t->ereturnPressed(); break;
        case 65: _t->eeditingFinished(); break;
        case 66: _t->oncellPress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 67: _t->onPreviewRequested((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 68: _t->oncellItemPress((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 69: _t->oncellClick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 70: _t->oncellItemClick((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 71: _t->oncellDBClick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 72: _t->oncellItemDBClick((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 73: _t->oncellEnter((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 74: _t->oncellItemEnter((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 75: _t->oncellActive((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 76: _t->oncellItemActive((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 77: _t->oncellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 78: _t->oncellItemChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 79: _t->eselectionChanged(); break;
        case 80: _t->onValueChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 81: _t->onValueChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 82: _t->onAttributeChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QVariant(*)>(_a[3]))); break;
        case 83: _t->renderStarted(); break;
        case 84: _t->renderPageFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 85: _t->renderFinished(); break;
        case 86: _t->qtabwidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 87: _t->qtabwidget_tabCloseRequested((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 88: _t->qtabwidget_tabBarClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 89: _t->qtabwidget_tabBarDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 90: _t->qtabbar_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 91: _t->qtabbar_tabCloseRequested((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 92: _t->qtabbar_tabMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 93: _t->qtabbar_tabBarClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 94: _t->qtabbar_tabBarDoubleClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 95: _t->slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 96: _t->slider_sliderPressed(); break;
        case 97: _t->slider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 98: _t->slider_sliderReleased(); break;
        case 99: _t->slider_rangeChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 100: _t->slider_actionTriggered((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 101: _t->ondateTimeChanged((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        case 102: _t->ontimeChanged((*reinterpret_cast< const QTime(*)>(_a[1]))); break;
        case 103: _t->ondateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ActionReceiver::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ActionReceiver.data,
      qt_meta_data_ActionReceiver,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ActionReceiver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ActionReceiver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ActionReceiver.stringdata0))
        return static_cast<void*>(const_cast< ActionReceiver*>(this));
    return QObject::qt_metacast(_clname);
}

int ActionReceiver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 104)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 104;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 104)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 104;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
