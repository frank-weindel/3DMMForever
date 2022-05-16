include_directories(../../inc ../../kauai/src ../../bren/inc ../../src)

add_compile_definitions(WIN)
add_library(engine actor.cpp actredit.cpp actrsave.cpp actrsnd.cpp bkgd.cpp body.cpp modl.cpp movie.cpp msnd.cpp mtrl.cpp scene.cpp srec.cpp tagl.cpp tagman.cpp tbox.cpp tdf.cpp tdt.cpp tmpl.cpp)
set_property(TARGET engine PROPERTY
             MSVC_RUNTIME_LIBRARY "MultiThreadedDLL$<$<CONFIG:Debug>:Debug>")

target_link_libraries(engine 3dmovie)
