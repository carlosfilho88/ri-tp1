ri-tp1
======

Trabalho Prático I: Recuperação de Informação - Máquinas de Busca na Web

## Prerequisites
You must have installed the following libraries (apt options are avaliable):

- [zlib](http://www.zlib.net/)
  * zlib1g zlib1g-dev
- [htmlcxx](http://htmlcxx.sourceforge.net/)
  * libhtmlcxx3 libhtmlcxx-dev

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