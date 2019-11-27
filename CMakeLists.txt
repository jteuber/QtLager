cmake_minimum_required(VERSION 3.15)

project(Core LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(extern/immer extern/lager extern/cereal/include extern/zug)

find_package(Qt5 COMPONENTS Core Quick Qml Concurrent Gui Widgets QuickControls2 REQUIRED)


add_subdirectory(examples/snake)
message("MODEL_HEADER: ${MODEL_HEADER}")
message("ACTIONS_HEADER: ${ACTIONS_HEADER}")
add_compile_definitions(ACTIONS_HEADER=${ACTIONS_HEADER} MODEL_HEADER=${MODEL_HEADER})


set(SOURCES
    private/main.cpp
    private/core.cpp)

set(HEADERS
    private/core.h
    public/reducer.h
    public/view.h
    public/effect_dispatcher.h
    public/model_actions.h)

set(OTHER
    README.md)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${OTHER})
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Qml Qt5::QuickControls2 -lstdc++)
