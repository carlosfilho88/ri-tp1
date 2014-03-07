ri-tp1
======

Trabalho Prático I: Recuperação de Informação - Máquinas de Busca na Web

*Practical Work I: Information Retrieval - Web Search Machines*

## Prerequisites
You must have installed the following libraries:

- [zlib](http://www.zlib.net/)
  * zlib1g zlib1g-dev (via apt repository)
- [icu4c](http://site.icu-project.org/download)
  * libicu-dev libicu48-dbg (via apt repository)
- [gumbo-parser](https://github.com/google/gumbo-parser) (built-in)
- [htmlcxx](https://github.com/dhoerl/htmlcxx) (built-in)

## How to compile code
```bash
cd tp/
mkdir -p build && cd build/
cmake ..
cd src/ && make
```

## Running an example
```bash
cd build/src/
./run ../../files/ indexToCompressedColection.txt
```
