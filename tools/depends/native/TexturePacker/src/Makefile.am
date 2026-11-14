AUTOMAKE_OPTIONS = subdir-objects

AM_CFLAGS = -DTARGET_POSIX
AM_CFLAGS += @EXTRA_DEFINES@
AM_CXXFLAGS = $(AM_CFLAGS) -std=c++17

AM_CPPFLAGS = \
  -I. \
  -I./decoder \
  -I@UNIVERSAL MEDIA CENTER_SRC_DIR@/ \
  -I@UNIVERSAL MEDIA CENTER_SRC_DIR@//guilib \
  @CPPFLAGS@

AM_LDFLAGS = @LIBS@ @STATIC_FLAG@


bin_PROGRAMS = TexturePacker
TexturePacker_SOURCES =  md5.cpp \
  XBTFWriter.cpp \
  TexturePacker.cpp \
  DecoderManager.cpp \
  decoder/PNGDecoder.cpp \
  decoder/JPGDecoder.cpp \
  decoder/GifHelper.cpp \
  decoder/GIFDecoder.cpp \
  XBTF.cpp

XBTF.cpp:
	@cp @UNIVERSAL MEDIA CENTER_SRC_DIR@//guilib/XBTF.cpp .
