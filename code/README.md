cd build/
cmake ..
make
g++ main.cpp -l RICPlib -L code/build/src/ -I code/src/ -l z