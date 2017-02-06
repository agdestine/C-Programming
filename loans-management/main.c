#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <dos.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>

#include "domaine.h"
#include "controleur.h"
#include "vues.h"



static struct User_account accounts[10];

/* Cette fonction lit le contenu du fichier de securite
 * pour realiser l'authentification de l'utilisateur.
 */
void read_file(struct User_account accounts[])
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
        fscanf(fp, "%s %s", accounts[j].id, accounts[j].password);
        ++j;
    }
};




void gotoxy(int x, int y)
{
   HANDLE hConsoleOutput;
   COORD dwCursorPosition;
//   cout.flush();
   dwCursorPosition.X = x;
   dwCursorPosition.Y = y;
   hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}







/* Cette fonction affiche la liste des prets (contenus dans le ficher pret.dat) pour MODIFICATION.
 */
accueil_modifier_pret() {
draw_main_frame();
print_title("LISTE DES PRETS");\

gotoxy(2, 8); printf("+============+===========+============+==========+==========+");
   gotoxy(2, 9); printf("| Numero Pret| Date      | Montant    | Terme    | Taux     |");
   gotoxy(2,10); printf("|            | Ouverture |            | (mois)   | intérêt  |");
   gotoxy(2,11); printf("+============+===========+============+==========+==========+");

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
       // gotoxy(2,12+i); printf("|%11s |           |%11.2f |%10d |%9.2f |", i+1, pret.numero_pret, pret.montant, pret.terme, pret.taux_interet);
        gotoxy(2,12+i); printf("|%11s |           |%11.2f |%10d |%8.2f |", pret.numero_pret, pret.montant, pret.terme, pret.taux_interet);
        i++;
   }
   char select1[20];
   print_footer("Saisir le numero de pret a modifier : ");
   scanf_s("%s", &select1);
}











void main ()
{

    //draw_empty_screen();
    draw_main_frame();
    display_form_login();
    char userid[] = "uim", password[]="123", p[15], u[15];
    int n = 1,a,b;
    while(n<=3)
    {
        gotoxy(23,10); printf("                    "); gotoxy(23,10); // Clear password field
        gotoxy(23, 9); printf("                    "); gotoxy(23, 9); // Clear username field
        scanf("%s",u);
        gotoxy(23,10); printf("                    "); gotoxy(23,10);
        scanf("%s",p);
        int resultat = verifier_login(u,p);

        if(resultat==1)
        {
            while(1) {
            gotoxy(0,0);
            display_main_menu();
            ecouter_choix();
            }

            break;
        }
        else
        {
            gotoxy(2,21);
            printf("Mot de passe ou username incorrect. %d tentative(s) restante(s).",3-n);
        }
        n++;
    }
    getch();

    read_file(accounts);
    printf("%s, %s, %s, %s\n",
        accounts[0].id, accounts[0].password,
        accounts[1].id, accounts[1].password);
    return 0;
}
