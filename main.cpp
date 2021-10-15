// LIFAP6 - Automne 2017 - R. Chaine

#include "element.h"
#include "skiplist.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
  srand(time(NULL)); //pour que les nombres aléatoires soient vraiment aléatoires
  Skiplist sissi;
  Cellule *p=NULL;
  for(int i=0;i<5;i++)
  { 
    int K = rand()%100;
    cout <<endl<< K << " ";
    sissi.insere(K);}
  cout << endl;
  sissi.affichage();
  /*sissi.etablissementNiveaux();*/
  for(int j=0; j<MAX_NIVEAUX; j++)
    {
      cout << "niveau " << j << endl;
      sissi.affichageParNiveau(j);
      cout<<endl;
    }
  int K = rand()%100; 
  cout << "nouveau nombre " << K << endl;
  sissi.insere(K);
  
  for(int j=0; j<MAX_NIVEAUX; j++)
    {
      cout << "niveau " << j << endl;
      sissi.affichageParNiveau(j);
      cout<<endl;
    }
  p=sissi.recherche(K);
  if(p!=nullptr)
  cout << K << " est dans la skipliste" << endl;
  else cout << K << " n'est pas dans la skipliste" << endl;
  sissi.supprime(K);
  for(int j=0; j<MAX_NIVEAUX; j++)
    {
      cout << "niveau " << j << endl;
      sissi.affichageParNiveau(j);
      cout<<endl;
    }

  p=sissi.recherche(15);
  if(p!=nullptr)
  cout << K << " est dans la skipliste" << endl;
  else cout << K << " n'est pas dans la skipliste" << endl;
  return 0;
}
