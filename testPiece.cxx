/** 
 * Programme test de Piece
 *
 * @file testPiece.cxx
 */

// Utile pour l'affichage
#include <iostream>
#include <assert.h>
#include "Piece.h"
#include "Joueur.h"
#include "Echiquier.h"
#include "Partie.h"


// Pour utiliser les flux de iostream sans mettre "std::" tout le temps.
using namespace std;

bool memeEndroit(Piece & p1, Piece & p2){
	return p1.x() == p2.x() && p1.y() == p2.y();
}


/**
 * Programme principal
 */
int main( int argc, char** argv )
{
	Partie mapartie;	

	mapartie.commencerPartie();
}
