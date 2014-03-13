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
  * libtool automake (via apt repository)

## How to compile this code
```bash
cd tp/
mkdir -p build && cd build/
cmake ..
cd src/ && make

## Parameters
You can set these follow parameters to configure environment:

- **-r** to run size (default 256MB)
- **-d** to index directory (collection)
- **-f** to index filename

```
## Running an example
```bash
cd build/src/
./run ../../files/ indexToCompressedColection.txt
```
