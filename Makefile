ifndef VERBOSE
	MAKEFLAGS += --silent
endif

BUILD_FOLDER := build

.PHONY: default setup debug release test

default:
	$(MAKE) debug

debug:
	mkdir -p $(BUILD_FOLDER)
	cd $(BUILD_FOLDER);\
	cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DNPED_BUILD_TESTS=1 -DLIBTINS_BUILD_TESTS=0;\
	cmake --build .
	echo "Build finished, to run: ./build/bin/spoofy"
	
release:
	mkdir -p $(BUILD_FOLDER)
	cd $(BUILD_FOLDER);\
	cmake '..' -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DNPED_BUILD_TESTS=1 -DLIBTINS_BUILD_TESTS=0;\
	cmake --build .
	echo "Build finished, to run: ./build/bin/spoofy"

test:
	cd $(BUILD_FOLDER);\
	ctest --rerun-failed --output-on-failure

clean:
	rm -rf build
