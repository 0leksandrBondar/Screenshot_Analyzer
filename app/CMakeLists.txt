set(SOURCE
    dbmanager/dbmanager.cpp
    widgets/tableview.cpp
    widgets/controlbar.cpp
    appcontroller.cpp
    screenshotcontroller.cpp
    mainwindow.cpp
    main.cpp)

set(HEADERS
    dbmanager/dbmanager.h
    widgets/tableview.h
    widgets/controlbar.h
    appcontroller.h
    screenshotcontroller.h
    mainwindow.h)

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})

target_link_libraries(${PROJECT_NAME}
  PRIVATE
   Qt6::Widgets
   Qt6::Core
   Qt6::Sql
 )
