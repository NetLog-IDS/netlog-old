# nped - network packet editor

Simple tool for editing network packet header fields. Works by first running a live capture, or reading the data from a file, and then searching and replacing the specified fields with the values the user provides

## How-To

### Building the project

```bash
$ git clone https://github.com/adriancostin6/nped.git
$ cd nped
$ mkdir build
$ cmake ..
$ cmake --build .
```

### Generating documentation

```bash
$ cd nped
$ doxygen doc/Doxyfile.in
```

### Usage

```bash
# ./nped -i INTERFACE -f FILTER
```

## Dependencies

- [libtins](https://github.com/mfontanini/libtins)
- [cmake](https://cmake.org/)
