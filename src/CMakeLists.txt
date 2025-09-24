cmake_minimum_required(VERSION 3.19)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(QMainWindow_Project
    WIN32 MACOSX_BUNDLE
    # Common Section - begin ----------------------------
    lib/QtLib_Project_Template/src/bico_qthread.h
    lib/QtLib_Project_Template/src/bico_qthread.cpp
    lib/QtLib_Project_Template/src/bico_qmessdata.h
    lib/QtLib_Project_Template/src/bico_qmessdata.cpp
    lib/QtLib_Project_Template/src/bico_qmutexqueue.h
    lib/bico_qwindowthread_ui.cpp
    lib/bico_qwindowthread_ui.h
    lib/bico_qwindowthread.cpp
    lib/bico_qwindowthread.h
    # Common Section - end ----------------------------

    # Specific Section - begin ----------------------------
    main.cpp

    Client_Code/Bico_QWindowThread_Sample/Bico_QWindowThread_Sample_UI.cpp
    Client_Code/Bico_QWindowThread_Sample/Bico_QWindowThread_Sample_UI.h
    Client_Code/Bico_QWindowThread_Sample/Bico_QWindowThread_Sample.cpp
    Client_Code/Bico_QWindowThread_Sample/Bico_QWindowThread_Sample.h
    Client_Code/Bico_QWindowThread_Sample/Bico_QWindowThread_Sample_UI.ui
    Client_Code/Bico_QWindowThread_Sample/Data_Object/Bico_QWindowThread_Sample_Data.cpp
    Client_Code/Bico_QWindowThread_Sample/Data_Object/Bico_QWindowThread_Sample_Data.h

    Client_Code/Task_1/Task_1_UI.cpp
    Client_Code/Task_1/Task_1_UI.h
    Client_Code/Task_1/Task_1.cpp
    Client_Code/Task_1/Task_1.h
    Client_Code/Task_1/Task_1_UI.ui
    Client_Code/Task_1/Data_Object/Task_1_Data.cpp
    Client_Code/Task_1/Data_Object/Task_1_Data.h
    # Specific Section - end ----------------------------
)

target_include_directories(QMainWindow_Project
    PRIVATE
        # Common Section - begin ----------------------------
        lib
        lib/QtLib_Project_Template/src
        # Common Section - end ----------------------------
        
        # Specific Section - begin ----------------------------
        Client_Code/Task_1
        Client_Code/Bico_QWindowThread_Sample
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
