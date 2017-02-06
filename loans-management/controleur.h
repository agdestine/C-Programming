#ifndef CONTROLEUR_H_INCLUDED
#define CONTROLEUR_H_INCLUDED

void ecouter_choix();
int verifier_login(char username[], char password[]);
void get_data_saisir_pret();
void display_liste_prets();
void display_liste_clients();
void afficher_table_amortissement(char code[]);
void afficher_table_amortissement1(struct Pret p1);



#endif // CONTROLEUR_H_INCLUDED
