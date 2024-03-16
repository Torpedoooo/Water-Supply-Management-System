cmake_minimum_required(VERSION 3.26)
project(GraphProject)

set(CMAKE_CXX_STANDARD 14)

file(COPY src/dataset/large/Cities.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY src/dataset/large/Pipes.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY src/dataset/large/Reservoir.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY src/dataset/large/Stations.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY src/dataset/small/Cities_Madeira.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY src/dataset/small/Pipes_Madeira.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY src/dataset/small/Reservoirs_Madeira.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY src/dataset/small/Stations_Madeira.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


add_executable(GraphProject
        src/main.cpp
        src/Data.cpp
        src/Data.h
        src/data_structures/Graph.h
        src/data_structures/MutablePriorityQueue.h
        src/data_structures/City.h
        src/data_structures/Reservoir.h
        src/data_structures/Station.h
)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)