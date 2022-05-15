ifndef VERBOSE
	MAKEFLAGS += --silent
endif

CMAKE_FLAGS  := -DCMAKE_EXPORT_COMPILE_COMMANDS=1
SPOOFY_FLAGS := -DNPED_BUILD_TESTS=1
LIBTINS_FLAGS := -DLIBTINS_BUILD_TESTS=0 -DLIBTINS_BUILD_SHARED=0

ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
	LIBTINS_FLAGS += -DPCAP_ROOT_DIR=ext\WpdPack
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif


BUILD_FOLDER := build

.PHONY: default setup debug release test

setup:
ifeq ($(detected_OS),Windows) 
	cmd /C setup/setup.bat
endif
ifeq ($(detected_OS),Darwin)
	./setup/setup.sh mac
endif
ifeq ($(detected_OS),Linux) 
	./setup/setup.sh linux
endif

default:
	$(MAKE) debug

debug:
	$(MAKE) setup
	mkdir -p $(BUILD_FOLDER)
	cd $(BUILD_FOLDER);\
	cmake .. -DCMAKE_BUILD_TYPE=Debug $(CMAKE_FLAGS) $(LIBTINS_FLAGS) $(SPOOFY_FLAGS);\
	cmake --build .
	echo "Build finished, to run: ./build/bin/spoofy"
	
release:
	$(MAKE) setup
	mkdir -p $(BUILD_FOLDER)
	cd $(BUILD_FOLDER);\
	cmake .. -DCMAKE_BUILD_TYPE=Release $(CMAKE_FLAGS) $(LIBTINS_FLAGS) $(SPOOFY_FLAGS);\
	cmake --build .
	echo "Build finished, to run: ./build/bin/spoofy"

test:
	cd $(BUILD_FOLDER);\
	ctest --rerun-failed --output-on-failure

clean:
	rm -rf build

