#src/Makefile

CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar

LIB_A = libhardware.a
BUILD_DIR = build
OBJS = $(BUILD_DIR)/*.o

TEST = LED
TEST += BEEP 
TEST += KEY
TEST += USART


.PHONY: all
all: $(TEST)
	$(AR) -cvq $(LIB_A) $(OBJS)

.PHONY: $(TEST)
LED:
	make -C LED

BEEP:
	make -C BEEP

KEY:
	make -C KEY

USART:
	make -C USART

$(OBJS): | $(BUILD_DIR)

.PHONY: clean
clean:
	-rm -fr $(BUILD_DIR)
	-rm -f *.a

