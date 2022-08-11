set(HEADERS TestFolder/test.h)
set(SOURCES main.cpp)

add_executable(TheatricusStudio ${HEADERS} ${SOURCES})
set_property(TARGET TheatricusStudio PROPERTY CXX_STANDARD 20)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS} ${SOURCES})

target_link_libraries(TheatricusStudio PUBLIC Core)
target_include_directories(TheatricusStudio PUBLIC ../Core)