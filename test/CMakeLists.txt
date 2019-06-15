set(UNIT_TEST grabberTest)

include_directories(${${PROJECT_NAME}_SOURCE_DIR}/src )
add_executable(${UNIT_TEST} GrabberTest.cpp GrabberTest.h)
target_link_libraries(${UNIT_TEST} ${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Test)
add_custom_command(
    TARGET ${UNIT_TEST}
    COMMENT "Run tests"
    POST_BUILD
    COMMAND ${UNIT_TEST}
)
