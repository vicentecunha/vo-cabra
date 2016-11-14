CC=avr-c++
CFLAGS=-I$(INCDIR) -mmcu=atmega328p -std=c++11 -Os
LFLAGS=-Wl,-u,vfprintf -lprintf_flt -lm

INCDIR=./include
_DEPS= adc.h display.h eeprom.h io.h pneumo.h timer0.h timer1.h sensors.h uart.h
DEPS=$(patsubst %,$(INCDIR)/%,$(_DEPS))

ODIR=./obj
_OBJ= adc.o display.o eeprom.o io.o pneumo.o timer0.o timer1.o sensors.o uart.o main.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

ELF=main.elf

CONVERTER=avr-objcopy
CONVFLAGS=-O ihex -R .eeprom
HEX=main.hex

INSTALLER=avrdude
PORT=/dev/ttyACM0
IFLAGS=-c arduino -p ATMEGA328P -b 115200 -P $(PORT) -U flash:w:$(HEX)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(ELF) $^ $(CFLAGS) $(LFLAGS)

install:
	$(CONVERTER) $(CONVFLAGS) $(ELF) $(HEX)
	$(INSTALLER) $(IFLAGS)

clean:
	rm -f $(ODIR)/*.o *~ core $(ELF) $(HEX)
