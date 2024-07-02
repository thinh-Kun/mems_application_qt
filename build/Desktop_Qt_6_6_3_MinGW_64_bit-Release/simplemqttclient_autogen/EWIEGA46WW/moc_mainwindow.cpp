/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "setClientPort",
    "",
    "p",
    "plot_chart_cv",
    "plot_chart_eis",
    "cv_add_data",
    "_voltage",
    "_current",
    "eis_add_data",
    "_freq",
    "_mangitude",
    "_phase",
    "on_btnPortInfo_clicked",
    "on_pushButton_2_clicked",
    "readData",
    "on_meansure_Btn_clicked",
    "on_btn_send_control_vol_clicked",
    "on_btn_checkmqtt_clicked",
    "on_box_value_vol1_currentIndexChanged",
    "index",
    "on_btn_clear_chart_clicked",
    "on_plot_data_clicked",
    "on_pushButton_6_clicked",
    "on_sync_btn_4_clicked",
    "on_sync_btn_7_clicked",
    "on_pushButton_3_clicked",
    "on_pushButton_7_clicked",
    "on_pushButton_8_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[58];
    char stringdata0[11];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[2];
    char stringdata4[14];
    char stringdata5[15];
    char stringdata6[12];
    char stringdata7[9];
    char stringdata8[9];
    char stringdata9[13];
    char stringdata10[6];
    char stringdata11[11];
    char stringdata12[7];
    char stringdata13[23];
    char stringdata14[24];
    char stringdata15[9];
    char stringdata16[24];
    char stringdata17[32];
    char stringdata18[25];
    char stringdata19[38];
    char stringdata20[6];
    char stringdata21[27];
    char stringdata22[21];
    char stringdata23[24];
    char stringdata24[22];
    char stringdata25[22];
    char stringdata26[24];
    char stringdata27[24];
    char stringdata28[24];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 13),  // "setClientPort"
        QT_MOC_LITERAL(25, 0),  // ""
        QT_MOC_LITERAL(26, 1),  // "p"
        QT_MOC_LITERAL(28, 13),  // "plot_chart_cv"
        QT_MOC_LITERAL(42, 14),  // "plot_chart_eis"
        QT_MOC_LITERAL(57, 11),  // "cv_add_data"
        QT_MOC_LITERAL(69, 8),  // "_voltage"
        QT_MOC_LITERAL(78, 8),  // "_current"
        QT_MOC_LITERAL(87, 12),  // "eis_add_data"
        QT_MOC_LITERAL(100, 5),  // "_freq"
        QT_MOC_LITERAL(106, 10),  // "_mangitude"
        QT_MOC_LITERAL(117, 6),  // "_phase"
        QT_MOC_LITERAL(124, 22),  // "on_btnPortInfo_clicked"
        QT_MOC_LITERAL(147, 23),  // "on_pushButton_2_clicked"
        QT_MOC_LITERAL(171, 8),  // "readData"
        QT_MOC_LITERAL(180, 23),  // "on_meansure_Btn_clicked"
        QT_MOC_LITERAL(204, 31),  // "on_btn_send_control_vol_clicked"
        QT_MOC_LITERAL(236, 24),  // "on_btn_checkmqtt_clicked"
        QT_MOC_LITERAL(261, 37),  // "on_box_value_vol1_currentInde..."
        QT_MOC_LITERAL(299, 5),  // "index"
        QT_MOC_LITERAL(305, 26),  // "on_btn_clear_chart_clicked"
        QT_MOC_LITERAL(332, 20),  // "on_plot_data_clicked"
        QT_MOC_LITERAL(353, 23),  // "on_pushButton_6_clicked"
        QT_MOC_LITERAL(377, 21),  // "on_sync_btn_4_clicked"
        QT_MOC_LITERAL(399, 21),  // "on_sync_btn_7_clicked"
        QT_MOC_LITERAL(421, 23),  // "on_pushButton_3_clicked"
        QT_MOC_LITERAL(445, 23),  // "on_pushButton_7_clicked"
        QT_MOC_LITERAL(469, 23)   // "on_pushButton_8_clicked"
    },
    "MainWindow",
    "setClientPort",
    "",
    "p",
    "plot_chart_cv",
    "plot_chart_eis",
    "cv_add_data",
    "_voltage",
    "_current",
    "eis_add_data",
    "_freq",
    "_mangitude",
    "_phase",
    "on_btnPortInfo_clicked",
    "on_pushButton_2_clicked",
    "readData",
    "on_meansure_Btn_clicked",
    "on_btn_send_control_vol_clicked",
    "on_btn_checkmqtt_clicked",
    "on_box_value_vol1_currentIndexChanged",
    "index",
    "on_btn_clear_chart_clicked",
    "on_plot_data_clicked",
    "on_pushButton_6_clicked",
    "on_sync_btn_4_clicked",
    "on_sync_btn_7_clicked",
    "on_pushButton_3_clicked",
    "on_pushButton_7_clicked",
    "on_pushButton_8_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  134,    2, 0x0a,    1 /* Public */,
       4,    0,  137,    2, 0x0a,    3 /* Public */,
       5,    0,  138,    2, 0x0a,    4 /* Public */,
       6,    2,  139,    2, 0x0a,    5 /* Public */,
       9,    3,  144,    2, 0x0a,    8 /* Public */,
      13,    0,  151,    2, 0x08,   12 /* Private */,
      14,    0,  152,    2, 0x08,   13 /* Private */,
      15,    0,  153,    2, 0x08,   14 /* Private */,
      16,    0,  154,    2, 0x08,   15 /* Private */,
      17,    0,  155,    2, 0x08,   16 /* Private */,
      18,    0,  156,    2, 0x08,   17 /* Private */,
      19,    1,  157,    2, 0x08,   18 /* Private */,
      21,    0,  160,    2, 0x08,   20 /* Private */,
      22,    0,  161,    2, 0x08,   21 /* Private */,
      23,    0,  162,    2, 0x08,   22 /* Private */,
      24,    0,  163,    2, 0x08,   23 /* Private */,
      25,    0,  164,    2, 0x08,   24 /* Private */,
      26,    0,  165,    2, 0x08,   25 /* Private */,
      27,    0,  166,    2, 0x08,   26 /* Private */,
      28,    0,  167,    2, 0x08,   27 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    7,    8,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   10,   11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'setClientPort'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'plot_chart_cv'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'plot_chart_eis'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cv_add_data'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'eis_add_data'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'on_btnPortInfo_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'readData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_meansure_Btn_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_send_control_vol_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_checkmqtt_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_box_value_vol1_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_btn_clear_chart_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_plot_data_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_6_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_sync_btn_4_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_sync_btn_7_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_3_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_7_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_8_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setClientPort((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->plot_chart_cv(); break;
        case 2: _t->plot_chart_eis(); break;
        case 3: _t->cv_add_data((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        case 4: _t->eis_add_data((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3]))); break;
        case 5: _t->on_btnPortInfo_clicked(); break;
        case 6: _t->on_pushButton_2_clicked(); break;
        case 7: _t->readData(); break;
        case 8: _t->on_meansure_Btn_clicked(); break;
        case 9: _t->on_btn_send_control_vol_clicked(); break;
        case 10: _t->on_btn_checkmqtt_clicked(); break;
        case 11: _t->on_box_value_vol1_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->on_btn_clear_chart_clicked(); break;
        case 13: _t->on_plot_data_clicked(); break;
        case 14: _t->on_pushButton_6_clicked(); break;
        case 15: _t->on_sync_btn_4_clicked(); break;
        case 16: _t->on_sync_btn_7_clicked(); break;
        case 17: _t->on_pushButton_3_clicked(); break;
        case 18: _t->on_pushButton_7_clicked(); break;
        case 19: _t->on_pushButton_8_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 20;
    }
    return _id;
}
QT_WARNING_POP
