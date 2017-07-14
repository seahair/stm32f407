#src Makefile

include ../Makefile.common

OBJS+=startup.o
OBJS+=main.o
OBJS+=stm32f4xx_it.o
OBJS+=system_stm32f4xx.o

#OBJS+=delay.o
#OBJS+=sys.o
#OBJS+=usart.o
#OBJS+=stm32f4xx_it.o
#OBJS+=system_stm32f4xx.o


all: src

src: app.a

app.a: $(OBJS)
	$(AR) cr app.a $(OBJS)

.PHONY: src clean tshow

clean:
	rm -f app.a $(OBJS)

tshow:
	@echo "#############################################################"
	@echo "############ optimize settings: $(InfoTextLib),$(InfoTestSrc)"
	@echo "#############################################################"
