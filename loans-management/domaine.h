#ifndef DOMAINE_H_INCLUDED
#define DOMAINE_H_INCLUDED

struct Client
{
    char code[10]; // Code interne
    char nom[20];
    char prenom[25];
    char nif_cin[20];
    char telephone[11];
    char email[20];
    char adresse[25];
};

struct date;

struct Pret
{
    char id_client[10]; //Code interne ref. client
    char numero_pret[15];
    float montant;
    int terme;
    float taux_interet;
    time_t date_ouverture;
};

struct User_account {
    char id[20];
    char password[20];
};


#endif // DOMAINE_H_INCLUDED
