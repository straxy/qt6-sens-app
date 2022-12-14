cmake_minimum_required(VERSION 3.16)

project(qt6-sens VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Widgets REQUIRED)

file(GLOB SOURCES "src/*.cpp")

qt_add_executable(qt6-sens-app ${SOURCES})

set_source_files_properties(qml/main.qml PROPERTIES
    QT_RESOURCE_ALIAS main.qml
)

qt_add_qml_module(qt6-sens-app
    URI qt6sens
    VERSION 1.0
    QML_FILES qml/main.qml
)

target_link_libraries(qt6-sens-app
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Widgets)

install(TARGETS qt6-sens-app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
