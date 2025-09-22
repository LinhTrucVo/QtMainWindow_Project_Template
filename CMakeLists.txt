cmake_minimum_required(VERSION 3.19)
project(QMainWindow_Project LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(QMainWindow_Project
    WIN32 MACOSX_BUNDLE
    # Common Section - begin ----------------------------
    Template_Material/Common/bico_qthread.h
    Template_Material/Common/bico_qthread.cpp
    Template_Material/Common/bico_qmessdata.h
    Template_Material/Common/bico_qmessdata.cpp
    Template_Material/Common/bico_qmutexqueue.h
    Template_Material/bico_qwindowthread_ui.cpp
    Template_Material/bico_qwindowthread_ui.h
    Template_Material/bico_qwindowthread.cpp
    Template_Material/bico_qwindowthread.h
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
