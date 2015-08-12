AM_CXXFLAGS = $(PICKY_CXXFLAGS)

common_source = pipeline.h stage.h field_container.h atom.h  packet.h  packet_latches.h

include_HEADERS = $(common_source)
bin_PROGRAMS = banzai
lib_LTLIBRARIES = libprogtorun.la

banzai_LDADD = -ldl
banzai_SOURCES = $(common_source) banzai.cc dynamic_linking_loader.h

libprogtorun_la_SOURCES =  $(common_source) prog_to_run.cc
