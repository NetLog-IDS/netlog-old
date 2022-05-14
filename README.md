# spoofy - network packet spoofer

Spoofs and forwards network packets.

## How-To

### Building the project

```bash
$ git clone https://github.com/adriancostin6/spoofy.git
$ make
```

### Generating documentation

```bash
$ cd nped
$ make docs
$ doxygen doc/Doxyfile.in
```

### Usage

```bash
# ./spoofy -i INTERFACE -f FILTER
```

## Dependencies

- [libtins](https://github.com/mfontanini/libtins)
- [cmake](https://cmake.org/)
