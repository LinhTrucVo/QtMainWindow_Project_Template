include(Client_Code/Task1/Task1_Paths.cmake)

qt_add_executable(QMainWindow_Project
    WIN32 MACOSX_BUNDLE
    # Common Section - begin ----------------------------
    lib/QtLib_Project_Template/src/bico_qthread.cpp
    lib/QtLib_Project_Template/src/bico_qmessdata.cpp
    lib/bico_qwindowthread_ui.cpp
    lib/bico_qwindowthread.cpp
    # Common Section - end ----------------------------
    
    main.cpp

    # Specific Section - begin ----------------------------
    ${TASK1_SOURCE_FILES}
    # Specific Section - end ----------------------------
)

target_include_directories(QMainWindow_Project
    PRIVATE
        # Common Section - begin ----------------------------
        lib
        lib/QtLib_Project_Template/src
        # Common Section - end ----------------------------
        
        # Specific Section - begin ----------------------------
        ${TASK1_INCLUDE_DIRS}
        # Specific Section - end ----------------------------
)


















target_link_libraries(QMainWindow_Project
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS QMainWindow_Project
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
    
qt_generate_deploy_app_script(
    TARGET QMainWindow_Project
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
