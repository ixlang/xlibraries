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
    QByteArrayData data[118];
    char stringdata0[1504];
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
QT_MOC_LITERAL(38, 459, 18), // "SCN_AUTOCCANCELLED"
QT_MOC_LITERAL(39, 478, 20), // "SCN_AUTOCCHARDELETED"
QT_MOC_LITERAL(40, 499, 18), // "SCN_AUTOCCOMPLETED"
QT_MOC_LITERAL(41, 518, 11), // "const char*"
QT_MOC_LITERAL(42, 530, 9), // "selection"
QT_MOC_LITERAL(43, 540, 8), // "position"
QT_MOC_LITERAL(44, 549, 2), // "ch"
QT_MOC_LITERAL(45, 552, 6), // "method"
QT_MOC_LITERAL(46, 559, 18), // "SCN_AUTOCSELECTION"
QT_MOC_LITERAL(47, 578, 11), // "SCEN_CHANGE"
QT_MOC_LITERAL(48, 590, 16), // "SCN_CALLTIPCLICK"
QT_MOC_LITERAL(49, 607, 9), // "direction"
QT_MOC_LITERAL(50, 617, 13), // "SCN_CHARADDED"
QT_MOC_LITERAL(51, 631, 9), // "charadded"
QT_MOC_LITERAL(52, 641, 15), // "SCN_DOUBLECLICK"
QT_MOC_LITERAL(53, 657, 4), // "line"
QT_MOC_LITERAL(54, 662, 9), // "modifiers"
QT_MOC_LITERAL(55, 672, 12), // "SCN_DWELLEND"
QT_MOC_LITERAL(56, 685, 1), // "x"
QT_MOC_LITERAL(57, 687, 1), // "y"
QT_MOC_LITERAL(58, 689, 14), // "SCN_DWELLSTART"
QT_MOC_LITERAL(59, 704, 11), // "SCN_FOCUSIN"
QT_MOC_LITERAL(60, 716, 12), // "SCN_FOCUSOUT"
QT_MOC_LITERAL(61, 729, 16), // "SCN_HOTSPOTCLICK"
QT_MOC_LITERAL(62, 746, 22), // "SCN_HOTSPOTDOUBLECLICK"
QT_MOC_LITERAL(63, 769, 23), // "SCN_HOTSPOTRELEASECLICK"
QT_MOC_LITERAL(64, 793, 18), // "SCN_INDICATORCLICK"
QT_MOC_LITERAL(65, 812, 20), // "SCN_INDICATORRELEASE"
QT_MOC_LITERAL(66, 833, 15), // "SCN_MACRORECORD"
QT_MOC_LITERAL(67, 849, 3), // "msg"
QT_MOC_LITERAL(68, 853, 6), // "wparam"
QT_MOC_LITERAL(69, 860, 6), // "lparam"
QT_MOC_LITERAL(70, 867, 15), // "SCN_MARGINCLICK"
QT_MOC_LITERAL(71, 883, 6), // "margin"
QT_MOC_LITERAL(72, 890, 20), // "SCN_MARGINRIGHTCLICK"
QT_MOC_LITERAL(73, 911, 12), // "SCN_MODIFIED"
QT_MOC_LITERAL(74, 924, 7), // "modType"
QT_MOC_LITERAL(75, 932, 4), // "text"
QT_MOC_LITERAL(76, 937, 6), // "length"
QT_MOC_LITERAL(77, 944, 10), // "linesAdded"
QT_MOC_LITERAL(78, 955, 12), // "foldLevelNow"
QT_MOC_LITERAL(79, 968, 13), // "foldLevelPrev"
QT_MOC_LITERAL(80, 982, 5), // "token"
QT_MOC_LITERAL(81, 988, 20), // "annotationLinesAdded"
QT_MOC_LITERAL(82, 1009, 19), // "SCN_MODIFYATTEMPTRO"
QT_MOC_LITERAL(83, 1029, 13), // "SCN_NEEDSHOWN"
QT_MOC_LITERAL(84, 1043, 11), // "SCN_PAINTED"
QT_MOC_LITERAL(85, 1055, 17), // "SCN_SAVEPOINTLEFT"
QT_MOC_LITERAL(86, 1073, 20), // "SCN_SAVEPOINTREACHED"
QT_MOC_LITERAL(87, 1094, 15), // "SCN_STYLENEEDED"
QT_MOC_LITERAL(88, 1110, 12), // "SCN_UPDATEUI"
QT_MOC_LITERAL(89, 1123, 7), // "updated"
QT_MOC_LITERAL(90, 1131, 21), // "SCN_USERLISTSELECTION"
QT_MOC_LITERAL(91, 1153, 8), // "SCN_ZOOM"
QT_MOC_LITERAL(92, 1162, 12), // "etextChanged"
QT_MOC_LITERAL(93, 1175, 11), // "etextEdited"
QT_MOC_LITERAL(94, 1187, 22), // "ecursorPositionChanged"
QT_MOC_LITERAL(95, 1210, 1), // "a"
QT_MOC_LITERAL(96, 1212, 1), // "b"
QT_MOC_LITERAL(97, 1214, 14), // "ereturnPressed"
QT_MOC_LITERAL(98, 1229, 16), // "eeditingFinished"
QT_MOC_LITERAL(99, 1246, 11), // "oncellPress"
QT_MOC_LITERAL(100, 1258, 3), // "row"
QT_MOC_LITERAL(101, 1262, 15), // "oncellItemPress"
QT_MOC_LITERAL(102, 1278, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(103, 1296, 11), // "oncellClick"
QT_MOC_LITERAL(104, 1308, 15), // "oncellItemClick"
QT_MOC_LITERAL(105, 1324, 13), // "oncellDBClick"
QT_MOC_LITERAL(106, 1338, 17), // "oncellItemDBClick"
QT_MOC_LITERAL(107, 1356, 11), // "oncellEnter"
QT_MOC_LITERAL(108, 1368, 15), // "oncellItemEnter"
QT_MOC_LITERAL(109, 1384, 12), // "oncellActive"
QT_MOC_LITERAL(110, 1397, 16), // "oncellItemActive"
QT_MOC_LITERAL(111, 1414, 13), // "oncellChanged"
QT_MOC_LITERAL(112, 1428, 17), // "oncellItemChanged"
QT_MOC_LITERAL(113, 1446, 17), // "eselectionChanged"
QT_MOC_LITERAL(114, 1464, 14), // "onValueChanged"
QT_MOC_LITERAL(115, 1479, 11), // "QtProperty*"
QT_MOC_LITERAL(116, 1491, 8), // "property"
QT_MOC_LITERAL(117, 1500, 3) // "val"

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
    "QSCN_SELCHANGED\0yes\0SCN_AUTOCCANCELLED\0"
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
    "SCN_ZOOM\0etextChanged\0etextEdited\0"
    "ecursorPositionChanged\0a\0b\0ereturnPressed\0"
    "eeditingFinished\0oncellPress\0row\0"
    "oncellItemPress\0QTableWidgetItem*\0"
    "oncellClick\0oncellItemClick\0oncellDBClick\0"
    "oncellItemDBClick\0oncellEnter\0"
    "oncellItemEnter\0oncellActive\0"
    "oncellItemActive\0oncellChanged\0"
    "oncellItemChanged\0eselectionChanged\0"
    "onValueChanged\0QtProperty*\0property\0"
    "val"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ActionReceiver[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      75,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  389,    2, 0x08 /* Private */,
       4,    2,  392,    2, 0x08 /* Private */,
       8,    2,  397,    2, 0x08 /* Private */,
       9,    2,  402,    2, 0x08 /* Private */,
      10,    2,  407,    2, 0x08 /* Private */,
      11,    2,  412,    2, 0x08 /* Private */,
      12,    2,  417,    2, 0x08 /* Private */,
      13,    1,  422,    2, 0x08 /* Private */,
      14,    1,  425,    2, 0x08 /* Private */,
      15,    2,  428,    2, 0x08 /* Private */,
      18,    0,  433,    2, 0x08 /* Private */,
      19,    1,  434,    2, 0x08 /* Private */,
      21,    1,  437,    2, 0x08 /* Private */,
      22,    0,  440,    2, 0x08 /* Private */,
      23,    0,  441,    2, 0x08 /* Private */,
      24,    1,  442,    2, 0x08 /* Private */,
      26,    1,  445,    2, 0x08 /* Private */,
      28,    1,  448,    2, 0x08 /* Private */,
      30,    1,  451,    2, 0x08 /* Private */,
      32,    1,  454,    2, 0x08 /* Private */,
      33,    1,  457,    2, 0x08 /* Private */,
      34,    0,  460,    2, 0x08 /* Private */,
      35,    0,  461,    2, 0x08 /* Private */,
      36,    1,  462,    2, 0x08 /* Private */,
      38,    0,  465,    2, 0x08 /* Private */,
      39,    0,  466,    2, 0x08 /* Private */,
      40,    4,  467,    2, 0x08 /* Private */,
      46,    4,  476,    2, 0x08 /* Private */,
      46,    2,  485,    2, 0x08 /* Private */,
      47,    0,  490,    2, 0x08 /* Private */,
      48,    1,  491,    2, 0x08 /* Private */,
      50,    1,  494,    2, 0x08 /* Private */,
      52,    3,  497,    2, 0x08 /* Private */,
      55,    3,  504,    2, 0x08 /* Private */,
      58,    3,  511,    2, 0x08 /* Private */,
      59,    0,  518,    2, 0x08 /* Private */,
      60,    0,  519,    2, 0x08 /* Private */,
      61,    2,  520,    2, 0x08 /* Private */,
      62,    2,  525,    2, 0x08 /* Private */,
      63,    2,  530,    2, 0x08 /* Private */,
      64,    2,  535,    2, 0x08 /* Private */,
      65,    2,  540,    2, 0x08 /* Private */,
      66,    3,  545,    2, 0x08 /* Private */,
      70,    3,  552,    2, 0x08 /* Private */,
      72,    3,  559,    2, 0x08 /* Private */,
      73,   10,  566,    2, 0x08 /* Private */,
      82,    0,  587,    2, 0x08 /* Private */,
      83,    2,  588,    2, 0x08 /* Private */,
      84,    0,  593,    2, 0x08 /* Private */,
      85,    0,  594,    2, 0x08 /* Private */,
      86,    0,  595,    2, 0x08 /* Private */,
      87,    1,  596,    2, 0x08 /* Private */,
      88,    1,  599,    2, 0x08 /* Private */,
      90,    4,  602,    2, 0x08 /* Private */,
      90,    2,  611,    2, 0x08 /* Private */,
      91,    0,  616,    2, 0x08 /* Private */,
      92,    1,  617,    2, 0x08 /* Private */,
      93,    1,  620,    2, 0x08 /* Private */,
      94,    2,  623,    2, 0x08 /* Private */,
      97,    0,  628,    2, 0x08 /* Private */,
      98,    0,  629,    2, 0x08 /* Private */,
      99,    2,  630,    2, 0x08 /* Private */,
     101,    1,  635,    2, 0x08 /* Private */,
     103,    2,  638,    2, 0x08 /* Private */,
     104,    1,  643,    2, 0x08 /* Private */,
     105,    2,  646,    2, 0x08 /* Private */,
     106,    1,  651,    2, 0x08 /* Private */,
     107,    2,  654,    2, 0x08 /* Private */,
     108,    1,  659,    2, 0x08 /* Private */,
     109,    2,  662,    2, 0x08 /* Private */,
     110,    1,  667,    2, 0x08 /* Private */,
     111,    2,  670,    2, 0x08 /* Private */,
     112,    1,  675,    2, 0x08 /* Private */,
     113,    0,  678,    2, 0x08 /* Private */,
     114,    2,  679,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 41, QMetaType::Int, QMetaType::Int, QMetaType::Int,   42,   43,   44,   45,
    QMetaType::Void, 0x80000000 | 41, QMetaType::Int, QMetaType::Int, QMetaType::Int,   42,   43,   44,   45,
    QMetaType::Void, 0x80000000 | 41, QMetaType::Int,   42,   43,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   49,
    QMetaType::Void, QMetaType::Int,   51,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   43,   53,   54,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   43,   56,   57,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   43,   56,   57,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   43,   54,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   43,   54,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   43,   54,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   43,   54,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   43,   54,
    QMetaType::Void, QMetaType::UInt, QMetaType::ULong, QMetaType::VoidStar,   67,   68,   69,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   43,   54,   71,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   43,   54,   71,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 41, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   43,   74,   75,   76,   77,   53,   78,   79,   80,   81,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   43,   76,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   43,
    QMetaType::Void, QMetaType::Int,   89,
    QMetaType::Void, 0x80000000 | 41, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 41, QMetaType::Int,   75,   76,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   95,   96,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  100,    7,
    QMetaType::Void, 0x80000000 | 102,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  100,    7,
    QMetaType::Void, 0x80000000 | 102,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  100,    7,
    QMetaType::Void, 0x80000000 | 102,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  100,    7,
    QMetaType::Void, 0x80000000 | 102,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  100,    7,
    QMetaType::Void, 0x80000000 | 102,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  100,    7,
    QMetaType::Void, 0x80000000 | 102,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 115, QMetaType::Int,  116,  117,

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
        case 24: _t->SCN_AUTOCCANCELLED(); break;
        case 25: _t->SCN_AUTOCCHARDELETED(); break;
        case 26: _t->SCN_AUTOCCOMPLETED((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 27: _t->SCN_AUTOCSELECTION((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 28: _t->SCN_AUTOCSELECTION((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 29: _t->SCEN_CHANGE(); break;
        case 30: _t->SCN_CALLTIPCLICK((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->SCN_CHARADDED((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->SCN_DOUBLECLICK((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 33: _t->SCN_DWELLEND((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 34: _t->SCN_DWELLSTART((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 35: _t->SCN_FOCUSIN(); break;
        case 36: _t->SCN_FOCUSOUT(); break;
        case 37: _t->SCN_HOTSPOTCLICK((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 38: _t->SCN_HOTSPOTDOUBLECLICK((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 39: _t->SCN_HOTSPOTRELEASECLICK((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 40: _t->SCN_INDICATORCLICK((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 41: _t->SCN_INDICATORRELEASE((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 42: _t->SCN_MACRORECORD((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< ulong(*)>(_a[2])),(*reinterpret_cast< void*(*)>(_a[3]))); break;
        case 43: _t->SCN_MARGINCLICK((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 44: _t->SCN_MARGINRIGHTCLICK((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 45: _t->SCN_MODIFIED((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const char*(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8])),(*reinterpret_cast< int(*)>(_a[9])),(*reinterpret_cast< int(*)>(_a[10]))); break;
        case 46: _t->SCN_MODIFYATTEMPTRO(); break;
        case 47: _t->SCN_NEEDSHOWN((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 48: _t->SCN_PAINTED(); break;
        case 49: _t->SCN_SAVEPOINTLEFT(); break;
        case 50: _t->SCN_SAVEPOINTREACHED(); break;
        case 51: _t->SCN_STYLENEEDED((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->SCN_UPDATEUI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 53: _t->SCN_USERLISTSELECTION((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 54: _t->SCN_USERLISTSELECTION((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 55: _t->SCN_ZOOM(); break;
        case 56: _t->etextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 57: _t->etextEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 58: _t->ecursorPositionChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 59: _t->ereturnPressed(); break;
        case 60: _t->eeditingFinished(); break;
        case 61: _t->oncellPress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 62: _t->oncellItemPress((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 63: _t->oncellClick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 64: _t->oncellItemClick((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 65: _t->oncellDBClick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 66: _t->oncellItemDBClick((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 67: _t->oncellEnter((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 68: _t->oncellItemEnter((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 69: _t->oncellActive((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 70: _t->oncellItemActive((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 71: _t->oncellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 72: _t->oncellItemChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 73: _t->eselectionChanged(); break;
        case 74: _t->onValueChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
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
        if (_id < 75)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 75;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 75)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 75;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
