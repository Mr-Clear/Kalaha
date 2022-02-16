set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock gtest_main pthread)

include(../CodeCoverage.cmake)
append_coverage_compiler_flags()
setup_target_for_coverage_gcovr_html(NAME ${PROJECT_NAME}_coverage EXECUTABLE ${PROJECT_NAME}
                               DEPENDENCIES ${PROJECT_NAME})
