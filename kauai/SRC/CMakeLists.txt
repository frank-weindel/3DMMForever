include_directories(../../inc ../../kauai/src ../../bren/inc ../../src)

add_compile_definitions(WIN)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} /Gz") # Use __stdcall as default calling convention

add_library(kauai appb.cpp appbwin.cpp base.cpp chcm.cpp chse.cpp chunk.cpp clip.cpp clok.cpp cmd.cpp codec.cpp codkauai.cpp crf.cpp ctl.cpp cursor.cpp dlg.cpp dlgwin.cpp docb.cpp file.cpp filewin.cpp fniwin.cpp gfx.cpp gfxwin.cpp gob.cpp gobwin.cpp groups.cpp groups2.cpp kidhelp.cpp kidspace.cpp kidworld.cpp lex.cpp mbmp.cpp mbmpgui.cpp memwin.cpp menuwin.cpp midi.cpp mididev2.cpp mssio.cpp pic.cpp picwin.cpp region.cpp rtxt.cpp rtxt2.cpp scrcom.cpp scrcomg.cpp screxe.cpp screxeg.cpp sndam.cpp sndm.cpp spell.cpp stream.cpp test.cpp text.cpp textdoc.cpp util.cpp utilcopy.cpp utilerro.cpp utilglob.cpp utilint.cpp utilmem.cpp utilrnd.cpp utilstr.cpp video.cpp)

add_library(audioman STATIC IMPORTED)
set_property(TARGET audioman PROPERTY
             IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/kauai/elib/wins/audios.lib")

target_link_libraries(kauai stub audioman legacy_stdio_definitions.lib kernel32.lib comdlg32.lib user32.lib gdi32.lib winmm.lib vfw32.lib)
