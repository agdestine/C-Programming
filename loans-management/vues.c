#ifndef VUES_C_INCLUDED
#define VUES_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "domaine.h"

/* Cette fonction affiche la structure principale de l'écran.
 */

void draw_main_frame() {
gotoxy(0,0);
printf("+------------------------------------------------------------------------------+");
printf("|                               BANQUE DE L'OUEST                              |");
printf("|                         SYSTEME DE GESTION DES PRETS                         |");
printf("+------------------------------------------------------------------------------+");
printf("|                                                                              |");
printf("+------------------------------------------------------------------------------+");
printf("|                                                                              |");
printf("|                                                                              |");
printf("|                                                                              |");
printf("|                                                                              |");
printf("|                                                                              |");
printf("|                                                                              |");
printf("|                                                                              |");
printf("|                                                                              |");
printf("|                                                                              |");
printf("|                                                                              |");
printf("|                                                                              |");
printf("|                                                                              |");
printf("|                                                                              |");
printf("|                                                                              |");
printf("+------------------------------------------------------------------------------+");
printf("|                                                                              |");
printf("+------------------------------------------------------------------------------+");
};

/* Cette fonction permet d'afficher le titre de la fonctionnalite dans la position adequate au niveau de l'ecran.
 */
void print_title(char title[]) {
    gotoxy(2,4);
    printf(title);
};

/* Cette fonction permet d'afficher un message dans la position adequate au niveau de l'ecran.
 */
void print_footer(char message[]) {
    gotoxy(2,21);
    printf(message);
};

/* Cette fonction affiche le contenu de l'ecran EC-1 (ecran de connexion).
 */
void display_form_login() {
   print_title("AUTHENTIFICATION");
   gotoxy(2,7);
   printf("Saisissez votre <<nom d'utilisateur>> et <<mot de passe>>;");
   gotoxy(3,9);
   printf("Nom d'utilisateur : ");
   gotoxy(3,10);
   printf("Mot de passe      : ");
};

/* Cette fonction affiche le menu principal.
 */
void display_main_menu(void) {
   draw_main_frame();
   print_title("MENU PRINCIPAL");
   gotoxy(2, 7);
   printf("1- Saisir un nouveau pret");
   gotoxy(2, 8);
   printf("2- Modifier un pret");
   gotoxy(2, 9);
   printf("3- Lister les prets en cours ");
   gotoxy(2,10);
   printf("4- Lister les emprunteurs ");
   gotoxy(2,11);
   printf("5- Quitter ");
};

/* Cette fonction affiche la forme pour la saisie d'un pret.
 */
void display_form_saisir_pret() {
   draw_main_frame();
   print_title("SAISIR UN NOUVEAU PRET");
   gotoxy(2, 7);
   printf("-Emprunteur-");
   gotoxy(3, 8);
   printf("Code interne: ");
   gotoxy(3, 9);
   printf("Nom         : ");
   gotoxy(3,10);
   printf("Prenom      : ");
   gotoxy(3,11);
   printf("NIF / CIN   : ");
   gotoxy(3,12);
   printf("Telephone   : ");
   gotoxy(3,13);
   printf("Email       : ");
   gotoxy(3,14);
   printf("Adresse     : ");


   gotoxy(40, 7);
   printf("-Pret-");
   gotoxy(41, 8);
   printf("Numero      : ");
   gotoxy(41, 9);
   printf("Montant     : ");
   gotoxy(41,10);
   printf("Terme       : ");
   gotoxy(41,11);
   printf("Taux int.   : ");

};

/* Cette fonction affiche la forme pour la modifier d'un pret.
 */
void display_form_modifier_pret(char numero_pret[]) {
    /*** Verifier si le pret exist ***/
    struct Pret pret;
    struct Client client;

    int temoin1 = 0;
    int temoin2 = 0;

    FILE *fp;
    fp = fopen ("C:\\Travaux\\pret.dat","rb");
    if (fp == NULL)
     {
      print_footer("Impossible d'ouvrir pret.dat");
      exit (1);
     }

    while(1) {
        fread (&pret, sizeof(struct Pret), 1, fp);
        if(feof(fp)) {
            break;
        }
        if(strcmp(pret.numero_pret,numero_pret)==0) {
            temoin1 = 1;
        }

    }
    fclose(fp);

    if(temoin1 == 1) {
        fp = fopen ("C:\\Travaux\\client.dat","rb");
        if (fp == NULL)
         {
          print_footer("Impossible d'ouvrir client.dat");
          exit (1);
         }

        while(1) {
            fread (&client, sizeof(struct Client), 1, fp);
            if(feof(fp)) {
                break;
            }
            if(strcmp(pret.id_client,client.code)==0) {
                temoin2 = 1;
            }

        }
    }

    if(temoin2 == 1) {
        /*** Affcher le formulaire si les donnees existent deja ***/
        draw_main_frame();
   print_title("MODIFIER UN PRET");
   gotoxy(2, 7);
   printf("-Emprunteur-");
   gotoxy(3, 8);
   printf("Code interne: %s", client.code);
   gotoxy(3, 9);
   printf("Nom         : %s", client.nom);
   gotoxy(3,10);
   printf("Prenom      : %s"), client.prenom;
   gotoxy(3,11);
   printf("NIF / CIN   : %s"), client.nif_cin;
   gotoxy(3,12);
   printf("Telephone   : %s"), client.telephone;
   gotoxy(3,13);
   printf("Email       : %s"), client.email;
   gotoxy(3,14);
   printf("Adresse     : %s"), client.adresse;


   gotoxy(40, 7);
   printf("-Pret-");
   gotoxy(41, 8);
   printf("Numero      : ");
   gotoxy(41, 9);
   printf("Montant     : ");
   gotoxy(41,10);
   printf("Terme       : ");
   gotoxy(41,11);
   printf("Taux int.   : ");

    } else {
        /*** La donnee a modifier n'existe pas. ***/
        print_footer("Impossible de recuperer le pret ou le client.");
    }

};

#endif // VUES_C_INCLUDED
