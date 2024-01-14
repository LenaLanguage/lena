
# Preparation
ifeq ($(OS),Windows_NT)
    UNAME_S := Windows
    ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
        UNAME_M := x86_64
    endif
    ifeq ($(PROCESSOR_ARCHITECTURE),x86)
        UNAME_M := x86
    endif
else
    UNAME_S := $(shell uname -s)
    UNAME_M := $(shell uname -m)
endif

# Compiler ---------------------------------------------->

CC=gcc

# Flags ---------------------------------------------->

#
# -s -flto  -ffunction-sections -fdata-sections -Wl,--gc-sections
#

CFLAGS=-Wall -std=c17 -Isrc -m64 -municode -O3

ifeq ($(UNAME_S),Linux)
    ifeq ($(UNAME_M),x86_64)
		OUT=lena/linux64/lena
	endif
	ifeq ($(UNAME_M),x86)
		OUT=lena/linux32/lena
	endif
endif
ifeq ($(UNAME_S),Windows)
    ifeq ($(UNAME_M),x86_64)
		OUT=lena/win64/lena.exe
	endif
	ifeq ($(UNAME_M),x86)
		OUT=lena/win32/lena.exe
	endif
endif


SRC_FILES :=  $(shell python utils/find.py src .c)
HDR_FILES :=  $(shell python utils/find.py src .h)


OBJ_FILES := $(SRC_FILES:.c=.o)

# Default target
all: $(OUT)

# Linking
$(OUT): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ_FILES)

# Compiling
%.o: %.c $(HDR_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OUT) $(OBJ_FILES)