SRC_CXX=Piece.cxx Joueur.cxx Echiquier.cxx Partie.cxx

OBJ=${SRC_CXX:.cxx=.o}

CFLAGS=-MMD -g -std=c++11

%.o: %.cxx
	g++ -c $(CFLAGS) $<

all: testPiece

testPiece: $(OBJ) testPiece.o
	g++ $(OBJ) testPiece.o -o testPiece

clean:
	@rm -f $(OBJ) testPiece.o testPiece *~

-include *.d
