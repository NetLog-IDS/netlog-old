add_executable(nped 
        sniffer.cpp
        app.cpp
        main.cpp
)

set_target_properties(nped
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

target_link_libraries(nped PRIVATE cclap PRIVATE tins)
target_include_directories(nped PRIVATE ${CMAKE_SOURCE_DIR}/include PRIVATE ${cclap_SOURCE_DIR}/include)

