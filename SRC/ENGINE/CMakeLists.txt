include_directories(../../inc ../../kauai/src ../../bren/inc ../../src)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} /Gz") # Use __stdcall as default calling convention

add_compile_definitions(WIN)
add_library(engine actor.cpp actredit.cpp actrsave.cpp actrsnd.cpp bkgd.cpp body.cpp modl.cpp movie.cpp msnd.cpp mtrl.cpp scene.cpp srec.cpp tagl.cpp tagman.cpp tbox.cpp tdf.cpp tdt.cpp tmpl.cpp)
target_link_libraries(engine 3dmovie)
