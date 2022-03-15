add_executable(nped 
        capture.h
        capture.cpp
        option-parser.h
        option-parser.cpp
        main.cpp
)

set_target_properties(nped
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

target_link_libraries(nped PRIVATE tins PRIVATE Catch2::Catch2WithMain)
