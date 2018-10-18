#if !defined Piece_h
#define Piece_h
#include "Echiquier.h"

class Piece
{
private:
  int m_x;
  int m_y;
  bool m_white;

public:
  Piece();
  Piece(int x, int y, bool white);
  ~Piece();
  void init(int x, int y, bool white);
  void move(int x, int y);
  int x() const;
  int y() const;
  bool isWhite();
  void affiche();
  Piece &plusforte(Piece &p);
  virtual bool mouvementValide(Echiquier &e, int x, int y);
  virtual char name();
};

class Pion : public Piece
{
public:
  Pion(int x, int y, bool white);
  bool mouvementValide(Echiquier &e, int x, int y);
  char name();
};

class Roi : public Piece
{
public:
  Roi(int x, int y, bool white);
  bool mouvementValide(Echiquier &e, int x, int y);
  char name();
};

class Reine : public Piece
{
public:
  Reine(int x, int y, bool white);
  bool mouvementValide(Echiquier &e, int x, int y);
  char name();
};

class Fou : public Piece
{
public:
  Fou(int x, int y, bool white);
  bool mouvementValide(Echiquier &e, int x, int y);
  char name();
};

class Cavalier : public Piece
{
public:
  Cavalier(int x, int y, bool white);
  bool mouvementValide(Echiquier &e, int x, int y);
  char name();
};

class Tour : public Piece
{
public:
  Tour(int x, int y, bool white);
  bool mouvementValide(Echiquier &e, int x, int y);
  char name();
};
#endif // !defined Piece_h

