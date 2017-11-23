DIR_TARGET = $(shell cd ../..;pwd)

SRCadc   =  $(DIR_TARGET)/Perifericos/Ads1115c/source/*.cc
INCadc   =  $(DIR_TARGET)/Perifericos/Ads1115c/include

INCLUDE =	-I $(INCadc)
SRC	 	=	$(SRCadc)

Adc:
	g++ adcTest.cc $(SRC) $(INCLUDE) -lwiringPi -lpthread -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -o adcTeste
