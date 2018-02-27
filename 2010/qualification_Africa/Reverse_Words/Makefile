CXX=g++
CPPFLAGS=-std=c++11

INPUT=$(wildcard *.in)
OUTPUT=$(patsubst %.in,%.out,$(INPUT))

FILES=main.cpp
EXE=main

all: $(EXE)

$(EXE): $(FILES)
	$(CXX) $(CPPFLAGS) $^ -o $@

run: $(OUTPUT)

%.out: %.in $(EXE)
	./$(EXE) < $< > $@
