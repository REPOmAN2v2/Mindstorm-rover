_HEADERS = robot.hpp cell.hpp map.hpp display.hpp

#------------------------------------#

ODIR=./obj
BDIR=./bin
SRC=./src

STD = -std=gnu++11

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CXXFLAGS = -Wall -Wextra -g -pg
else
	CXXFLAGS = -O2 -march=native -static
endif

SDL ?= 1
ifeq ($(SDL), 1)
	_HEADERS += sdl.hpp
	CXXFLAGS += -DSDL_SUPPORT
	ifdef COMSPEC
		LIBS = -lmingw32 -lSDL2main -lSDL2 -mwindows -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid
	else
		LIBS = `sdl2-config --cflags --libs`
	endif
else
	LIBS =
endif

CXXFLAGS += $(STD)

_OBJECTS = $(_HEADERS:.hpp=.o)
OBJECTS = $(patsubst %,$(ODIR)/%,$(_OBJECTS))
HEADERS = $(patsubst %,$(SRC)/%,$(_HEADERS))

default: rover

build:
	@test -d $(ODIR) || mkdir $(ODIR)
	@test -d $(BDIR) || mkdir $(BDIR)

clean:
	rm -rf ../obj/
	rm -rf ../bin/
	rm -f ./*~
	rm -f ./*.swp

rebuild: clean default

rover: ${OBJECTS}
	${CXX} $^ $(SRC)/main.cpp $(LIBS) $(CXXFLAGS) -o $(BDIR)/$@

${OBJECTS}: | build

$(ODIR)/%.o: $(SRC)/%.cpp $(SRC)/%.hpp
	${CXX} $< -c $(CXXFLAGS) -o $@

.PHONY: default clean check dist distcheck install rebuild uninstall