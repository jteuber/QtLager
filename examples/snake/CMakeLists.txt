cmake_minimum_required(VERSION 3.15)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../.. ../../extern/immer ../../extern/lager ../../extern/zug)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)


######## MODEL ########

set(MODEL_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/model.h)
set(MODEL_HEADER ${MODEL_HEADER} PARENT_SCOPE)
add_compile_definitions(MODEL_HEADER=${MODEL_HEADER})


######## ACTION ########

set(ACTIONS_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/actions.h)
set(ACTIONS_HEADER ${ACTIONS_HEADER} PARENT_SCOPE)
add_compile_definitions(ACTIONS_HEADER=${ACTIONS_HEADER})


# add custom target for IDEs
add_custom_target(headers SOURCES ${ACTIONS_HEADER} ${MODEL_HEADER})


######## VIEW ########
project(ExampleView LANGUAGES CXX)

set(SOURCES
    View/ExampleView.cpp)
set(HEADERS
    View/ExampleView.h)

set(OTHER
    View/qml.qrc)

set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Views )

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS} ${OTHER})
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick)


######## REDUCER ########
project(ExampleReducer LANGUAGES CXX)

set(SOURCES
    Reducer/ExampleReducer.cpp)
set(HEADERS
    Reducer/ExampleReducer.h)

set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Reducers )

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick)
