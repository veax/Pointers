/***************************************************************/
// compilation:  gpp -std=c++0x main.cpp -o main.exe
//				 c++ -std=c++0x main.cpp -o main.exe

#include <iostream>   // pour pouvoir utiliser cin, cout, endl
#include <string> 	  // pour facilement convertir les entiers et les reels en chaines des caractes (to_string())
#include <math.h>  	  // precision des reels a 3 chiffres significatifs		
using namespace std;  // pour éviter de devoir écrire std::cin, std::cout, std::endl

/*---------------declarations------------*/

struct t_coord {
	double valeur ;
	int indice ;	// 1 à D
	t_coord *suiv ; // coordonnée suivante dans le chaînage
};

struct t_vecteur {
	int dimension ; // positive
	double defaut ; // valeur par défaut
	t_coord *tete ; // du chaînage des coordonnées significative,
					// ordonnées par indices croissant
};

/*------------procedures--------------*/

// initialisation d'un vecteur

void initialiser(t_vecteur &v, int dim, double def){
	while (dim <= 0) {
		cout << "entrez dimension positive! :" << endl;
		cin >> dim;
	}
	v.dimension = dim;
	v.defaut = def;
	v.tete = nullptr;
}

// vider un vecteur

void vider(t_vecteur &v){
	t_coord *temp;
	temp = v.tete;
	while (temp != nullptr) {
		temp = (v.tete)->suiv;
		delete v.tete;
		v.tete = temp;
	}
	
}

//modifier vecteur

void modifier(t_vecteur &v, int ind, double val){
	// coherence d`un indice
	while (ind > v.dimension || ind < 1){
			cout << "Entrez un indice plus petit ou egal a une dimension d`une vecteur: " << endl;
			cin >> ind;
	}

	// cas d`un valeur different d`un valeur par default
	if (val != v.defaut) {
		if (v.tete == nullptr){			// cas d`un chainage vide
			t_coord *nouveau;
			nouveau = new (t_coord);
			(nouveau)->valeur = val;
			(nouveau)->indice = ind;
			(nouveau)->suiv = nullptr;    
			v.tete = nouveau;
		}

		else{							// cas d`un chainage pas vide
			t_coord *temp;
			temp = v.tete; 


			// cas d`un seul maillon:
			if ((temp)->suiv == nullptr){
				if ((temp)->indice == ind){
					(temp)->valeur = val;
					cout << "change" << endl;
				}
				else if ((temp)->indice > ind){
					t_coord *nouveau;
					nouveau = new(t_coord);
					(*nouveau).valeur = val;    
					(*nouveau).indice = ind;
					(*nouveau).suiv = temp;
					v.tete = nouveau;
				}
				else{
					t_coord *nouveau_fin;
					nouveau_fin = new(t_coord);
					(*nouveau_fin).valeur = val;    
					(*nouveau_fin).indice = ind;
					(*nouveau_fin).suiv = nullptr; 
					(temp)->suiv = nouveau_fin;
				}
			}


			// cas d`un chainage contenant au moins 2 maillons:
			else{
				t_coord *precedent;

				while ((temp)->suiv != nullptr && (temp)->indice != ind && (temp)->indice <= ind ){
				// condition d`arret: on trouve le maillon avec notre indice ou l`indice est plus grand que l`indice indique ou il n`y a pas 
				// de maillon avec indice indique
					precedent = temp;
					temp = (temp)->suiv;
				}
				
				if ((temp)->suiv == nullptr){
					if ((temp)->indice == ind){
						(temp)->valeur = val;
					}
					else if((temp)->indice > ind){    
						t_coord *nouveau;
						nouveau = new(t_coord);
						(*nouveau).valeur = val;    
						(*nouveau).indice = ind;
						(*nouveau).suiv = temp;
						delete temp;
						(*precedent).suiv = nouveau;
					}
					else {
						t_coord *nouveau_fin;
						nouveau_fin = new(t_coord);
						(*nouveau_fin).valeur = val;    
						(*nouveau_fin).indice = ind;
						(*nouveau_fin).suiv = nullptr; 
						(temp)->suiv = nouveau_fin;
					}
				}

				else if ((temp)->indice == ind){
					(temp)->valeur = val;
				}

				else if((temp)->indice > ind){
					t_coord *nouveau;
					nouveau = new(t_coord);
					(*nouveau).valeur = val;    
					(*nouveau).indice = ind;
					(*nouveau).suiv = temp;
					if (temp == v.tete){
						v.tete = nouveau;
					}
					else {
						temp = nouveau;
					}
				}
			}
			
		}
		
	}







	// cas d`un valeur egal a un valeur par default
	else {    
		t_coord *temp;
		temp = v.tete;

		if (v.tete == nullptr){
			// on fait rien car si la chainage des chiffres significatifs est vide 
			//ca veut dire qu`on a que nos valeurs par default et la valeur default saisie
			//par utilisateur ne faut pas entrer dans notre chainage des chiffres signif 
			//par definition
		}

		

		//cas d`un seul maillon:
		else if ((temp)->suiv == nullptr){
			if ((temp)->indice == ind){
				delete v.tete;
				v.tete = nullptr;
			}
			else {
				// rien faire
			}
		}





		// cas d`un chainage contenant au moins 2 maillons:
		else{
			t_coord *precedent, *suivant;
			 
			while ((temp)->suiv != nullptr && (temp)->indice != ind && (temp)->indice <= ind){
				precedent = temp;
				temp = (temp)->suiv;
			}

			if ((temp)->suiv == nullptr){
				if ((temp)->indice == ind){
					(precedent)->suiv = nullptr;
					delete temp;
				}
				else{
					//rien faire, car on stock pas les valeurs par default dans le chainage
				}
			}

			else if ((temp)->indice == ind){
				if (temp == v.tete){
					suivant = (temp)->suiv;
					delete temp;
					v.tete = suivant;
				}
				else {
					(precedent)->suiv = (temp)->suiv;
					delete temp;
				}
			}

			else if((temp)->indice > ind){
				//rien faire
			}
		}
	}
}


/*------------entrees/sorties--------------*/

void saisir(t_vecteur &v){
	bool fin = false;
	string rep;
	int cpt = 1;
	while (fin == false && cpt <= v.dimension){
		int ind;
		double val;
		cout << "----------saisie d`une valeur--------" << endl;
		cout << " " << endl;
		cout << "Indice?: " << endl;
		cin >> ind;
		while (ind > v.dimension || ind < 1){
			cout << "Entrez un indice positive plus petit ou egal a une dimension d`une vecteur: " << endl;
			cin >> ind;
		}
		cout << "Valeur?: " << endl;
		cin >> val;
		while (val == v.defaut){
			cout << "Entrez une valeur significative (la valeur differente d`une valeur par default): " << endl;
			cin >> val;
		}
		modifier(v, ind, val);
		cpt++;
		if (cpt <= v.dimension){
			cout << "Voulez-vous saisir d`autre valeur? (o/n): " << endl;
			cin >> rep;
			if (rep == "n"){
				fin = true;
			}
		}
	}
}

void afficher(t_vecteur v, bool complet){
	string seq;
	t_coord *temp;
	temp = v.tete;
	string indice;
	string valeur;
	if (complet){
		cout << "" << endl;
		cout << "**************affichage complet d`un vecteur creux**************" << endl;
		cout << " " << endl;

		// on evite la virguille a la fin d`un affichage
		if (temp != nullptr){
				if ((*temp).indice == 1){
					seq += to_string((*temp).valeur);
					temp = (*temp).suiv;
				}
				else {
					seq += to_string(v.defaut);
				}
		}
		else {
			seq += to_string(v.defaut);
		}

		for (int i = 1; i < v.dimension; i++){
			if (temp != nullptr){
				if ((*temp).indice == i+1){
					seq +=  ", " + to_string((*temp).valeur);
					temp = (*temp).suiv;
				}
				else {
					seq += ", " + to_string(v.defaut);
				}
			}
			else {
				seq += ", " + to_string(v.defaut);
			}
			
		}
		cout << "[" << seq << "]" << endl;

	}
	else {
		cout << "" << endl;
		cout << "**************affichage des valeurs significatifs**************" << endl;
		cout << " " << endl;

		// on affiche les paires des valeurs significatifs (indice:valeur)
		while((temp)->suiv != nullptr){
			seq = seq + to_string((*temp).indice) + ":" + to_string((*temp).valeur) + ", ";
			temp = (*temp).suiv;
		}
		seq += to_string((*temp).indice) + ":" + to_string((*temp).valeur);
		cout << "[" << seq << "]" << endl;
	}
}


/*------------fonctions--------------*/
t_vecteur somme(t_vecteur v1, t_vecteur v2){
	t_vecteur v3;
	if (v1.dimension != v2.dimension){
		cout << "les dimensions des 2 vecteurs doivent etre egaux" << endl;
		return v3;
	}
	else {
		double def = v1.defaut + v2.defaut;		// valeur par default
		int dim = v1.dimension;
		initialiser(v3, dim, def);
		t_coord *temp1, *temp2;
		temp1 = v1.tete;
		temp2 = v2.tete;
		for (int i = 0; i < v3.dimension; i++){
			if (temp1 != nullptr && temp2 != nullptr){
				if ((temp1)->indice == i+1){
					// cas: chiffre signif1 + chiffre signif2
					if ((temp2)->indice == i+1){
						modifier(v3, i+1, (temp1)->valeur + (temp2)->valeur);
						temp1 = (temp1)->suiv;
						temp2 = (temp2)->suiv;
					}

					// cas: chiffre signif1 + def2
					else{
						modifier(v3, i+1, (temp1)->valeur + v2.defaut);
						temp1 = (temp1)->suiv;
					}
				}

					// cas: def1 + chiffre signif2
				else if ((temp2)->indice == i+1){
					modifier(v3, i+1, v1.defaut + (temp2)->valeur);
					temp2 = (temp2)->suiv;
				}
					// cas: de1+def2
				else {
					// rien faire
				}
			}
			else if (temp1 != nullptr || temp2 != nullptr){
				if (temp1 != nullptr){
					if ((temp1)->indice == i+1){
						modifier(v3, i+1, (temp1)->valeur + v2.defaut);
						temp1 = (temp1)->suiv;
					}
				}
				else if (temp2 != nullptr){
					if ((temp2)->indice == i+1){
						modifier(v3, i+1, v1.defaut + (temp2)->valeur);
						temp2 = (temp2)->suiv;
					}
				}
			}
			else {
			}
		}
		return v3;
	}	// fin else
}


/**************** fonction principale *************************/
int main(){
	t_vecteur vect1;
	t_vecteur vect2;
	t_vecteur vect3;
	initialiser(vect1,4,7);
	initialiser(vect2,4,5);
	saisir(vect1);
	saisir(vect2);
	afficher(vect1, true);
	afficher(vect2, true);
	vect3 = somme(vect1,vect2);
	afficher(vect3, true);
/*
	t_vecteur vect;
	initialiser(vect,4,7);
	saisir(vect);
	afficher(vect, true);
	//modifier(vect, 2, 7);
	afficher(vect, false);*/
	return 0;
}
