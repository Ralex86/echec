#include <iostream>
#include <assert.h>
#include "Joueur.h"

using namespace std;

Joueur::Joueur(){
}

Joueur::~Joueur(){
	for (int i = 0; i < m_pieces.size(); i++)
	{
		if (m_pieces[i] != nullptr)
			delete m_pieces[i];
	}
}

void Joueur::init(bool white){
	m_white = white;
	m_pieces.resize(16);
	if (white)
	{
		m_pieces[0] = new Tour(1, 1, true);
		m_pieces[1] = new Cavalier(2, 1, true);
		m_pieces[2] = new Fou(3, 1, true);
		m_pieces[3] = new Reine(4, 1, true);
		m_pieces[4] = new Roi(5, 1, true);
		m_pieces[5] = new Fou(6, 1, true);
		m_pieces[6] = new Cavalier(7, 1, true);
		m_pieces[7] = new Tour(8, 1, true);
		for (int i = 0; i < 8; i++)
		{
			m_pieces[i + 8] = new Pion(i + 1, 2, true);
		}
	}
	else
	{
		m_pieces[0] = new Tour(1, 8, false);
		m_pieces[1] = new Cavalier(2, 8, false);
		m_pieces[2] = new Fou(3, 8, false);
		m_pieces[3] = new Reine(4, 8, false);
		m_pieces[4] = new Roi(5, 8, false);
		m_pieces[5] = new Fou(6, 8, false);
		m_pieces[6] = new Cavalier(7, 8, false);
		m_pieces[7] = new Tour(8, 8, false);
		for (int i = 0; i < 8; i++)
		{
			m_pieces[i + 8] = new Pion(i + 1, 7, false);
		}
	}

	string couleur = white ? "blanc" : "noir";
	cout << "Joueur " << couleur << " créé" << endl;
}

void Joueur::affiche(){
	cout << "Joueur : " << (m_white ? "blanc" : "noir") << endl;
	for (int i = 0; i < 16; i++){
		m_pieces[i]->affiche();
	}
	cout << "End Joueur" << endl;
}

void Joueur::placer(Echiquier *e){
	for (int i = 0; i < 16; i++)
	{
		assert(e->placer(m_pieces[i]) == true);
		assert(e->getPiece(m_pieces[i]->x(), m_pieces[i]->y()) == m_pieces[i]);
	}
}

bool Joueur::supprimerPiece(Piece *p) {
	for (auto i = m_pieces.begin(); i!=m_pieces.end(); i++) {
		if (*i == p) {
			m_pieces.erase(i);
			return true;
		}
	}
	return false;
}

JoueurBlanc::JoueurBlanc(){
	init(true);
}

JoueurNoir::JoueurNoir(){
	init(false);
}
