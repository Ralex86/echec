#if !defined Echiquier_h
#define Echiquier_h

class Piece;

class Echiquier {
private:
  Piece *m_cases[64];
  int indexCase(int x, int y) { return ((x - 1) + 8 * (y - 1)); }
  bool caseValide (int x, int y) { return (x >= 1 && x <= 8 && y >= 1 && y <= 8); }	
public:
  Echiquier();
  Piece* getPiece( int x, int y );
  bool placer( Piece* p );
  bool deplacer( Piece* p, int x, int y );
  Piece* enleverPiece( int x, int y );
  void affiche();
};

#endif // !defined Echiquier_h

