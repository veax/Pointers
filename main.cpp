/***************************************************************/
// compilation:  gpp -std=c++0x main.cpp -o main.exe
//				 c++ -std=c++0x main.cpp -o main.exe

#include <iostream>   // pour pouvoir utiliser cin, cout, endl
#include <string> 	  // pour facilement convertir les entiers et les reels en chaines de caracteres (to_string())
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
				}
				else if ((temp)->indice > ind){
					t_coord *nouveau;
					nouveau = new(t_coord);
					(nouveau)->valeur = val;    
					(nouveau)->indice = ind;
					(nouveau)->suiv = v.tete;
					v.tete = nouveau;
					
				}
				else{
					t_coord *nouveau_fin;
					nouveau_fin = new(t_coord);
					(nouveau_fin)->valeur = val;    
					(nouveau_fin)->indice = ind;
					(nouveau_fin)->suiv = nullptr; 
					(temp)->suiv = nouveau_fin;
				}
			}

			// cas d`un chainage contenant au moins 2 maillons:
			else{
				t_coord *precedent;
				while ((temp)->suiv != nullptr && (temp)->indice < ind ){
				// condition d`arret: on trouve le maillon avec notre indice ou l`indice est plus grand que l`indice indique ou il n`y a pas 
				// de maillon avec indice indique
					precedent = temp;
					temp = (temp)->suiv;
				}
				
				// le cas de dernier maillon
				if ((temp)->suiv == nullptr){
					if ((temp)->indice == ind){
						(temp)->valeur = val;
					}
					else if((temp)->indice > ind){    
						t_coord *nouveau;
						nouveau = new(t_coord);
						(nouveau)->valeur = val;    
						(nouveau)->indice = ind;
						(nouveau)->suiv = temp;
						(precedent)->suiv = nouveau;
					}
					else {
						t_coord *nouveau_fin;
						nouveau_fin = new(t_coord);
						(nouveau_fin)->valeur = val;    
						(nouveau_fin)->indice = ind;
						(nouveau_fin)->suiv = nullptr; 
						(temp)->suiv = nouveau_fin;
					}
				}

				else if ((temp)->indice == ind){
					(temp)->valeur = val;
				}

				// le cas inserer maillon avant
				else if((temp)->indice > ind){
					t_coord *nouveau;
					nouveau = new(t_coord);
					(nouveau)->valeur = val;    
					(nouveau)->indice = ind;
					(nouveau)->suiv = temp;
					if (temp == v.tete){
						v.tete = nouveau;
					}
					else {
						(precedent)->suiv = nouveau;
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
			while ((temp)->suiv != nullptr && (temp)->indice < ind){
				precedent = temp;
				temp = (temp)->suiv;
			}

			if ((temp)->suiv == nullptr){
				if ((temp)->indice == ind){
					(precedent)->suiv = nullptr;
					delete temp;
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
		}
	}
}


/*------------entrees/sorties--------------*/

void saisir(t_vecteur &v){
	bool fin = false;
	string rep;
	while (fin == false){
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
		cout << "Voulez-vous saisir d`autre valeur? (o/n): " << endl;
		cin >> rep;
		if (rep == "n"){
			fin = true;
		}
	}
}

void afficher(t_vecteur v, bool complet){
	string seq;
	t_coord *temp;
	temp = v.tete;
	if (complet){
		cout << "" << endl;
		cout << "**************affichage complet d`un vecteur creux**************" << endl;
		cout << " " << endl;

		// on evite la virguille a la fin d`un affichage
		if (temp != nullptr){
				if ((temp)->indice == 1){
					seq += to_string((temp)->valeur);
					temp = (temp)->suiv;
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
				if ((temp)->indice == i+1){
					seq +=  ", " + to_string((temp)->valeur);
					temp = (temp)->suiv;
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
		cout << "" << endl;
		if (temp == nullptr){		// le cas si on a vide le vecteur
			cout << "[]" << endl;
		}
		else {
			// on affiche les paires des valeurs significatifs (indice:valeur)
			while((temp)->suiv != nullptr){
				seq = seq + to_string((temp)->indice) + ":" + to_string((temp)->valeur) + ", ";
				temp = (temp)->suiv;
			}
			seq += to_string((temp)->indice) + ":" + to_string((temp)->valeur);
			cout << "[" << seq << "]" << endl;
		}
		
	}
}


/*------------fonctions--------------*/

// calculer la somme des 2 vecteurs
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
		int i = 0;
		while (temp1 != nullptr || temp2 != nullptr){
			if (temp1 != nullptr && temp2 != nullptr){
				if ((temp1)->indice == i+1){
					// 1 cas: chiffre signif1 + chiffre signif2
					if ((temp2)->indice == i+1){
						modifier(v3, i+1, (temp1)->valeur + (temp2)->valeur);
						temp1 = (temp1)->suiv;
						temp2 = (temp2)->suiv;
					}

					// 2 cas: chiffre signif1 + def2
					else{
						modifier(v3, i+1, (temp1)->valeur + v2.defaut);
						temp1 = (temp1)->suiv;
					}
				}

					// 3 cas: def1 + chiffre signif2
				else if ((temp2)->indice == i+1){
					modifier(v3, i+1, v1.defaut + (temp2)->valeur);
					temp2 = (temp2)->suiv;
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
			i++;
		}
		return v3;
	}	// fin else
}


// calculer le produit vectoriel
double produit(t_vecteur v1, t_vecteur v2){
	double prodScal = 0;
	if (v1.dimension != v2.dimension){
		cout << "les dimensions des 2 vecteurs doivent etre egaux" << endl;
		return prodScal = -1;
	}
	else {
		int dim = v1.dimension;
		t_coord *temp1, *temp2;
		temp1 = v1.tete;
		temp2 = v2.tete;
		if (temp1 == nullptr && temp2 == nullptr){		// le cas avec les vecteurs seulement avec les valeurs defauts
			prodScal = (v1.defaut * v2.defaut)*dim;
			return prodScal;
		}
		else{
			int i = 0;
			while (temp1 != nullptr || temp2 != nullptr){
				if (temp1 != nullptr && temp2 != nullptr){
					if ((temp1)->indice == i+1){
						if ((temp2)->indice == i+1){    // 1 cas: chiffre signif1 + chiffre signif2
							prodScal += (temp1)->valeur * (temp2)->valeur;
							temp1 = (temp1)->suiv;
							temp2 = (temp2)->suiv;
						}
						else{							// 2 cas: chiffre signif1 + def2
							prodScal += (temp1)->valeur * v2.defaut;
							temp1 = (temp1)->suiv;
						}
					}
					else if ((temp2)->indice == i+1){	// 3 cas: def1 + chiffre signif2
						prodScal += v1.defaut * (temp2)->valeur;
						temp2 = (temp2)->suiv;
					}
				}
				
				else if (temp1 != nullptr) {
					if ((temp1)->indice == i+1){
						prodScal += (temp1)->valeur * v2.defaut;
						temp1 = (temp1)->suiv;
					}
				}
				else if (temp2 != nullptr){
					if ((temp2)->indice == i+1){
						prodScal += v1.defaut * (temp2)->valeur;
						temp2 = (temp2)->suiv;
					}
				}
				i++;
			}
			if (i < dim){
				prodScal += (v1.defaut * v2.defaut)*(dim - i);
			}
			return prodScal;
		}	
	}	// fin else
}


/**************** fonction principale *************************/
int main(){
	t_vecteur vect, vect2, vect3;
	initialiser(vect,1000000,5);
	initialiser(vect2, 1000000, 15);
	modifier(vect, 19, 8);
	modifier(vect, 17, 10);
	modifier(vect, 4867, 10);
	modifier(vect, 3123, 10);
	modifier(vect, 45, 8);
	modifier(vect, 52, 8);
	modifier(vect, 987, 8);		
	modifier(vect, 6582, 8);
	vect3 = somme(vect,vect2);
	afficher(vect, false);
	afficher(vect3, false);
	double prod = produit(vect, vect2);
	cout << "produit scalaire est: " << prod << endl;
	vider(vect);
	afficher(vect, false);
	return 0;

}
