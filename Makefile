ifndef VERBOSE
	MAKEFLAGS += --silent
endif

CMAKE_FLAGS  := -DCMAKE_EXPORT_COMPILE_COMMANDS=1
SPOOFY_FLAGS := -DSPOOFY_BUILD_TESTS=1
LIBTINS_FLAGS := -DLIBTINS_BUILD_TESTS=0 -DLIBTINS_BUILD_SHARED=0 -DPCAP_ROOT_DIR=${CMAKE_SOURCE_DIR}\ext\WpdPack

BUILD_FOLDER := build

.PHONY: default debug release test

default:
	$(MAKE) debug

debug:
	mkdir build;\
	cd build;\
	cmake .. -DCMAKE_BUILD_TYPE=Debug $(CMAKE_FLAGS) $(LIBTINS_FLAGS) $(SPOOFY_FLAGS);\
	cmake --build .;\
	echo "Build finished, to run: ./build/bin/spoofy"
	
release:
	mkdir build;\
	cd build;\
	cmake .. -DCMAKE_BUILD_TYPE=Release $(CMAKE_FLAGS) $(LIBTINS_FLAGS) $(SPOOFY_FLAGS);\
	cmake --build .;\
	echo "Build finished, to run: ./build/bin/spoofy";\

test:
	cd build;\
	ctest --rerun-failed --output-on-failure

clean:
	rm -rf build
