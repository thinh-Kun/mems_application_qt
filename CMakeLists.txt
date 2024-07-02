# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(simplemqttclient LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/mqtt/simpleclient")

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Network)
find_package(Qt6 COMPONENTS Mqtt)
find_package(Qt6 COMPONENTS SerialPort)
find_package(Qt6 COMPONENTS PrintSupport)

find_package(Qt6 COMPONENTS Widgets) # special case
qt_add_executable(simplemqttclient
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    qcustomplot.h qcustomplot.cpp
    picture.qrc
)

set_target_properties(simplemqttclient PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_compile_definitions(simplemqttclient PUBLIC
    QT_DEPRECATED_WARNINGS
)

target_link_libraries(simplemqttclient PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Mqtt
    Qt::Network
    Qt::SerialPort
    Qt6::Widgets Qt6::PrintSupport
)

target_link_libraries(simplemqttclient PUBLIC Qt::Widgets)

if((QT_MAJOR_VERSION GREATER 4))
    target_link_libraries(simplemqttclient PUBLIC
        Qt::Widgets
    )
endif()

install(TARGETS simplemqttclient
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
