set(SOURCE
    dbmanager/dbmanager.cpp
    widgets/tableview.cpp
    widgets/controlbar.cpp
    appcontroller.cpp
    screencontroller.cpp
    mainwindow.cpp
    main.cpp)

set(HEADERS
    dbmanager/dbmanager.h
    widgets/tableview.h
    widgets/controlbar.h
    appcontroller.h
    screencontroller.h
    mainwindow.h)

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})

target_link_libraries(${PROJECT_NAME}
  PRIVATE
   Qt5::Widgets
   Qt5::Core
   Qt5::Sql
 )
