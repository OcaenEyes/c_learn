cmake_minimum_required(VERSION 3.14)

project(ocean_markdown VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick LinguistTools WebEngineQuick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick LinguistTools WebEngineQuick)


set(TS_FILES language/ocean_markdown_zh_CN.ts)

set(PROJECT_SOURCES
        source/main.cpp
        source/markdowncore.h
        source/markdowncore.cpp

        source/filelistmodel.h
        source/filelistmodel.cpp
        source/filefolderpathindir.h
        source/filefolderpathindir.cpp
        source/filefoldername.h
        ui/qml.qrc

        3rdparty/js/qwebchannel.js
        3rdparty/js/showdown.js
        3rdparty/js/marked.min.js
        3rdparty/js/marked_with_katex.js
        3rdparty/js/katex.min.js
        3rdparty/css/katex.min.css

        3rdparty/fonts/KaTeX_Main-Regular.woff2
        3rdparty/fonts/KaTeX_Math-Italic.woff2
        3rdparty/fonts/KaTeX_Size3-Regular.woff2
        3rdparty/fonts/KaTeX_Main-Regular.woff
        3rdparty/fonts/KaTeX_Math-Italic.woff
        3rdparty/fonts/KaTeX_Size3-Regular.woff
        3rdparty/fonts/KaTeX_Main-Regular.ttf
        3rdparty/fonts/KaTeX_Math-Italic.ttf
        3rdparty/fonts/KaTeX_Size3-Regular.ttf
        3rdparty/fonts/KaTeX_Size4-Regular.woff2

        3rdparty/css/sspai.css
        3rdparty/css/han.css
        3rdparty/css/mdhere.css
        3rdparty/css/businessblue.css
        3rdparty/css/github.css

        3rdparty/css/wechatallblue.css
        3rdparty/css/wechatazure.css
        3rdparty/css/wechatgeekblack.css
        3rdparty/css/wechatinkblack.css
        3rdparty/css/wechatmountain.css

        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    if(WIN32)
        set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/icon.rc")
        qt_add_executable(ocean_markdown
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            ${app_icon_resource_windows}
        )
    elseif(APPLE)
        set(MACOSX_BUNDLE_ICON_FILE icon.icns)
        set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/icon.icns")
        set_source_files_properties(${app_icon_macos} PROPERTIES
               MACOSX_PACKAGE_LOCATION "Resources")

        qt_add_executable(ocean_markdown
            MACOSX_BUNDLE
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            ${app_icon_macos}
        )
    endif()
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(ocean_markdown SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ocean_markdown
          ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(ocean_markdown
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::WebEngineQuick)

set_target_properties(ocean_markdown PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.gzy.oceanmarkdown
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ocean_markdown
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(ocean_markdown)
    qt_finalize_executable(ocean_markdown)
endif()
