#if !defined Partie_h
#define Partie_h

using namespace std;

class Partie {
	private:
		Echiquier *p_e;
		JoueurBlanc *p_blanc;
		JoueurNoir *p_noir;
		std::vector<std::string> coups;

	public:

		Partie();
		Partie(Echiquier &e);
		bool saisieValide(string line);
		int* convertirSaisieEnCoordonnee(string line);
		bool traitAuxBlancs();

		void ajouterCoup(string line);
		void afficherCoups();
		void commencerPartie();
};

#endif // !defined Partie_h
