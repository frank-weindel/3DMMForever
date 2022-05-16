add_compile_definitions(WIN)
#set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} /Gz") # Use __stdcall as default calling convention

add_library(stub stub.c)
