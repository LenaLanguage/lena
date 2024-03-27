# This is makefile for Lena executor + Llibs

# Compiler --------------------->
CC = gcc

# Flags --------------------->
LENA_CFLAGS = -Wall -MMD -std=c17 -Iinclude

# OS --------------------->
OS := $(shell node scripts/os.js)

# Add flags based on OS --------------------->
LENA_CFLAGS += $(shell node scripts/os-flags.js $(OS))

# And based on CPU arch --------------------->
LENA_CFLAGS += $(shell node scripts/arch-flags.js)

# LENA_OUT --------------------->
LENA_OUT := $(shell node scripts/out.js $(OS))

# Llibs path --------------------->

LLIBS_PATH = external/llibs

# Llibs build ------------------------------------------>

LLIBS_CFLAGS = -Wall -MMD -std=c17 -Iinclude -I$(LLIBS_PATH)/cross/include

# Use Lingua framework ------------------------------------------>
LLIBS_CFLAGS += -D USE_LINGUA

LLIBS_NATIVE_PATH := $(shell node $(LLIBS_PATH)/scripts/native.js $(OS))

# Different files --------------------->
LLIBS_SRC_FILES := $(shell node scripts/find.js $(LLIBS_PATH)/$(LLIBS_NATIVE_PATH) .c)\
	$(shell node scripts/find.js $(LLIBS_PATH)/cross/ .c)
LLIBS_OBJ_FILES := $(LLIBS_SRC_FILES:.c=.o)
LLIBS_DEP_FILES := $(LLIBS_OBJ_FILES:.o=.d)

# Lena build ------------------------------------------>

# Llibs framework --------------------->
LENA_CFLAGS += -I$(LLIBS_PATH)/cross/include

# Different files --------------------->
LENA_SRC_FILES := $(shell node scripts/find.js src .c)
LENA_OBJ_FILES := $(LENA_SRC_FILES:.c=.o)
LENA_DEP_FILES := $(LENA_OBJ_FILES:.o=.d)

# Default Target --------------------->
all: $(LENA_OUT)

# Linking Llibs and Lena together --------------------->
$(LENA_OUT): $(LENA_OBJ_FILES) $(LLIBS_OBJ_FILES)
	$(CC) $(LENA_CFLAGS) -o $@ $^

# Compiling Lena object files --------------------->
$(LENA_SRC_FILES:.c=.o): %.o: %.c
	$(CC) $(LENA_CFLAGS) -c $< -o $@

# Compiling Llibs object files --------------------->
$(LLIBS_SRC_FILES:.c=.o): %.o: %.c
	$(CC) $(LLIBS_CFLAGS) -c $< -o $@

# Include generated dependencies --------------------->
-include $(LENA_DEP_FILES) $(LLIBS_DEP_FILES)

# Clean --------------------->
clean:
	rm -f $(LENA_OUT) $(LENA_OBJ_FILES) $(LENA_DEP_FILES) $(LLIBS_DEP_FILES)