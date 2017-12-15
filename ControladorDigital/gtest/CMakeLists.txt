cmake_minimum_required(VERSION 2.8)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${TARGET_DIR}/include)

get_filename_component(PARENT_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)
set(LIBCtrCEqDiff_SRC_DIR "${PARENT_DIR}/LibCtrCEqDiff/source")
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(	runTests tests.cpp testsADC.cpp testsPWM.cpp)

target_link_libraries(runTests ${GTEST_LIBRARIES} pthread
					${LIBCtrCEqDiff_SRC_DIR}/Utilities/utilities.c
					${LIBCtrCEqDiff_SRC_DIR}/TransferFunctions/TF1stOrdEqDiff.c
					${LIBCtrCEqDiff_SRC_DIR}/TransferFunctions/TF2ndOrdEqDiff.c
					${LIBCtrCEqDiff_SRC_DIR}/Converters/ADCCtrDAC.c
					${LIBCtrCEqDiff_SRC_DIR}/Controllers/CtrPIEqDiff.c
					${LIBCtrCEqDiff_SRC_DIR}/Filters/Butterworth2nd.c
					)
