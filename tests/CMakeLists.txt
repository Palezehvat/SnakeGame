add_executable(tests snaketests.cpp boardtests.cpp foodtests.cpp)

set_target_properties(tests PROPERTIES
    AUTOMOC OFF
    AUTOUIC OFF
    AUTORCC OFF
)

target_link_libraries(tests
    PRIVATE
    snake
    food
    board
    score
    logger
    app
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    GTest::GTest
    GTest::Main
)

include(GoogleTest)
gtest_discover_tests(tests)