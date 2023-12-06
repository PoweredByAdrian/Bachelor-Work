cmake_minimum_required(VERSION 3.5)

project(DukeGame VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DukeGame
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        cell.h cell.cpp
        figure.h figure.cpp
        p_duke.h p_duke.cpp
        p_bowman.h p_bowman.cpp
        p_dracoon.h p_dracoon.cpp
        p_assassin.h p_assassin.cpp
        p_champion.h p_champion.cpp
        p_footman.h p_footman.cpp
        p_general.h p_general.cpp
        p_marshall.h p_marshall.cpp
        p_priest.h p_priest.cpp
        p_knight.h p_knight.cpp
        p_pikeman.h p_pikeman.cpp
        p_seer.h p_seer.cpp
        p_wizard.h p_wizard.cpp
        figurebag.h figurebag.cpp
        player.h player.cpp
        p_longbowman.h p_longbowman.cpp
        enums.h
        connectionmanager.h connectionmanager.cpp
        gameconfigure.h gameconfigure.cpp
        gameinterface.h gameinterface.cpp
        gamelogic.h gamelogic.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DukeGame APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DukeGame SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DukeGame
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DukeGame PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DukeGame)
endif()
set_target_properties(DukeGame PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DukeGame
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DukeGame)
endif()
