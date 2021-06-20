
CXX?=g++
TARGET?=$(shell $(CXX) -dumpmachine)

BIN=tower
CXXFLAGS=-Wall -g -O0 -fPIC -I../externals/include
CPPFLAGS=-MMD

ifeq ($(OS),Windows_NT)
LDFLAGS=-L../externals/$(TARGET)/libs
LDLIBS=-lgpdll -lglfw3dll -lgdi32 -lglu32
else
LD_LIBRARY_PATH=../externals/$(TARGET)/bin
LDFLAGS+=-L../externals/$(TARGET)/bin -Wl,-rpath,$(LD_LIBRARY_PATH)
LDLIBS=-lgp -lglfw
endif

OBJS=src/main.o
DEPS=$(OBJS:.o=.d)

.PHONY: all clean run

all: $(BIN)

-include $(DEPS)

$(BIN): $(OBJS)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

run: $(BIN)
	PATH=$$PATH:externals/$(TARGET)/bin ./$<

clean:
	rm -f $(OBJS) $(DEPS) $(BIN)
