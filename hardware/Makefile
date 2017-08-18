#src/Makefile

CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar

LIB_A = libhardware.a

BUILD_DIR = build
#SUB_LED = LED
#SUB_USART = USART

OBJS = $(BUILD_DIR)/*.o

.PHONY: all
all: LED BEEP
	$(AR) -cvq $(LIB_A) $(OBJS)

.PHONY: LED BEEP
LED:
	make -C LED

BEEP:
	make -C BEEP

#USART:
#	make -C USART

$(OBJS): | $(BUILD_DIR)

.PHONY: clean
clean:
	-rm -fr $(BUILD_DIR)
	-rm -f *.a

