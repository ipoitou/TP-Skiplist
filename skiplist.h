// LIFAP6 - Automne 2017 - R. Chaine

#ifndef _SKIPLIST
#define _SKIPLIST
#define MAX_NIVEAUX 10

#include "element.h" //offrant le type Elem


class Skiplist; // declaration

class Cellule
{
    friend class Skiplist;

    private :
        Elem info;
        Cellule *suivant[MAX_NIVEAUX];
	int nbNiveaux;
};

class Skiplist
{
    public :
    //Constructeurs-------------------------------------------------------------
    Skiplist();
    //Postcondition : la liste *this est  initialisée comme étant vide
    Skiplist(const Skiplist & l);
    //Postcondition :  la liste *this est initialisée en copie profonde de l
    //         (mais elles sont totalement independantes l'une de l'autre)
    
    //Destructeur---------------------------------------------------------------
    ~Skiplist();
     //Postcondition : l'espace occupé par *this  peut-être restitué
    
    //Affectation---------------------------------------------------------------
    Skiplist & operator = (const Skiplist & l);
    //Précondition : aucune
    //       (la liste *this à affecter et l doivent être initialisées)
    //Postcondition : la liste *this correspond à une copie profonde de l
    //           (mais elles sont totalement independantes l'une de l'autre)
    
    bool testVide() const;
    //Précondition : aucune
    //               (*this initialisée)
    //Résultat : true si *this est vide, false sinon
    
    Elem premierElement() const;
    //Précondition : testListeVide(l)==false
    //Résultat : valeur de l'Elem contenu dans la 1ere Cellule
    
    Cellule * premiereCellule() const;
    //Précondition : aucune
    //               (*this initialisée)
    //Résultat : adresse de la premiere cellule de *this si this->testVide()==false
    //           0 sinon
    //           Attention : la liste *this pourrait ensuite etre modifiée à travers
    //           la connaissance de l'adresse de sa première cellule
    
    Cellule * celluleSuivante(const Cellule *pc) const;
    //Précondition : pc adresse valide d'une Cellule de la Liste *this
    //Résultat : adresse de la cellule suivante si elle existe
    //           0 sinon
    //           Attention : la liste *this pourrait ensuite etre modifiée à travers
    //           la connaissance de l'adresse d'une de ses cellules
    
    Elem elementCellule(const Cellule * pc) const;
    //Précondition : pc adresse valide d'une Cellule de la Liste *this
    //Résultat : valeur de l'Elem contenu dans la Cellule
    
    void affichage() const;
    //Précondition : aucune
    //               (*this initialisée)
    //Postcondition : Affichage exhaustif de tous les éléments de *this
    
    void insere(const Elem & e);
    //Précondition : aucune
    //               (*this et e initialisés)
    //Postcondition : L'Elem e est ajouté dans *this qui reste triée
	
    void suppressionEnTete();
    //Précondition : this->testVide()==false
    //Postcondition : la liste *this perd son premier élément

    void vide();
    //Précondition : aucune
    //               (*this initialisée)
    //Postcondition : this->testVide()==true (tous les éléments sont retirés)
    
    void etablissementNiveaux();
	//Précondition : aucune
    //               (*this initialisée)
    //Postcondition : this->niveau2=true et affectation des pointeurs niveau 2 des cellules

	void affichageParNiveau(const int n) const;
    //Précondition : le niveau 2 est mis en place
    //               (niveau2==true)
    //Postcondition : Affichage exhaustif de tous les éléments du niveau 2 de *this

	Cellule * recherche(const Elem & e) const;
    //Précondition : aucune
    //               (*this initialisée)
    //Résultat : Adresse de la première Cellule de *this contenant e, 0 sinon
    //           Attention : la liste *this pourrait ensuite etre modifiée à travers
    //           la connaissance de l'adresse d'une de ses cellules

	void supprime (const Elem & e);

    
    //OPERATIONS QUI POURRAIENT ETRE AJOUTEES AU MODULE LISTE
        
    void modifieInfoCellule(const Elem & e,Cellule *pc);
    //Precondition : *this non vide et pc adresse valide d'une Cellule de *this
    //Postcondition : l'info contenue dans *pc a pour valeur e
 
    private :
        
    void affichageDepuisCellule(const Cellule * pc) const;
    //Donnees membres-----------------------------------------------------------
        Cellule *ad;
        int taille;
};


#endif
