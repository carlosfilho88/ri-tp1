ri-tp1
======

Trabalho Prático I: Recuperação de Informação - Máquinas de Busca na Web

*Practical Work I: Information Retrieval - Web Search Machines*

## Prerequisites
You must have installed the following libraries:

- [zlib](http://www.zlib.net/)
  * zlib1g zlib1g-dev (via apt repository)
- [htmlcxx](https://github.com/dhoerl/htmlcxx)

## How to compile code
```bash
cd tp/
mkdir -p build && cd build/
cmake ..
make
```

## Running an example
```bash
cd build/src/
./indexer ../../files/ indexToCompressedColection.txt
```