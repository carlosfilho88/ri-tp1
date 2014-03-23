ri-tp1
======
UFMG - ICEx - DCC

Recuperação de Informação - Máquinas de Busca na Web (MSc. 2014.1)

Trabalho Prático I

*Practical Work I: Information Retrieval - Web Search Machines*

## Prerequisites
You must have installed the following libraries:

- [zlib](http://www.zlib.net/)
  * zlib1g zlib1g-dev (via apt repository)
- [icu4c](http://site.icu-project.org/download)
  * libicu-dev libicu48-dbg (via apt repository)
- [gumbo-parser](https://github.com/google/gumbo-parser) (built-in)
  * libtool automake (via apt repository)

## How to compile
```bash
cd tp/
mkdir -p build && cd build/
cmake ..
cd src/ && make
```

## Parameters
You can set these follow parameters to configure environment:

- **_-rd_** to set run directory (default */var/tmp*)
- **_-rf_** to set run filetype (default *.run*)
- **_-rs_** to set run size (default *256MB*)
- **_-id_** to set index directory (collection)
- **_-if_** to set index filename
- **_-od_** to set index output directory
- **_-of_** to set index output filename (default *inverted_index.bin*)
- **_-vd_** to set vocabulary output directory
- **_-vf_** to set vocabulary output filename (default *vocabulary.bin*)

## Running an example
```bash
cd build/src/
./index -rd ../../files/ -if indexToCompressedColection.txt -rs 128
./search -vd /home/user/files
```
