CC=clang
CPPCHECK=C:\Program Files\Cppcheck\cppcheck.exe
CFLAGS=-Wall -Iinclude -Wno-pragma-pack
LDFLAGS=-L. -lSDL2 -llibui
BINARY=ui
BINARY_TESTS=ui_tests

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

ui: main.o
	$(CC) -o $(BINARY) $(LDFLAGS) $^

main.o: main.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

tests.o: tests.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

test: tests.o
	$(CC) -o $(BINARY_TESTS) $(LDFLAGS) $^
	./$(BINARY_TESTS)
