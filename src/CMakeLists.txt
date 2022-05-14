add_executable(spoofy 
        sniffer.cpp
        spoofer.cpp
        sender.cpp
        app.cpp
        main.cpp
)

set_target_properties(spoofy
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

target_link_libraries(spoofy PRIVATE cclap PRIVATE tins)
target_include_directories(spoofy PRIVATE ${CMAKE_SOURCE_DIR}/include PRIVATE ${cclap_SOURCE_DIR}/include)

