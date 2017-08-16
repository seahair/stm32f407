#src/Makefile
include ../../Makefile.common
CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar

#LIB_A = libhardware.a

BUILD_DIR = ../build

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS = $(patsubst %.o, %.d, $(OBJS))

#.PHONY: all
#all: $(OBJS)
#	$(AR) -cvq $(LIB_A) $^

-include $(DEPS)

$(BUILD_DIR)/%.o: %.c
	$(CC) -fPIC -MMD $(CFLAGS) -c -o $@ $<

$(OBJS): | $(BUILD_DIR)

.PHONY: $(BUILD_DIR)
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

#.PHONY: clean
#clean:
#	-rm -fr $(BUILD_DIR)
#	-rm -f *.a

