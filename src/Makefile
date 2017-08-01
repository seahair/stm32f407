#src Makefile

include ../Makefile.common

OBJS+=startup.o
OBJS+=main.o
OBJS+=stm32f4xx_it.o
OBJS+=system_stm32f4xx.o
//OBJS+=usart.o
OBJS+=led.o



all: src

src: app.a

app.a: $(OBJS) startup.o
	$(AR) cr app.a $(OBJS)

#startup.o: startup.S
#	$(AS) -o startup.o startup.S

.PHONY: src clean tshow

clean:
	rm -f app.a $(OBJS)

tshow:
	@echo "#############################################################"
	@echo "############ optimize settings: $(InfoTextLib),$(InfoTestSrc)"
	@echo "#############################################################"
