TARGET=x86_64-pc-windows-msvc

CONFIGURATION?=Debug
BIN=x64/$(CONFIGURATION)/tower.exe

.PHONY: install run clean $(BIN)

all: $(BIN)

$(BIN):
	MSBuild.exe /p:configuration=$(CONFIGURATION)

run: $(BIN)
	PATH=$$PATH:externals/$(TARGET)/bin $(BIN)

clean:
	rm -rf x64