DIR_TARGET = $(shell cd ../../..;pwd)

SRCadc   =  $(DIR_TARGET)/RaspberryPi3B/Perifericos/Ads1115c/source/*.cc
INCadc   =  $(DIR_TARGET)/RaspberryPi3B/Perifericos/Ads1115c/include

SRCcontrol	 =	$(DIR_TARGET)/ControladorDigital/LibCtrCEqDiff/source/Controllers/*.c	$(DIR_TARGET)/ControladorDigital/LibCtrCEqDiff/source/Converters/*.c	$(DIR_TARGET)/ControladorDigital/LibCtrCEqDiff/source/TransferFunctions/*c	$(DIR_TARGET)/ControladorDigital/LibCtrCEqDiff/source/Utilities/*.c
INCIcontrol  =  $(DIR_TARGET)/ControladorDigital/LibCtrCEqDiff/include
INCcontrol   =  $(DIR_TARGET)/ControladorDigital/LibCtrCEqDiff

INCLUDE =	-I $(INCadc)	-I $(INCcontrol)	-I $(INCIcontrol)
SRC	 	=	$(SRCadc)		$(SRCcontrol)

controle:
	g++ controle.cc $(SRC) $(INCLUDE) -lwiringPi -lpthread -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -o Controle
