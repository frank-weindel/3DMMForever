set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} /Gz") # Use __stdcall as default calling convention

include_directories(../../inc ../../kauai/src ../../bren/inc ../../src)

add_compile_definitions(WIN)

# utestscb.cpp left out !!!
add_executable(3dmovie WIN32 utest.rc CreateConsole.cpp ape.cpp browser.cpp esl.cpp mminstal.cpp popup.cpp portf.cpp scnsort.cpp splot.cpp stdiobrw.cpp stdioscb.cpp studio.cpp tatr.cpp tgob.cpp utest.cpp)
add_dependencies(3dmovie kauai engine)

target_link_libraries(3dmovie mpr.lib kauai engine bren brfmmxr brfwmxr brzbmxr)
