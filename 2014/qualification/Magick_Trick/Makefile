INPUT=$(wildcard *.in)
OUTPUT=$(patsubst %.in,%.out,$(INPUT))

FILES=main.go
EXE=main

all: $(EXE)

$(EXE): $(FILES)
	go build -o $@

run: $(OUTPUT)

%.out: %.in $(EXE)
	./$(EXE) < $< > $@
