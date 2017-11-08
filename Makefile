all:
	/usr/local/bin/g++-4.9 src/tim.cpp -Wall -std=c++11 -O3 src/sfmt/SFMT.c  -o tim
