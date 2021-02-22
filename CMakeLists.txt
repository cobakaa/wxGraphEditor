cmake_minimum_required(VERSION 3.16)
project(wxPaintingTest)

set(CMAKE_CXX_STANDARD 14)


if (UNIX)
        SET(wxWidgets_USE_LIBS)
        FIND_PACKAGE(wxWidgets)
        IF(wxWidgets_FOUND)
                INCLUDE("${wxWidgets_USE_FILE}")
        # and for each of your dependant executable/library targets:
        ELSE(wxWidgets_FOUND)
        # For convenience. When we cannot continue, inform the user
                MESSAGE("wxWidgets not found!")
        ENDIF(wxWidgets_FOUND)
elseif (WIN32)

        if (CMAKE_BUILD_TYPE MATCHES Debug)

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

                set(
                        wxWidgets_LIBRARIES
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
        elseif(CMAKE_BUILD_TYPE MATCHES Release)
                include_directories(
                        include
                        C:/wxWidgets-3.1.4
                        C:/wxWidgets-3.1.4/include
                        C:/wxWidgets-3.1.4/cmake/release/lib/wx/include/msw-unicode-3.1
                )

                link_directories(
                        C:/wxWidgets-3.1.4/cmake/release/lib/
                        #C:/wxWidgets-3.1.4/lib/gcc_dll/mswud
                )

                set(
                        wxWidgets_LIBRARIES
                        libwx_mswu_propgrid-3.1.dll.a
                        libwx_mswu_ribbon-3.1.dll.a
                        libwx_mswu_stc-3.1.dll.a
                        libwx_mswu_webview-3.1.dll.a
                        libwx_mswu_gl-3.1.dll.a
                        libwx_mswu_richtext-3.1.dll.a
                        libwx_mswu_xrc-3.1.dll.a
                        libwx_mswu_aui-3.1.dll.a
                        libwx_mswu_html-3.1.dll.a
                        libwx_mswu_adv-3.1.dll.a
                        libwx_mswu_core-3.1.dll.a
                        libwx_baseu_xml-3.1.dll.a
                        libwx_baseu_net-3.1.dll.a
                        libwx_baseu-3.1.dll.a
                        libwxscintilla.a
                        libwxtiff.a
                        libwxjpeg.a
                        libwxpng.a
                        libwxzlib.a
                        libwxregexu.a
                        libwxexpat.a
                        libwx_mswu_media-3.1.dll.a

                )
        endif ()

endif ()

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


        target_link_libraries(
                ${PROJECT_NAME}
                ${wxWidgets_LIBRARIES}
        )