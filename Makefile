ifndef VERBOSE
	MAKEFLAGS += --silent
endif


CMAKE_FLAGS  := -DCMAKE_EXPORT_COMPILE_COMMANDS=1
SPOOFY_FLAGS := -DSPOOFY_BUILD_TESTS=0
RDKAFKA_FLAGS := -DRDKAFKA_BUILD_STATIC=1 -DRDKAFKA_BUILD_TESTS=OFF

ifeq ($(OS), Windows_NT)
	LIBTINS_FLAGS := -DLIBTINS_BUILD_TESTS=0 -DLIBTINS_BUILD_SHARED=0 -DPCAP_ROOT_DIR=../ext/WpdPack
	RM := rmdir /S /Q
else
	LIBTINS_FLAGS := -DLIBTINS_BUILD_TESTS=0 -DLIBTINS_BUILD_SHARED=0
	RM := rm -rf
endif

.PHONY: default debug release test clean configure

default:
	$(MAKE) debug

configure:
	mkdir build
ifeq ($(OS), Windows_NT)
	cmd /C configure.bat
else
	./configure.sh
endif


debug:
	cd build ;\
	cmake .. -DCMAKE_BUILD_TYPE=Debug $(CMAKE_FLAGS) $(LIBTINS_FLAGS) $(SPOOFY_FLAGS) $(RDKAFKA_FLAGS) ;\
	cmake --build . ;\
	echo "Build finished, to run: ./build/bin/spoofy"
	
release:
	$(MK_BUILD_DIR)
	cd build ;\
	cmake .. -DCMAKE_BUILD_TYPE=Release $(CMAKE_FLAGS) $(LIBTINS_FLAGS) $(SPOOFY_FLAGS) $(RDKAFKA_FLAGS);\
	cmake --build . ;\
	echo "Build finished, to run: ./build/bin/spoofy"

test:
	cd build ;\
	ctest --rerun-failed --output-on-failure

clean:
	$(RM) build
	mkdir build
