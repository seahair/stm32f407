#src/Makefile

CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar

LIB_A = libhardware.a

BUILD_DIR = build
SUB_LIB = LED

OBJS = $(BUILD_DIR)/led.o
#SRCS = $(wildcard $(BUILD_DIR)/*.o)
#OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))
#DEPS = $(patsubst %.o, %.d, $(OBJS))

.PHONY: all
#all: $(OBJS)
all: $(BUILD_DIR)/*.o $(SUB_LIB)
	$(AR) -cvq $(LIB_A) $<

-include $(DEPS)

.PHONY: $(SUB_LIB)
$(SUB_LIB):
	make -C LED


#$(BUILD_DIR)/%.o: %.c
	#$(CC) -fPIC -MMD -c -o $@ $<

$(OBJS): | $(BUILD_DIR)

.PHONY: $(BUILD_DIR)
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: clean

clean:
	-rm -fr $(BUILD_DIR)
	-rm -f *.a

