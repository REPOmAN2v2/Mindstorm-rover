ODIR=./obj
BDIR=./bin
SRC=./src

CC = g++
CFLAGS := -Wall -Wextra -g -pg

_HEADERS := robot.hpp cell.hpp map.hpp
_OBJECTS := $(_HEADERS:.hpp=.o)
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
	${CC} $^ $(SRC)/main.cpp $(LIBS) $(CFLAGS) -o $(BDIR)/$@

$(ODIR)/%.o: $(SRC)/%.cpp $(SRC)/%.hpp build
	${CC} $< -c $(CFLAGS) -o $@

.PHONY: default clean check dist distcheck install rebuild uninstall