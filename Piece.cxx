#include <iostream>
#include <stdlib.h>
#include "Piece.h"

using namespace std;

Piece::Piece() {}

Piece::Piece(int x, int y, bool white){
  init(x, y, white);
}

Piece::~Piece() {}

void Piece::init(int x, int y, bool white){
  m_x = x;
  m_y = y;
  m_white = white;
}

void Piece::move(int x, int y){
  m_x = x;
  m_y = y;
}

int Piece::x() const{
  return m_x;
}

int Piece::y() const{
  return m_y;
}

bool Piece::isWhite(){
  return m_white;
}

void Piece::affiche(){
  cout << "Piece: x=" << x() << " y=" << y() << " " << (isWhite() ? "white" : "black") << endl;
}

Piece &Piece::plusforte(Piece &p){
  if (p.x() > x() && p.y() > y())
    return p;
  else
    return *this;
}

char Piece::name(){
  return (isWhite() ? 'B' : 'N');
}

bool Piece::mouvementValide(Echiquier &e, int px, int py){
  Piece *p = e.getPiece(px, py);
  if (px == x() && py == y()) 
    return false;
  if (p == nullptr) 
    return true;
  else                                  
    return (p->isWhite() != isWhite()); 
}

Pion::Pion(int x, int y, bool white) : Piece(x, y, white) {}

bool Pion::mouvementValide(Echiquier &e, int px, int py)
{
  if (!Piece::mouvementValide(e, px, py))
    return false;
  if (isWhite()) // piece blanche
  {
    if (py - y() == 1) // avance vers le haut de 1 case
    {
      if (px == x()) // avance droit
        return e.getPiece(px, py) == nullptr; // il n'y a pas de pièce devant
      else if (abs(px - x()) == 1) // avance en diagonale
      {
        return e.getPiece(px, py) != nullptr; // il y a une pièce à capturer
      }
    }
    else if (y() == 2 && px == x() && py == 4)
      return true;
  }
  else // piece noire
  {
    if (y() - py == 1) // avance vers le bas de 1 case
    {
      if (px == x()) // avance droit
        return e.getPiece(px, py) == nullptr; // il n'y a pas de pièce devant
      else if (abs(px - x()) == 1) // avance en diagonale
      {
        return e.getPiece(px, py) != nullptr; // il y a une pièce à capturer
      }
    }
    else if (y() == 7 && px == x() && py == 5)
      return true;
  }
	return false;
}

char Pion::name()
{
  return (Piece::isWhite() ? 'P' : 'p');
}

Roi::Roi(int x, int y, bool white) : Piece(x, y, white) {}

bool Roi::mouvementValide(Echiquier &e, int px, int py)
{
  if (!Piece::mouvementValide(e, px, py))
    return false;
  // mouvements du roi (1 autour de lui)
  if (abs(px - x()) == 1 || abs(py - y()) == 1)
    return true;
  return false;
}

char Roi::name()
{
  return (Piece::isWhite() ? 'R' : 'r');
}

Reine::Reine(int x, int y, bool white) : Piece(x, y, white) {}

bool Reine::mouvementValide(Echiquier &e, int px, int py)
{
  if (!Piece::mouvementValide(e, px, py))
    return false;
  Tour *p1 = new Tour(x(), y(), isWhite());
  Fou *p2 = new Fou(x(), y(), isWhite());
  // mouvement du fou ou de la tour
  return (p1->mouvementValide(e, px, py) || p2->mouvementValide(e, px, py));
}

char Reine::name()
{
  return (Piece::isWhite() ? 'Q' : 'q');
}

Fou::Fou(int x, int y, bool white) : Piece(x, y, white) {}

bool Fou::mouvementValide(Echiquier &e, int px, int py)
{
  if (!Piece::mouvementValide(e, px, py))
    return false;
  if (abs(px - x()) != abs(py - y()))
    return false;
  if (px - x() > 0) // vers la droite
  {
    if (py - y() > 0) // sens diagonale droite haut
    {
      for (int i = 1; i < px - x(); i++)
      {
        Piece *tmp = e.getPiece(x() + i, y() + i);
        if (tmp != nullptr) // une pièce bloque sur son chemin
          return false;
      }
    }
    else // sens diagonale droite bas
    {
      for (int i = 1; i < px - x(); i++)
      {
        Piece *tmp = e.getPiece(x() + i, y() - i);
        if (tmp != nullptr) // une pièce bloque sur son chemin
          return false;
      }
    }
  }
  else
  {
    if (py - y() > 0) // sens diagonale gauche haut
    {
      for (int i = 1; i < abs(px - x()); i++)
      {
        Piece *tmp = e.getPiece(x() - i, y() + i);
        if (tmp != nullptr) // une pièce bloque sur son chemin
          return false;
      }
    }
    else // sens diagonale gauche bas
    {
      for (int i = 1; i < abs(px - x()); i++)
      {
        Piece *tmp = e.getPiece(x() - i, y() - i);
        if (tmp != nullptr) // une pièce bloque sur son chemin
          return false;
      }
    }
  }
  return true;
}

char Fou::name()
{
  return (Piece::isWhite() ? 'F' : 'f');
}

Cavalier::Cavalier(int x, int y, bool white) : Piece(x, y, white) {}

bool Cavalier::mouvementValide(Echiquier &e, int px, int py)
{
  if (!Piece::mouvementValide(e, px, py))
    return false;
  // mouvements du cavalier autorisés
  if ((px == x() + 1 || px == x() - 1) && (py == y() + 2 || py == y() - 2))
    return true;
  if ((px == x() + 2 || px == x() - 2) && (py == y() + 1 || py == y() - 1))
    return true;
  return false;
}

char Cavalier::name()
{
  return (Piece::isWhite() ? 'C' : 'c');
}

Tour::Tour(int x, int y, bool white) : Piece(x, y, white) {}

bool Tour::mouvementValide(Echiquier &e, int px, int py)
{
  // le mouvement n'est pas valide ou n'est pas sur la même ligne ou la même colonne
  if (!(Piece::mouvementValide(e, px, py) &&
        (px == x() || py == y())))
    return false;
  if (px == x()) // même lettre de ligne
  {
    int sens = py - y(); // sens du déplacement
    if (sens > 0)        // vers le haut
    {
      for (int i = y() + 1; i < py; i++)
        if (e.getPiece(px, i) != nullptr) // une pièce bloque sur son chemin
          return false;
    }
    else // vers le bas
    {
      for (int i = y() - 1; i > py; i--)
        if (e.getPiece(px, i) != nullptr) // une pièce bloque sur son chemin
          return false;
    }
    return true; // aucune pièce bloque sur son chemin
  }
  else // même numéro de colonne
  {
    int sens = px - x(); // sens du déplacement
    if (sens > 0)        // vers la droite
    {
      for (int i = x() + 1; i < px; i++)
        if (e.getPiece(i, py) != nullptr) // une pièce bloque sur son chemin
          return false;
    }
    else // vers la gauche
    {
      for (int i = x() - 1; i > px; i--)
        if (e.getPiece(i, py) != nullptr) // une pièce bloque sur son chemin
          return false;
    }
    return true; // aucune pièce bloque sur son chemin
  }
}

char Tour::name()
{
  return (Piece::isWhite() ? 'T' : 't');
}
