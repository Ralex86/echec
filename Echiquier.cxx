/**
 * Mise en oeuvre de Echiquier.h
 *
 * @file Echiquier.cxx
 */

#include <iostream>
// A besoin de la declaration de la classe
#include "Echiquier.h"
#include "Piece.h"

using namespace std;

Echiquier::Echiquier()
{
	for (int i = 0; i < 64; i++)
		m_cases[i] = nullptr;

	cout << "echiquier construit" << endl;
}

Piece * Echiquier::getPiece(int x, int y){
	return m_cases[indexCase(x, y)];
}

bool Echiquier::placer(Piece *p)
{
	if (p == nullptr || getPiece(p->x(), p->y()) != nullptr ||
		!caseValide(p->x(), p->y()))
		return false;
	m_cases[indexCase(p->x(), p->y())] = p;
	return true;
}

bool Echiquier::deplacer(Piece *p, int x, int y)
{
	if (p == nullptr || !caseValide(x, y) || m_cases[indexCase(x, y)] != nullptr ||
		m_cases[indexCase(p->x(), p->y())] == nullptr)
		return false;
	m_cases[indexCase(p->x(), p->y())] = nullptr;
	m_cases[indexCase(x, y)] = p;
	p->move(x, y);
	return true;
}

Piece * Echiquier::enleverPiece(int x, int y){
	Piece *p = getPiece(x, y);
	if (p == nullptr)
		return nullptr;
	m_cases[indexCase(x, y)] = nullptr;
	return p;
}

void Echiquier::affiche(){
	cout << endl
		 << "  ABCDEFGH" << endl;
	for (int y = 8; y >= 1; --y)
	{
		cout << y << " ";
		for (int x = 1; x <= 8; ++x)
		{
			char c;
			Piece *p = getPiece(x, y);
			if (p == 0)
				c = ((x + y) % 2) == 0 ? '#' : '.';
			else
				c = p->name();
			cout << c;
		}
		cout << " " << y << endl;
	}
	cout << "  ABCDEFGH" << endl;
}

