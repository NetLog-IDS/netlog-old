if (SPOOFY_BUILD_TESTS)
    include (CTest)
    include (Catch)

    add_library(sniffer ${CMAKE_SOURCE_DIR}/src/sniffer.cpp)
    target_link_libraries(sniffer PRIVATE tins)
    target_include_directories(sniffer PRIVATE ${CMAKE_SOURCE_DIR}/include ${libtins_SOURCE_DIR}/include)

    add_executable(editor_test editor_test.cpp)
    target_link_libraries(editor_test PRIVATE Catch2::Catch2WithMain PRIVATE sniffer) 
    target_include_directories(editor_test PRIVATE ${CMAKE_SOURCE_DIR}/include ${libtins_SOURCE_DIR}/include)

    catch_discover_tests(editor_test)
endif()
