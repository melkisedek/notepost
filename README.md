_Warning: This is a very old project, it should not compile on any recent compiler. It handles memory UNSAFELY._
# notepost
========

A c program for my term project (PPR - procedural programming) at the polytechnic of namibia.

## Installation
### Compile from source
```bash
git clone https://github.com/melkisedek/notepost.git
cd notepost
make notepost
./notepost --start # to run it.
```
## Developing
You can get the source code following the [above steps](#compile-from-source).
There are several `make` targets to
assist development:

  * With no arguments `make` compiles all the sources to notepost
  * `make notepost` does the above also
  * `make clean` removes all .o files and notepost executable
  * `make clean_all` removes all .o , .data , temporary files and the notepost executable
