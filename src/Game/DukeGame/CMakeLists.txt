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
        Game/mainwindow.cpp
        Game/mainwindow.h
        Game/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DukeGame
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Game/cell.h Game/cell.cpp
        Game/figure.h Game/figure.cpp
        Game/p_duke.h Game/p_duke.cpp
        Game/p_bowman.h Game/p_bowman.cpp
        Game/p_dracoon.h Game/p_dracoon.cpp
        Game/p_assassin.h Game/p_assassin.cpp
        Game/p_champion.h Game/p_champion.cpp
        Game/p_footman.h Game/p_footman.cpp
        Game/p_general.h Game/p_general.cpp
        Game/p_marshall.h Game/p_marshall.cpp
        Game/p_priest.h Game/p_priest.cpp
        Game/p_knight.h Game/p_knight.cpp
        Game/p_pikeman.h Game/p_pikeman.cpp
        Game/p_seer.h Game/p_seer.cpp
        Game/p_wizard.h Game/p_wizard.cpp
        Game/figurebag.h Game/figurebag.cpp
        Game/player.h Game/player.cpp
        Game/p_longbowman.h Game/p_longbowman.cpp
        Game/enums.h
        Game/connectionmanager.h Game/connectionmanager.cpp
        Game/gameconfigure.h Game/gameconfigure.cpp
        Game/gameinterface.h Game/gameinterface.cpp
        Game/gamelogic.h Game/gamelogic.cpp
        TODO
        Game/debugmanager.h Game/debugmanager.cpp
        Game/movesimulator.h Game/movesimulator.cpp
        Game/cellinfo.h Game/cellinfo.cpp

        Algorithms/ExpMinMax/expectiminimax.h Algorithms/ExpMinMax/expectiminimax.cpp


        Algorithms/MCTS/mctsnode.h Algorithms/MCTS/mctsnode.cpp
        Algorithms/MCTS/mctsnode.h Algorithms/MCTS/mctsnode.cpp
        Algorithms/MCTS/Action.h




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
