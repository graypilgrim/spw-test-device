file(GLOB TEST_SOURCES "*.cpp")

#include_directories(${PROJECT_SOURCE_DIR}/tests/lib)

add_executable (spw-test-dev-tests ${TEST_SOURCES})

target_link_libraries(spw-test-dev-tests SOURCE_OBJS)
