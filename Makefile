ifndef VERBOSE
	MAKEFLAGS += --silent
endif

ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
	make_dir := mkdir
else
	make_dir := mkdir -p
endif

CMAKE_FLAGS  := -DCMAKE_EXPORT_COMPILE_COMMANDS=1
SPOOFY_FLAGS := -DSPOOFY_BUILD_TESTS=1
LIBTINS_FLAGS := -DLIBTINS_BUILD_TESTS=0 -DLIBTINS_BUILD_SHARED=0 -DPCAP_ROOT_DIR=${CMAKE_SOURCE_DIR}\ext\WpdPack

BUILD_FOLDER := build

.PHONY: default debug release test

default:
	$(MAKE) debug

debug:
	$(make_dir) -p $(BUILD_FOLDER)
	cd $(BUILD_FOLDER)
	cmake .. -DCMAKE_BUILD_TYPE=Debug $(CMAKE_FLAGS) $(LIBTINS_FLAGS) $(SPOOFY_FLAGS)
	cmake --build .
	echo "Build finished, to run: ./build/bin/spoofy"
	
release:
	$(make_dir) -p $(BUILD_FOLDER)
	cd $(BUILD_FOLDER)
	cmake .. -DCMAKE_BUILD_TYPE=Release $(CMAKE_FLAGS) $(LIBTINS_FLAGS) $(SPOOFY_FLAGS)
	cmake --build .
	echo "Build finished, to run: ./build/bin/spoofy"

test:
	cd $(BUILD_FOLDER)
	ctest --rerun-failed --output-on-failure

clean:
	rm -rf build
