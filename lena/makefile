# Compiler ---------------------------------------------->
CC=gcc

# Flags ------------------------------------------------>
CFLAGS=-Wall -std=c17 -Isrc -m64 -O3 -s -flto -ffunction-sections -fdata-sections -Wl,--gc-sections -MMD -MP

# Platform-specific Flags ------------------------------>
ifeq ($(OS),Windows_NT)
    UNAME_S := Windows
    CFLAGS += -municode
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

ifeq ($(UNAME_S),Linux)
    ifeq ($(UNAME_M),x86_64)
        CFLAGS += "-DLENA_BUILD_PLATFORM=l(\"Linux x86_64\")"
        OUT=lena/linux64/lena
    endif
    ifeq ($(UNAME_M),x86)
        CFLAGS += "-DLENA_BUILD_PLATFORM=l(\"Linux x86\")"
        OUT=lena/linux32/lena
    endif
endif
ifeq ($(UNAME_S),Windows)
    ifeq ($(UNAME_M),x86_64)
        CFLAGS += "-DLENA_BUILD_PLATFORM=l(\"Windows x86_64\")"
        OUT=lena/win64/lena.exe
    endif
    ifeq ($(UNAME_M),x86)
        CFLAGS += "-DLENA_BUILD_PLATFORM=l(\"Windows x86\")"
        OUT=lena/win32/lena.exe
    endif
endif

# Source and Object Files ------------------------------>
SRC_FILES :=  $(shell python utils/find.py src .c)
OBJ_FILES := $(SRC_FILES:.c=.o)
DEP_FILES := $(OBJ_FILES:.o=.d)

# Default Target --------------------------------------->
all: $(OUT)

# Linking ---------------------------------------------->
$(OUT): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ_FILES)

# Compiling -------------------------------------------->
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Include generated dependencies ----------------------->
-include $(DEP_FILES)

# Clean ------------------------------------------------>
clean:
	rm -f $(OUT) $(OBJ_FILES) $(DEP_FILES)
