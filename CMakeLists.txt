cmake_minimum_required (VERSION 2.6)
project (OXYGINEMOVIE)

set(OXYGINEMOVIE_INCLUDE_DIRS
	${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/deps
	${CMAKE_CURRENT_SOURCE_DIR}/deps/libtheora/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../oxygine-sound/dependencies/tremor/Tremor
  ${CMAKE_CURRENT_SOURCE_DIR}/../oxygine-sound/dependencies/libogg/include
	)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

message(status ${OXYGINEMOVIE_INCLUDE_DIRS})

set(SRC
	src/MovieSprite.h
	src/MovieSprite.cpp
  src/theora/MovieSpriteTheora.cpp
	)


set (SRC ${SRC}
    deps/libtheora/lib/analyze.c
    deps/libtheora/lib/apiwrapper.c
    deps/libtheora/lib/bitpack.c
    deps/libtheora/lib/cpu.c
    deps/libtheora/lib/decapiwrapper.c
    deps/libtheora/lib/decinfo.c
		deps/libtheora/lib/decode.c
    deps/libtheora/lib/dequant.c
    deps/libtheora/lib/encapiwrapper.c
    deps/libtheora/lib/encfrag.c
    deps/libtheora/lib/encinfo.c
    deps/libtheora/lib/encode.c
    deps/libtheora/lib/enquant.c
    deps/libtheora/lib/fdct.c
    deps/libtheora/lib/fragment.c
    deps/libtheora/lib/huffdec.c
    deps/libtheora/lib/huffenc.c
    deps/libtheora/lib/idct.c
    deps/libtheora/lib/info.c
    deps/libtheora/lib/internal.c
    deps/libtheora/lib/mathops.c
    deps/libtheora/lib/mcenc.c
    deps/libtheora/lib/quant.c
    deps/libtheora/lib/rate.c
    deps/libtheora/lib/state.c
    deps/libtheora/lib/tokenize.c
		)

add_library(oxygine-movie STATIC ${SRC})

set(OXYGINEMOVIE_INCLUDE_DIRS ${OXYGINEMOVIE_INCLUDE_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}/dependencies/openal/include)

set(OXYGINEMOVIE_LIBS
	oxygine-movie
	vlc
  tremor
  -logg
	)

include_directories(${OXYGINEMOVIE_INCLUDE_DIRS})


set(OXYGINEMOVIE_INCLUDE_DIRS
	${CMAKE_CURRENT_SOURCE_DIR}/src)

set(OXYGINEMOVIE_INCLUDE_DIRS ${OXYGINEMOVIE_INCLUDE_DIRS} PARENT_SCOPE)
set(OXYGINEMOVIE_LIBS ${OXYGINEMOVIE_LIBS} PARENT_SCOPE)
