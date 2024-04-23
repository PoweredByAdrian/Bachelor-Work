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
        Game/GameComponents/cell.h Game/GameComponents/cell.cpp
        Game/GameComponents/Figures/figure.h Game/GameComponents/Figures/figure.cpp
        Game/GameComponents/Figures/p_duke.h Game/GameComponents/Figures/p_duke.cpp
        Game/GameComponents/Figures/p_bowman.h Game/GameComponents/Figures/p_bowman.cpp
        Game/GameComponents/Figures/p_dracoon.h Game/GameComponents/Figures/p_dracoon.cpp
        Game/GameComponents/Figures/p_assassin.h Game/GameComponents/Figures/p_assassin.cpp
        Game/GameComponents/Figures/p_champion.h Game/GameComponents/Figures/p_champion.cpp
        Game/GameComponents/Figures/p_footman.h Game/GameComponents/Figures/p_footman.cpp
        Game/GameComponents/Figures/p_general.h Game/GameComponents/Figures/p_general.cpp
        Game/GameComponents/Figures/p_marshall.h Game/GameComponents/Figures/p_marshall.cpp
        Game/GameComponents/Figures/p_priest.h Game/GameComponents/Figures/p_priest.cpp
        Game/GameComponents/Figures/p_knight.h Game/GameComponents/Figures/p_knight.cpp
        Game/GameComponents/Figures/p_pikeman.h Game/GameComponents/Figures/p_pikeman.cpp
        Game/GameComponents/Figures/p_seer.h Game/GameComponents/Figures/p_seer.cpp
        Game/GameComponents/Figures/p_wizard.h Game/GameComponents/Figures/p_wizard.cpp
        Game/GameComponents/figurebag.h Game/GameComponents/figurebag.cpp
        Game/GameComponents/player.h Game/GameComponents/player.cpp
        Game/GameComponents/Figures/p_longbowman.h Game/GameComponents/Figures/p_longbowman.cpp
        Game/enums.h
        Game/connectionmanager.h Game/connectionmanager.cpp
        Game/GameComponents/gameconfigure.h Game/GameComponents/gameconfigure.cpp
        Game/gameinterface.h Game/gameinterface.cpp
        Game/gamelogic.h Game/gamelogic.cpp
        TODO
        Game/debugmanager.h Game/debugmanager.cpp
        Game/movesimulator.h Game/movesimulator.cpp



        Algorithms/ExpMinMax/expectiminimax.h Algorithms/ExpMinMax/expectiminimax.cpp


        Algorithms/MCTS/mctsnode.h Algorithms/MCTS/mctsnode.cpp
        Algorithms/MCTS/Action.h
        Game/GameComponents/GameState.h
        Algorithms/FinalMove.h




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
