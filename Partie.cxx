#include <iostream> 
#include "Echiquier.h"
#include "Joueur.h"
#include "Partie.h"
using namespace std;

Partie::Partie(){
	cout << "construction dune partie" << endl;

	p_e = new Echiquier;

	p_blanc = new JoueurBlanc;
	p_noir = new JoueurNoir;

	p_blanc->placer(p_e);
	p_noir->placer(p_e);
	p_e->affiche();
}

bool Partie::saisieValide(string line){
	if (line.size() != 4 || 
			line[0] < 'a' ||
			line[0] > 'h' || 
			line[2] < 'a' || 
			line[2] > 'h' || 
			line[1] < '1' || 
			line[1] > '8' || 
			line[3] < '1' || 
			line[3] > '8'){
		cout << "mouvement incompris" << endl;
		return false;
	}
	return true;
}

int* Partie::convertirSaisieEnCoordonnee(string line){
	static int coord[4];
	coord[0] = line[0] - 'a' + 1;
	coord[1] = line[1] - '0';
	coord[2] = line[2] - 'a' + 1;
	coord[3] = line[3] - '0';
	return coord;
}


void Partie::ajouterCoup(string line){
	this->coups.push_back(line);
}

void Partie::afficherCoups(){
	cout << "Liste des coups joues" << endl;
	for(int i=0; i<this->coups.size(); ++i){
		cout << this->coups[i] << endl ;
	}
}

bool Partie::traitAuxBlancs(){
	if(this->coups.size() == 0){
		return true;
	}
	if(this->coups.size() % 2 == 0){
		return true;
	}
	return false;
}


void Partie::commencerPartie(){


	string line;
	while(true) {
		cout << "> ";
		cin >> line;
		if (line == "exit") break;
		cout << "move=" << line << endl;
		if (this->saisieValide(line) == false) {
			continue;
		}

		int *coord;
		coord = convertirSaisieEnCoordonnee(line);

		int x1 = coord[0];
		int y1 = coord[1];
		int x2 = coord[2];
		int y2 = coord[3];


		Piece *p = this->p_e->getPiece(x1, y1);

		if (this->traitAuxBlancs() && !p->isWhite()){
			cout << "C'est aux blancs de jouer" << endl;
			continue;
		} 
		if (!this->traitAuxBlancs() && p->isWhite() ){
			cout << "C'est aux noirs de jouer" << endl;
			continue;
		}
		if (p != nullptr) // si les coord pièce sélectionnée est bien une pièce
		{
			p->affiche();
			cout << endl;
		}
		else
		{
			cout << "aucune pièce sélectionnée" << endl;
			continue;
		}
		Piece *p2 = p_e->getPiece(x2, y2);
		if (!(p->mouvementValide(*p_e, x2, y2))) // le mouvement n'est pas valide
		{
			cout << "mouvement non valide" << endl;
			p_e->affiche();
			continue;
		}


		if (p2 == nullptr) // si la case destination est libre
		{
			cout << "e.deplacer(" << x2 << ", " << y2 << ")" << endl;
			assert(p_e->deplacer(p, x2, y2) == true); // on déplace
		}
		else // la case destination est occupée
		{
			if (p2->isWhite() == p->isWhite()) // pièce de même couleur
				cout << "Case destination occupée de même couleur" << endl;
			else
			{ // p2 != p1 - pièce de couleur adverse
				cout << "e.enleverPiece(" << x2 << ", " << y2 << ")" << endl;
				Piece *p3 = p_e->enleverPiece(x2, y2); // on retire la pièce de l'échiquier
				assert(p2 == p3);
				// on supprime la pièce du joueur
				if (p2->isWhite())
					assert(p_blanc->supprimerPiece(p2) == true);
				else
					assert(p_noir->supprimerPiece(p2) == true);
				cout << "e.deplacer(" << x2 << ", " << y2 << ")" << endl;
				assert(p_e->deplacer(p, x2, y2) == true); // on déplace la pièce à la destination
			}
		}
		this->ajouterCoup(line);
		this->afficherCoups();
		this->p_e->affiche();
	}
}
