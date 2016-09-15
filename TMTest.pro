TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

QT     += core
QT     += gui

#edited for openCV3.0
#搴撳紩鍏ユ柟�#INCLUDEPATH += E:/QTPrj/QtOpenCV3/include
#LIBS += -LE:/QTPrj/QtOpenCV3/lib\
#INCLUDEPATH += D:/Qt/QtLibs/install_qt_world/include
#LIBS += -LD:/Qt/QtLibs/install_qt_world/x86/mingw/lib\
#-llibopencv_world300

INCLUDEPATH += D:/Qt/QtLibs/install_qt_qt/include
LIBS += -LD:/Qt/QtLibs/install_qt_qt/x86/mingw/lib\
-llibopencv_calib3d300\
-llibopencv_core300\
-llibopencv_features2d300\
-llibopencv_flann300\
-llibopencv_highgui300\
-llibopencv_imgcodecs300\
-llibopencv_imgproc300\
-llibopencv_ml300\
-llibopencv_objdetect300\
-llibopencv_photo300\
-llibopencv_shape300\
-llibopencv_stitching300\
-llibopencv_superres300\
-lopencv_hal300
#搴撳紩鍏ユ柟�#INCLUDEPATH += E:/QTPrj/QtOpenCV3/include
#LIBS += -L E:/QTPrj/QtOpenCV3/lib/libopencv_*.a

#edited for boost1.6.0
#static library
DEFINES += BOOST_THREAD_USE_LIB
INCLUDEPATH += D:/Qt/QtLibs/boost/include
LIBS += -LD:/Qt/QtLibs/boost/lib\
-lboost_atomic-mgw49-mt-s-1_60\
-lboost_atomic-mgw49-mt-sd-1_60\
-lboost_chrono-mgw49-mt-s-1_60\
-lboost_chrono-mgw49-mt-sd-1_60\
-lboost_container-mgw49-mt-s-1_60\
-lboost_container-mgw49-mt-sd-1_60\
-lboost_context-mgw49-mt-s-1_60\
-lboost_context-mgw49-mt-sd-1_60\
-lboost_coroutine-mgw49-mt-s-1_60\
-lboost_coroutine-mgw49-mt-sd-1_60\
-lboost_date_time-mgw49-mt-s-1_60\
-lboost_date_time-mgw49-mt-sd-1_60\
-lboost_exception-mgw49-mt-s-1_60\
-lboost_exception-mgw49-mt-sd-1_60\
-lboost_filesystem-mgw49-mt-s-1_60\
-lboost_filesystem-mgw49-mt-sd-1_60\
-lboost_iostreams-mgw49-mt-s-1_60\
-lboost_iostreams-mgw49-mt-sd-1_60\
-lboost_locale-mgw49-mt-s-1_60\
-lboost_locale-mgw49-mt-sd-1_60\
-lboost_log-mgw49-mt-s-1_60\
-lboost_log-mgw49-mt-sd-1_60\
-lboost_log_setup-mgw49-mt-s-1_60\
-lboost_log_setup-mgw49-mt-sd-1_60\
-lboost_math_c99-mgw49-mt-s-1_60\
-lboost_math_c99-mgw49-mt-sd-1_60\
-lboost_math_c99f-mgw49-mt-s-1_60\
-lboost_math_c99f-mgw49-mt-sd-1_60\
-lboost_math_c99l-mgw49-mt-s-1_60\
-lboost_math_c99l-mgw49-mt-sd-1_60\
-lboost_math_tr1-mgw49-mt-s-1_60\
-lboost_math_tr1-mgw49-mt-sd-1_60\
-lboost_math_tr1f-mgw49-mt-s-1_60\
-lboost_math_tr1f-mgw49-mt-sd-1_60\
-lboost_math_tr1l-mgw49-mt-s-1_60\
-lboost_math_tr1l-mgw49-mt-sd-1_60\
-lboost_prg_exec_monitor-mgw49-mt-s-1_60\
-lboost_prg_exec_monitor-mgw49-mt-sd-1_60\
-lboost_program_options-mgw49-mt-s-1_60\
-lboost_program_options-mgw49-mt-sd-1_60\
-lboost_python-mgw49-mt-s-1_60\
-lboost_python-mgw49-mt-sd-1_60\
-lboost_python3-mgw49-mt-s-1_60\
-lboost_python3-mgw49-mt-sd-1_60\
-lboost_random-mgw49-mt-s-1_60\
-lboost_random-mgw49-mt-sd-1_60\
-lboost_regex-mgw49-mt-s-1_60\
-lboost_regex-mgw49-mt-sd-1_60\
-lboost_serialization-mgw49-mt-s-1_60\
-lboost_serialization-mgw49-mt-sd-1_60\
-lboost_signals-mgw49-mt-s-1_60\
-lboost_signals-mgw49-mt-sd-1_60\
-lboost_system-mgw49-mt-s-1_60\
-lboost_system-mgw49-mt-sd-1_60\
-lboost_test_exec_monitor-mgw49-mt-s-1_60\
-lboost_test_exec_monitor-mgw49-mt-sd-1_60\
-lboost_thread-mgw49-mt-s-1_60\
-lboost_thread-mgw49-mt-sd-1_60\
-lboost_timer-mgw49-mt-s-1_60\
-lboost_timer-mgw49-mt-sd-1_60\
-lboost_type_erasure-mgw49-mt-s-1_60\
-lboost_type_erasure-mgw49-mt-sd-1_60\
-lboost_unit_test_framework-mgw49-mt-s-1_60\
-lboost_unit_test_framework-mgw49-mt-sd-1_60\
-lboost_wserialization-mgw49-mt-s-1_60\
-lboost_wserialization-mgw49-mt-sd-1_60
#dynamic library
#-lboost_atomic-mgw49-mt-1_60\
#-lboost_atomic-mgw49-mt-d-1_60\
#-lboost_chrono-mgw49-mt-1_60\
#-lboost_chrono-mgw49-mt-d-1_60\
#-lboost_container-mgw49-mt-1_60\
#-lboost_container-mgw49-mt-d-1_60\
#-lboost_context-mgw49-mt-1_60\
#-lboost_context-mgw49-mt-d-1_60\
#-lboost_coroutine-mgw49-mt-1_60\
#-lboost_coroutine-mgw49-mt-d-1_60\
#-lboost_date_time-mgw49-mt-1_60\
#-lboost_date_time-mgw49-mt-d-1_60\
#-lboost_exception-mgw49-mt-1_60\
#-lboost_exception-mgw49-mt-d-1_60\
#-lboost_filesystem-mgw49-mt-1_60\
#-lboost_filesystem-mgw49-mt-d-1_60\
#-lboost_iostreams-mgw49-mt-1_60\
#-lboost_iostreams-mgw49-mt-d-1_60\
#-lboost_locale-mgw49-mt-1_60\
#-lboost_locale-mgw49-mt-d-1_60\
#-lboost_log-mgw49-mt-1_60\
#-lboost_log-mgw49-mt-d-1_60\
#-lboost_log_setup-mgw49-mt-1_60\
#-lboost_log_setup-mgw49-mt-d-1_60\
#-lboost_math_c99-mgw49-mt-1_60\
#-lboost_math_c99-mgw49-mt-d-1_60\
#-lboost_math_c99f-mgw49-mt-1_60\
#-lboost_math_c99f-mgw49-mt-d-1_60\
#-lboost_math_c99l-mgw49-mt-1_60\
#-lboost_math_c99l-mgw49-mt-d-1_60\
#-lboost_math_tr1-mgw49-mt-1_60\
#-lboost_math_tr1-mgw49-mt-d-1_60\
#-lboost_math_tr1f-mgw49-mt-1_60\
#-lboost_math_tr1f-mgw49-mt-d-1_60\
#-lboost_math_tr1l-mgw49-mt-1_60\
#-lboost_math_tr1l-mgw49-mt-d-1_60\
#-lboost_prg_exec_monitor-mgw49-mt-1_60\
#-lboost_prg_exec_monitor-mgw49-mt-d-1_60\
#-lboost_program_options-mgw49-mt-1_60\
#-lboost_program_options-mgw49-mt-d-1_60\
#-lboost_python-mgw49-mt-1_60\
#-lboost_python-mgw49-mt-d-1_60\
#-lboost_python3-mgw49-mt-1_60\
#-lboost_python3-mgw49-mt-d-1_60\
#-lboost_random-mgw49-mt-1_60\
#-lboost_random-mgw49-mt-d-1_60\
#-lboost_regex-mgw49-mt-1_60\
#-lboost_regex-mgw49-mt-d-1_60\
#-lboost_serialization-mgw49-mt-1_60\
#-lboost_serialization-mgw49-mt-d-1_60\
#-lboost_signals-mgw49-mt-1_60\
#-lboost_signals-mgw49-mt-d-1_60\
#-lboost_system-mgw49-mt-1_60\
#-lboost_system-mgw49-mt-d-1_60\
#-lboost_test_exec_monitor-mgw49-mt-1_60\
#-lboost_test_exec_monitor-mgw49-mt-d-1_60\
#-lboost_thread-mgw49-mt-1_60\
#-lboost_thread-mgw49-mt-d-1_60\
#-lboost_timer-mgw49-mt-1_60\
#-lboost_timer-mgw49-mt-d-1_60\
#-lboost_type_erasure-mgw49-mt-1_60\
#-lboost_type_erasure-mgw49-mt-d-1_60\
#-lboost_unit_test_framework-mgw49-mt-1_60\
#-lboost_unit_test_framework-mgw49-mt-d-1_60\
#-lboost_wserialization-mgw49-mt-1_60\
#-lboost_wserialization-mgw49-mt-d-1_60

#edited for GDAL200
INCLUDEPATH += D:/Qt/QtLibs/gdal/include
LIBS += -LD:/Qt/QtLibs/gdal/lib\
-lgdal

SOURCES += main.cpp \
    kmatchcore.cpp \
    kbbs.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    kmatchcore.h \
    kbbs.h

