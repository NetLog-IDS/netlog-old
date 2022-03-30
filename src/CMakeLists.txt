add_executable(nped 
        capture.h
        capture.cpp
        main.cpp
)

set_target_properties(nped
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

target_link_libraries(nped PRIVATE cclap PRIVATE tins PRIVATE Catch2::Catch2WithMain)
target_include_directories(nped PRIVATE ${cclap_SOURCE_DIR}/include)
