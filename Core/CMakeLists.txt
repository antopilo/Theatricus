set(HEADERS Core.h Node.h Slate.h)
set(SOURCES Core.cpp)

add_subdirectory(Dependencies/)

add_library(Core ${HEADERS} ${SOURCES})

set_property(TARGET Core PROPERTY CXX_STANDARD 20)
target_link_libraries(Core PUBLIC NuakeRenderer)
target_include_directories(Core PUBLIC Dependencies/NuakeRenderer/)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS} ${SOURCES})
