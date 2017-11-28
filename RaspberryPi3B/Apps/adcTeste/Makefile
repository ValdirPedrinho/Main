DIR_TARGET = $(shell cd ../..;pwd)

#=================================================================================================

SRCadc   =  $(DIR_TARGET)/Perifericos/Ads1115c/source/*.cc
INCadc   =  $(DIR_TARGET)/Perifericos/Ads1115c/include

SRCTimerInt   =  $(DIR_TARGET)/Perifericos/TimerInterruptHandler/source/*.cc
INCTimerInt   =  $(DIR_TARGET)/Perifericos/TimerInterruptHandler/include

SRCGlobalH   =  $(DIR_TARGET)/Perifericos/GlobalElementHandler/source/*.cc
INCGlobalH   =  $(DIR_TARGET)/Perifericos/GlobalElementHandler/include

#=================================================================================================

INCLUDE1 	=	-I $(INCadc)
SRC1 		=	$(SRCadc)

INCLUDE2 	=	-I $(INCadc)	-I $(INCTimerInt)
SRC2 		=	$(SRCadc)		$(SRCTimerInt)

#=================================================================================================

Adc:
	g++ adcTeste.cc $(SRC1) $(INCLUDE1) -lwiringPi -lpthread -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -o adcTeste

TimerInterruptAdc:
	g++ adcInterrupcaoTimerTeste.cc $(SRC2) $(INCLUDE2) -lwiringPi -lpthread -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -o adcInterrupTest
