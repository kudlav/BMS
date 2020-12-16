# Created by Vladan Kudlac (kudlav) on 12.12.2020

all: main.cpp Decoder.h Encoder.h
	g++ -std=c++14 -static-libstdc++ main.cpp -o bms
