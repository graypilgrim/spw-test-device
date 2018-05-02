file(GLOB TEST_SOURCES "*.cpp")

add_executable (spw-test-dev-tests ${TEST_SOURCES})

target_link_libraries(spw-test-dev-tests SOURCE_OBJS)
