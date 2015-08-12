AM_CXXFLAGS = $(PICKY_CXXFLAGS)

common_source = pipeline.h stage.h field_container.h atom.h  packet.h  packet_latches.h dynamic_linking_loader.h

bin_PROGRAMS = banzai
lib_LTLIBRARIES = libprogtorun.la

banzai_LDADD = -ldl
banzai_SOURCES = $(common_source) banzai.cc

libprogtorun_la_SOURCES =  $(common_source) prog_to_run.cc
