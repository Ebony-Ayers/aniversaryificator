PLATFORM ?= linux
ifeq ($(PLATFORM), mac)
	COMPILER = clang++
else
	COMPILER = ccache g++
endif
ENABLE_PREFETCH ?= true
CLFAGS = -std=c++20 -ggdb -march=native
LDFLAGS = 
DEBUG_FLAGS = -DDEBUG -ggdb
WARNINGS = -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2
ifeq ($(PLATFORM), linux)
	WARNINGS += -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast
endif
ifeq ($(ENABLE_PREFETCH), true)
	CLFAGS += -DPREFETCH
endif
SIMD_FLAGS = -mavx -mavx2
PCH = pch.h.gch

.PHONY: debug
debug: v1.out v2.out Makefile
	

.PHONY: release
release: v1.cpp $(PCH) Makefile
	$(COMPILER) $(CLFAGS) -O3 -o v1.out v1.cpp common.cpp debug_tools.cpp tester.cpp $(LDFLAGS)
	$(COMPILER) $(CLFAGS) -O3 -o v2.out v2.cpp common.cpp debug_tools.cpp tester.cpp $(LDFLAGS)

v1.out: v1.o common.o debug_tools.o tester.o $(PCH) Makefile
	$(COMPILER) $(CLFAGS) $(WARNINGS) $(DEBUG_FLAGS) $(SIMD_FLAGS) -o v1.out v1.o common.o debug_tools.o tester.o $(LDFLAGS)
v1.o: v1.cpp debug_tools.hpp common.hpp $(PCH) Makefile
	$(COMPILER) $(CLFAGS) $(WARNINGS) $(DEBUG_FLAGS) $(SIMD_FLAGS) -c v1.cpp $(LDFLAGS)

v2.out: v2.o common.o debug_tools.o tester.o $(PCH) Makefile
	$(COMPILER) $(CLFAGS) $(WARNINGS) $(DEBUG_FLAGS) $(SIMD_FLAGS) -o v2.out v2.o common.o debug_tools.o tester.o $(LDFLAGS)
v2.o: v2.cpp debug_tools.hpp common.hpp $(PCH) Makefile
	$(COMPILER) $(CLFAGS) $(WARNINGS) $(DEBUG_FLAGS) $(SIMD_FLAGS) -c v2.cpp $(LDFLAGS)
	
common.o: common.hpp common.cpp $(PCH) Makefile
	$(COMPILER) $(CLFAGS) $(WARNINGS) $(DEBUG_FLAGS) $(SIMD_FLAGS) -c common.cpp $(LDFLAGS)
	
debug_tools.o: debug_tools.hpp debug_tools.cpp $(PCH) Makefile
	$(COMPILER) $(CLFAGS) $(WARNINGS) $(DEBUG_FLAGS) $(SIMD_FLAGS) -c debug_tools.cpp $(LDFLAGS)

tester.o: tester.hpp tester.cpp $(PCH) Makefile
	$(COMPILER) $(CLFAGS) $(WARNINGS) $(DEBUG_FLAGS) $(SIMD_FLAGS) -c tester.cpp $(LDFLAGS)

pch.h.gch: pch.h
	$(COMPILER) $(CLFAGS) $(WARNINGS) $(DEBUG_FLAGS) pch.h

.PHONY: clear
clear:
	rm *.o
	rm *.out
