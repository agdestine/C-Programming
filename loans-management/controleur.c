
/* Cette fonction collecte les données introduites sur la forme de saisie d'un pret.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "domaine.h"

/* Cette fonction prend le choix de l'utilisateur
 * et execute l'action correspondant au choix.
 */
void ecouter_choix() {
    int choix = 0;
    print_footer("Choisir un element du menu : ");
    scanf("%d",&choix);

    switch (choix)
          {
              case 1:
                  display_form_saisir_pret();
                  get_data_saisir_pret();
                  getch();
                  break;
              case 2:
                  draw_main_frame();
                  display_liste_prets();
                  print_footer("Saisir le numero de pret a modifier : ");
                  char pret_a_modifier[20];
                  scanf_s("%s", pret_a_modifier);
                  display_form_modifier_pret(pret_a_modifier);
                  get_data_modifier_pret(pret_a_modifier);
                  getch();
                  break;
              case 3:
                  display_liste_prets();
                  print_footer("Saisir le numero de pret a afficher : ");
                  char pret_a_afficher[20];
                  scanf_s("%s", pret_a_afficher);
                  afficher_table_amortissement(pret_a_afficher);
                  getch();
                  break;
              case 4:
                  display_liste_clients();
                  getch();
                  break;
              case 5:
                  exit(1);
          }
};


/* Cette fonction lit le contenu du fichier de securite
 * pour realiser l'authentification de l'utilisateur.
 */
int verifier_login(char username[], char password[])
{
    FILE *fp;
    int i=0;   // count how many lines are in the file
    int c;
    fp=fopen("C:\\Travaux\\securite.dat", "r");
    while(!feof(fp)) {
        c=fgetc(fp);
        if(c=='\n')
            ++i;
    }
    int j=0;
    rewind(fp);  // Line I added
        // read each line and put into accounts
    while(j!=i-1) {
        char username_in_file[20];
        char password_in_file[20];
        fscanf(fp, "%s %s", username_in_file, password_in_file);
        int a = strcmp(username, username_in_file);
        int b = strcmp(password, password_in_file);
        if(a==0&&b==0) {return 1;}
        ++j;
    }
    return 0;
};

/*
 * Cette fonction lit les donnees introduites par l'utilisateur sur le formulaire de saisie de pret.
 */
void get_data_saisir_pret() {
    struct Client client;
    struct Pret pret;
    gotoxy(17, 8);
    scanf("%s",client.code);
    gotoxy(17, 9);
    scanf("%s",client.nom);
    gotoxy(17,10);
    scanf("%s",client.prenom);
    gotoxy(17,11);
    scanf("%s",client.nif_cin);
    gotoxy(17,12);
    scanf("%s",client.telephone);
    gotoxy(17,13);
    scanf("%s",client.email);
    gotoxy(17,14);
    scanf("%s",client.adresse);

    strncpy(pret.id_client,client.code,10);

    gotoxy(55, 8);
    scanf("%s",pret.numero_pret);
    gotoxy(55, 9);
    scanf("%f",&pret.montant);
    gotoxy(55,10);
    scanf("%i",&pret.terme);
    gotoxy(55,11);
    scanf("%f",&pret.taux_interet);

    pret.date_ouverture = time(NULL);

    FILE *fp;
    fp = fopen("C:\\Travaux\\client.dat", "ab");
    if(fp==NULL)
    {
        printf("La création du fichier <<client.dat>> a echoué.");
        getch();
        exit(1);
    }
    fwrite(&client, sizeof(client),1,fp);
    fclose(fp);

    fp = fopen("C:\\Travaux\\pret.dat", "ab");
    if(fp==NULL)
    {
        printf("La création du fichier <<pret.dat>> a echoué.");
        getch();
        exit(1);
    }
    fwrite(&pret, sizeof(pret),1,fp);
    fclose(fp);

    draw_main_frame();
    afficher_table_amortissement1(pret);
};

/*
 * Cette fonction lit les donnees introduites par l'utilisateur sur le formulaire de modification de pret.
 */
void get_data_modifier_pret(char numero_pret[]) {

    struct Pret pret;

    /*** fp1 est utilise pour la pointer sur un fichier temporaire servant a la modification ***/
    FILE *fp, *fp1;
    fp  = fopen("C:\\Travaux\\pret.dat", "rb");
    fp1 = fopen("C:\\Travaux\\pret_temp.dat", "wb");

    int temoin = 0; // Temoin indiquant si le pret a ete trouve dans le fichier.
    while(1) {
        fread(&pret, sizeof(struct Pret), 1, fp);

        if(feof(fp)) {
            break;
        }
        if(strcmp(pret.numero_pret, numero_pret)==0) {
            temoin = 1;
            gotoxy(55, 8);
            scanf("%s",pret.numero_pret);
            gotoxy(55, 9);
            scanf("%f",&pret.montant);
            gotoxy(55,10);
            scanf("%i",&pret.terme);
            gotoxy(55,11);
            scanf("%f",&pret.taux_interet);
            //Ecrire le pret modifie dans un fichier temporaire.
            fwrite(&pret, sizeof(pret),1,fp1);
        } else {
            //Ecrire aussi les autres prets dans le fichier tempon mais sans modification
            fwrite(&pret, sizeof(pret),1,fp1);
        }
    }
    fclose(fp);
    fclose(fp1);

    if(temoin == 0) {
        print_footer("Aucun enregistrement trouve.");
    } else {
        fp  = fopen("C:\\Travaux\\pret.dat", "wb");
        fp1 = fopen("C:\\Travaux\\pret_temp.dat", "rb");

        while(1) {
            fread(&pret, sizeof(struct Pret),1,fp1);

            if(feof(fp1)) {
                break;
            }
            fwrite(&pret, sizeof(struct Pret),1,fp);

        }
    }
    fclose(fp);
    fclose(fp1);


    afficher_table_amortissement1(pret);
};

/* Cette fonction affiche la liste des prets.
 */
void display_liste_prets() {
   draw_main_frame();
   print_title("LISTE DES PRETS");

   gotoxy(2, 8); printf("+============+===========+============+==========+==========+");
   gotoxy(2, 9); printf("| Numero Pret| Date      | Montant    | Terme    | Taux     |");
   gotoxy(2,10); printf("|            | Ouverture |            | (mois)   | interet  |");
   gotoxy(2,11); printf("+============+===========+============+==========+==========+");

   FILE *infile;
   struct Pret pret;

   /*** ouvrir le fichier pret.dat ***/
   infile = fopen ("C:\\Travaux\\pret.dat","rb");
   if (infile == NULL)
     {
      fprintf(stderr, "\nImpossible d'ouvrir pret.dat\n\n");
      exit (1);
     }
    int i = 0;
    while(1) {
        fread (&pret, sizeof(struct Pret), 1, infile);
        if(feof(infile)) {
            break;
        }
        gotoxy(2,12+i); printf("|%11s |           |%11.2f |%10d |%8.2f |", pret.numero_pret, pret.montant, pret.terme, pret.taux_interet);
        i++;
    }
    fclose(infile);
};

/* Cette fonction affiche la table d'amortissement a partir du numero du pret.
 */
void afficher_table_amortissement(char code[]) {
   FILE *infile;
   struct Pret pret;
   /*** open the accounts file ***/
   infile = fopen ("C:\\Travaux\\pret.dat","r");

  if (infile == NULL)
     {
      fprintf(stderr, "\nImpossible d'ouvrir pret.dat\n\n");
      exit (1);
     }
   int i = 0;
   while (fread (&pret, sizeof(struct Pret), 1, infile)) {
        if(strcmp(pret.numero_pret, code)==0) {
            afficher_table_amortissement1(pret);
            break;
        }
   }
   fclose(infile);
}

/* Cette fonction affiche la table d'amortissement a partir de l'objet struct pret.
 */
void afficher_table_amortissement1(struct Pret p1) {
   draw_main_frame();
   print_title("TABLE D'AMORTISSEMENT");
   gotoxy(2, 7);
   printf("-- PRET # : %s --", p1.numero_pret);

   //Calcul amortissement fixe
   float interet_mensuel = p1.taux_interet*0.01/12.0;
   float versement = p1.montant * interet_mensuel / (1.0-powl(1.0+interet_mensuel,-6));
   float v = versement;
   float solde = p1.montant;
   float portion_int = 0.0;
   float portion_cap = 0.0;


   gotoxy(2, 8); printf("+============+===========+==========+==========+==========+============+");
   gotoxy(2, 9); printf("| Mensualite | Date de   | Montant a| Portion  | Portion  | Capital    |");
   gotoxy(2,10); printf("|            | versement | verser   | capital  | interet  | restant    |");
   gotoxy(2,11); printf("+============+===========+==========+==========+==========+============+");
for(int i=0; i<6; i++) {
    portion_int = solde * interet_mensuel;
    portion_cap = v - portion_int;
    solde = solde - portion_cap;
 gotoxy(2,12+i); printf("|     %2d     |           |%9.2f |%9.2f |%9.2f |%11.2f |", i+1, v, portion_cap, portion_int, solde);
}
  // gotoxy(2,17); printf("+------------+-----------+-----------+------------+------------+----------+");

}

/* Cette fonction affiche la liste des emprunteurs.
 */
void display_liste_clients() {
   draw_main_frame();
   print_title("LISTE DES CLIENT");

   gotoxy(2, 8); printf("+==========+=============+============+===========+=====================+");
   gotoxy(2, 9); printf("| Code     | Prenom      | Nom        | Telephone | email               |");
   gotoxy(2,10); printf("+==========+=============+============+===========+=====================+");

   FILE *infile;
   struct Client client;

   /*** ouvrir le fichier pret.dat ***/
   infile = fopen ("C:\\Travaux\\client.dat","rb");
   if (infile == NULL)
     {
      print_footer("Impossible d'ouvrir client.dat");
      exit (1);
     }
    int i = 0;
    while(1) {
        fread (&client, sizeof(struct Client), 1, infile);
        if(feof(infile)) {
            break;
        }
        gotoxy(2,11+i); printf("| %8s | %11s | %10s | %9s | %19s |", client.code, client.prenom, client.nom, client.telephone, client.email);
        i++;
    }
    fclose(infile);

};





