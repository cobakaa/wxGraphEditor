cmake_minimum_required(VERSION 3.16)
project(wxPaintingTest)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        include
        C:/wxWidgets-3.1.4
        C:/wxWidgets-3.1.4/include
        C:/wxWidgets-3.1.4/cmake/debug/lib/wx/include/msw-unicode-3.1
)

link_directories(
        C:/wxWidgets-3.1.4/cmake/debug/lib/
        #C:/wxWidgets-3.1.4/lib/gcc_dll/mswud
)

add_executable(wxPaintingTest
        include/customDialog.h
        include/graph.h
        include/gui.h
        include/guifrmMain.h
        include/node.h
        include/tools.h
        src/customDialog.cpp
        src/graph.cpp
        src/gui.cpp
        src/guifrmMain.cpp
        src/main.cpp
        src/node.cpp
        src/tools.cpp)


set(
        WX_LIBS
        libwx_mswud_propgrid-3.1.dll.a
        libwx_mswud_ribbon-3.1.dll.a
        libwx_mswud_stc-3.1.dll.a
        libwx_mswud_webview-3.1.dll.a
        libwx_mswud_gl-3.1.dll.a
        libwx_mswud_richtext-3.1.dll.a
        libwx_mswud_xrc-3.1.dll.a
        libwx_mswud_aui-3.1.dll.a
        libwx_mswud_html-3.1.dll.a
        libwx_mswud_adv-3.1.dll.a
        libwx_mswud_core-3.1.dll.a
        libwx_baseud_xml-3.1.dll.a
        libwx_baseud_net-3.1.dll.a
        libwx_baseud-3.1.dll.a
        libwxscintillad.a
        libwxtiffd.a
        libwxjpegd.a
        libwxpngd.a
        libwxzlibd.a
        libwxregexud.a
        libwxexpatd.a
        libwx_mswud_media-3.1.dll.a

)

target_link_libraries(
        ${PROJECT_NAME}
        ${WX_LIBS}
)
