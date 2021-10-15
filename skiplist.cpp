// LIFAP6 - Automne 2017 - R. Chaine

#include <cstdio>
#include <iostream>
#include <stdlib.h> //rand
#include "element.h" //offrant le type Elem
#include "skiplist.h"
//#include <cassert> //Si on veut faire des tests de preconditions en mode debug
using namespace std;


Skiplist::Skiplist()
{
    Cellule *sentinelle = new Cellule;
    sentinelle->nbNiveaux = 1;
    for (int i=0; i<MAX_NIVEAUX; i++)
    sentinelle->suivant[i] = nullptr;
    sentinelle->nbNiveaux = 1;
    ad = sentinelle; //this->ad=0;
    taille=0;
}

bool Skiplist::testVide() const
{
    return taille==0; //this->ad==0;
}

Elem Skiplist::premierElement() const
{
    return (ad->suivant[0])->info; //this->ad->info;
}

Cellule * Skiplist::premiereCellule() const
{
    return ad->suivant[0]; //this->ad;
}

Cellule * Skiplist::celluleSuivante(const Cellule *c) const
{
  return c->suivant[0];
}

Elem Skiplist::elementCellule(const Cellule * c) const
{
  return c->info;
}

#ifndef _RECURSIF 
void Skiplist::affichage() const  //ok
{
  std::printf("Liste ");
  Cellule *temp=ad->suivant[0]; // Cellule *temp=this->ad;
  while(temp!=0)
    {
      affichageElement(temp->info);
      temp=temp->suivant[0];
    }
  std::putchar('\n');
}
#endif

void Skiplist::insere(const Elem & e)
{
  //Creation d'une nouvelle Cellule
  Cellule *nouvelle=new Cellule;
  nouvelle->info=e;
  cout << endl << "nouvelle " << nouvelle << endl;

  //les pointeurs de tous les niveaux sont initialisés à nullptr
  for (int i=0;i<ad->nbNiveaux;i++) //verifier que ad->nbNiveaux est bien le nombre actuel de niveaux dans la skiplist
    nouvelle->suivant[i]=nullptr;
  
  Cellule *avant;
  Cellule *apres;
  int N = ad->nbNiveaux; //correspond au niveau max
  Cellule *tabPaliers[N];
  avant = ad;

  while (N>=1) // recherche où placer la cellule, en cherchant niveau par niveau à partir du plus haut, et enregistre l'endroit où on descend
  {
    apres = avant->suivant[N-1];
    cout << "N " << N << endl;
    cout << "avant " << avant << endl;
    cout << "apres" << apres << endl;
    
    while ((apres != nullptr) && (e>apres->info)) // on avance dans la liste tant qu'on ne dépasse pas la valeur
    {
      cout << " apres->info " << apres->info << endl;
      avant = avant->suivant[N-1];
      apres = apres->suivant[N-1]; // on peut avoir apres qui est nul
      cout << "avant dans boucle" << avant << endl;
      cout << "apres dans boucle" << apres << endl;
    }
    cout << N-1 << endl;
    cout << "avant " << avant << endl;
    tabPaliers[N-1] = avant;
    cout << tabPaliers[N-1] << endl;
    N--;
  }// N vaut 0 et apres pointe sur la premiere cellule du niveau 0 contenant une info plus grande ou bien 0
  nouvelle->suivant[0] = apres; // apres p
  avant->suivant[0] = nouvelle;
 
  if (ad->nbNiveaux>1)  // cas où on insère dans la skiplist déjà créée avec tous les niveaux
  {
    cout << "nouveau" << nouvelle->info;
    cout << " suivant nouveau " << nouvelle->suivant[0]->info;
    cout << " avant nouveau " << avant ->info << endl;
    for (int i = 0; i < ad->nbNiveaux; i++)
    cout << "palier " << ad->nbNiveaux-i-1<<" "<<tabPaliers[ad->nbNiveaux-i-1]->info;
    cout << endl;}

  /*if (ad->nbNiveaux>1) // à faire seulement si la skiplist est déjà installée avec plusieurs niveaux
                        // on détermine à quel niveau va la nouvelle cellule
  {*/
    int i=1;
    bool stop = false;
    while (i<=ad->nbNiveaux-1 && !stop) // est-ce qu'elle atteint le niveau i ? en utilisant tous les niveaux déjà créés
    {
      srand(time(NULL));
      int alea = rand() % 2;
      cout << alea;
      if (alea == 0) //la nouvelle atteint le niveau supérieur
      {
        nouvelle->suivant[i] = tabPaliers[i]->suivant[i];
        tabPaliers[i]->suivant[i] = nouvelle;
        nouvelle->nbNiveaux++;
        i++;
      }
      else stop = true;
    }
    if (i == ad->nbNiveaux) // est-ce qu'elle atteint le niveau i? au-delà des niveaux qui étaient utilisés
    {

      while (i<=MAX_NIVEAUX - 1 && !stop)
      {
        int alea = rand() % 2;
        cout << alea;
        if (alea == 0) //la nouvelle atteint le niveau supérieur
        {
          nouvelle->suivant[i] = nullptr;
          ad->suivant[i] = nouvelle;
          nouvelle->nbNiveaux++;
          ad->nbNiveaux++;
          i++;
        }
        else stop = true;
      }
    }
  /*}*/
  for(int j=0; j<MAX_NIVEAUX; j++)
    {
      cout << "niveau " << j << endl;
      affichageParNiveau(j);
      cout<<endl;
    }

  taille++; // this->taille++;
}

void Skiplist::suppressionEnTete()
{
  //assert(testVide()); //Si on veut faire des tests en mode debug
  Cellule *temp = ad->suivant[0]; // temp=this->ad; On memorise l'adresse de la premiere Cellule
  ad->suivant[0]=(ad->suivant[0])->suivant[0]; //this->ad=this->ad->suivant[0]; La deuxieme Cellule de *this devient la premiere
  delete temp;//L'espace occupe par la Cellule abandonnee est restitue
  taille--; // this->taille--;
}

#ifndef _RECURSIF 
void Skiplist::vide()
{
  while(!testVide()) //while(!this->testVide())
    {
      suppressionEnTete(); //this->suppressionEnTete();
    }
}
#endif
/*
Skiplist::Skiplist(const Skiplist & l)
{ 
    Cellule *sentinelle = new Cellule;
    sentinelle->suivant[0] = 0;
    this->ad = sentinelle;
    this->taille=0;
    if(!l.testVide())
    {
      Cellule *temp1=(l.ad)->suivant[0]; 
      Cellule *temp2=this->ad;
      while(temp1!=0)
      { //Il reste des elements a ajouter
          this->insere(temp1->info);
          temp2=temp2->suivant[0]; //Ainsi temp2 pointe sur la derniere cellule de *this
          temp1=temp1->suivant[0]; //tmp1 pointe sur la premiere Cellule de l
                                // dont l'info n'a pas ete ajoutee a *this
      }

    }
}*/

Skiplist::~Skiplist()
{
  this->vide();
}

Skiplist & Skiplist::operator=(const Skiplist & l)
{
  if (this!=&l)
    {
      this->vide();
      if(!l.testVide())
	    {
	      Cellule *temp1=(l.ad)->suivant[0]; 
        Cellule *temp2=this->ad;
        while(temp1!=0)
        { //Il reste des elements a ajouter
          this->insere(temp1->info);
          temp2=temp2->suivant[0]; //Ainsi temp2 pointe sur la derniere cellule de *this
          temp1=temp1->suivant[0]; //tmp1 pointe sur la premiere Cellule de l
                                // dont l'infowhile ((avant->suivant[N-1] != 0) && (e>apres->info))
        }
	    }
    }
  return *this;
}

void Skiplist::etablissementNiveaux()
{  
  if (!testVide())
  {
    for (int n = 0; n < MAX_NIVEAUX-1; n++)
    {// construction du niveau n+1 à partir du niveau n
      bool niveauplus1existe = false;
      Cellule *temp1=ad; //temp1 va visiter tout le niveau n
      Cellule *temp2=ad;
      while (temp1->suivant[n]!=nullptr)
      {
        int alea = rand() % 2;
        if (alea == 0) //pile
        {
          temp2->suivant[n+1] = temp1->suivant[n];
          temp2->suivant[n+1]->nbNiveaux++;
          temp2 = temp2->suivant[n+1];
          if (!niveauplus1existe) niveauplus1existe = true;
        }
        temp1 = temp1->suivant[n];
      }
      if (niveauplus1existe) ad->nbNiveaux++;
    }
  }
}

void Skiplist::affichageParNiveau(int niv) const
{
  std::printf("Liste (it) ");
  Cellule *temp=ad->suivant[niv]; // Cellule *temp=this->ad;
  while(temp!=nullptr)
    {
      affichageElement(temp->info);
      temp=temp->suivant[niv];
    }
  std::putchar('\n');
}

Cellule * Skiplist::recherche(const Elem & e) const
{
  Cellule *avant;
  Cellule *apres;
  int N = ad->nbNiveaux; //correspond au niveau max
  avant = ad;

  while (N>=1) // recherche l'intervalle où se trouve e, en cherchant niveau par niveau à partir du plus haut, et enregistre l'endroit où on descend
  {
    apres = avant->suivant[N-1];
    while ((avant->suivant[N-1] != nullptr) && (e>apres->info)) // on avance dans la liste tant qu'on ne dépasse pas la valeur
    {
      avant = avant->suivant[N-1];
      apres = apres->suivant[N-1];
    }
    if (e == apres->info) return apres;
    N--;
  }

  if (avant->suivant[0] != nullptr) // la boucle while s'est arrêtée parce que e<=apres->info
  {
    if (e == apres->info) return apres;
    else return nullptr;
  }
  return nullptr; //a verifier
}

void Skiplist::supprime (const Elem & e)
{
  Cellule *avant;
  Cellule *apres;
  int N = ad->nbNiveaux; //correspond au niveau max
  avant = ad;

  while (N>=1) // recherche l'intervalle où se trouve e, en cherchant niveau par niveau à partir du plus haut, et enregistre l'endroit où on descend
  {
    apres = avant->suivant[N-1];
    while ((avant->suivant[N-1] != nullptr) && (e>apres->info)) // on avance dans la liste tant qu'on ne dépasse pas la valeur
    {
      avant = avant->suivant[N-1];
      apres = apres->suivant[N-1];
    }
    if (e == apres->info) 
    {
      Cellule *temp = apres;
      while (N>=1)
      {
        avant->suivant[N-1] = apres->suivant[N-1];  // on supprime les liens avec la cellule qui contient e au niveau N-1 et dessous
        if (ad->suivant[N-1] == nullptr) ad->nbNiveaux--;
        N--;
      }
      delete temp;

    }
    N--;
  }

  
  
}

#ifdef _RECURSIF
// Version recursive de certaines fonctions/procedures
// pour lesquelles on a donne une version iterative plus haut

//Procedure interne au module
void Liste::affichageDepuisCellule(const Cellule * c) const
{
    if(c!=0) //il reste des cellules a afficher
    {
        affichageElement(c->info);
        affichageDepuisCellule(c->suivant[0]);//this->afficheDepuisCellule(c->suivant[0]);
    }
}

void Liste::affichage() const
{
    std::printf("Liste (rec) :");
    affichageDepuisCellule(ad); // this->afficheDepuisCellule(this->ad);
    std::putchar('\n');
}

void Liste::vide()
{
    if(!testVide()) //  if(!this->testVide())
    {
        suppressionEnTete(); //this->suppressionEnTete()
        vide(); //this->vide()
    }
}

#endif
