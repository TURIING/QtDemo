cmake_minimum_required(VERSION 3.25)
project(QtDemo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.14.2/5.14.2/mingw73_64")
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Svg
        Charts
        REQUIRED)
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/MovableTableView )
add_executable(QtDemo main.cpp iplineedit.cpp iplineedit.h mainwindow.cpp mainwindow.h mainwindow.ui ColorPicker.cpp ColorPicker.h GifCapture.cpp GifCapture.h Battery.cpp Battery.h ScrollText.h ScrollText.cpp SphericalProgressBar.cpp SphericalProgressBar.h DiskSpace.cpp DiskSpace.h DateRollBox.cpp DateRollBox.h Marquee.cpp Marquee.h EdgeHide.cpp EdgeHide.h SwitchButton.cpp SwitchButton.h MenuSwitcher.cpp MenuSwitcher.h graphicseffect.cpp graphicseffect.h graphicseffect.ui resources.qrc PageSwitcher.cpp PageSwitcher.h AnimationButton.cpp AnimationButton.h MovableTableView/MovableTableView.cpp MovableTableView/MovableTableView.h FrameLessWindow/FrameLessWindow.cpp FrameLessWindow/FrameLessWindow.h FrameLessWindow/TitleBar.cpp FrameLessWindow/TitleBar.h FrameLessWindow/windoweffect.h FrameLessWindow/windoweffect.cpp SketchBoard/SketchBoard.h Charts/CurveChart.h Charts/AreaChart.h Charts/BarChart.h)
target_link_libraries(QtDemo
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Svg
        Qt5::Charts
        dwmapi.dll
        )
if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets Svg Charts)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
