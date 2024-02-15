# Lena programming language -> Standard library (not verified)

## CIO

### Console out

* `cout` - console stream receiver (stdout)
* `cerr` - console stream receiver (stderr)

### Console in

* `cin` - console stream transmitter (stdin)

### To use stream as variable

* `transmitter:(type)` - it is a variable with `type` type

### CIO data types

* `cout`, `cerr`, `cin` - private data type `@stream`

## FIO

* `file(path:str)` - stream/function to open file, return stream

### To use as variable

* `a = file(path)` - `a` is a copy of FIO stream
