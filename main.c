#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define MAX_LIVRES 100
#define MAX_TITRE 100
#define MAX_EMPRUNTS 500

void menuprincipal();
void gestionbibliotheque();
void menustatistique();
void gestionemprunts();

void afflivres();
void ajouterLivre();
void supprimerLivre();
void modifnbexemp();
void rechercherLivre();
void livdispo();

void ajouterEmprunt();
void empruntsencours();
void empruntsdunadherant();
void affempdateretour();
void enregistrerRetour();
void livresenretard();
void supprimerEnsembleEmprunts();

void compte();
void livresplusempruntes();
void livresjamaisempruntes();
void livresplusempruntesperiode();
void emprunteursplusfrequent();
void obtenirDateActuelle(int *jour, int *mois, int *annee);

int numeros[MAX_LIVRES] = {111, 130, 125, 140, 112, 150, 160, 170, 180, 190, 200, 210};
char titres[MAX_LIVRES][MAX_TITRE] = {
    "Le Petit Prince", "L'Alchimiste", "Le Seigneur des Anneaux",
    "Les Miserables", "1984", "Harry Potter", "Orgueil et Prejuges",
    "Le Comte de Monte-Cristo", "Don Quichotte", "Moby Dick",
    "Guerre et Paix", "Le Vieil Homme et la Mer"
};
int nbexemplaires[MAX_LIVRES] = {12, 9, 18, 8, 10, 15, 7, 11, 3, 13, 5, 7};
int nbLivres = 12;

int matriceEmprunts[MAX_EMPRUNTS][8] = {
    {12345678, 111, 15, 10, 2025, 15, 11, 2025},
    {12345678, 130, 20, 10, 2025, 20, 11, 2025},
    {23456789, 125, 25, 10, 2025, 25, 11, 2025},
    {23456789, 140, 01, 11, 2025, 01, 12, 2025},
    {34567890, 112, 05, 11, 2025, 05, 12, 2025},
    {34567890, 150, 10, 11, 2025, 10, 12, 2025},
    {45678901, 160, 15, 11, 2025, 15, 12, 2025},
    {45678901, 170, 20, 11, 2025, 20, 12, 2025}
};
int nbEmprunts = 8;

void obtenirDateActuelle(int *jour, int *mois, int *annee) {
    time_t t = time(NULL);
    struct tm *dateActuelle = localtime(&t);
    *jour = dateActuelle->tm_mday;
    *mois = dateActuelle->tm_mon + 1;
    *annee = dateActuelle->tm_year + 1900;
}

int main() {
    int choix;
    do {
        menuprincipal();
        printf("Votre choix : ");
        while(scanf("%d", &choix) != 1) {
            system("cls");
            menuprincipal();
            while(getchar() != '\n');
            printf("Votre choix : ");
        }

        switch(choix) {
            case 1:
                gestionbibliotheque();
                break;
            case 2:
                gestionemprunts();
                break;
            case 3:
                menustatistique();
                break;
            case 4:
                printf("Merci d'avoir utilise l'application!");
                Sleep(2000);
                exit(0);
            default:
                printf("\nChoix invalide! Veuillez choisir entre 1 et 4.\n");
                Sleep(2000);
        }
    } while(choix != 4);

    return 0;
}

void menuprincipal() {
    system("cls");
    printf("||========================================================================================================================================================||\n");
    printf("||-----------------------------------------------------BIENVENUE DANS LE MENU PRINCIPAL DE LA BIBLIOTHEQUE------------------------------------------------||\n");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
    printf("||----------------------------------------------------               Veuillez choisir               ------------------------------------------------------||\n");
    printf("||========================================================================================================================================================||\n");
    printf("||                                                           1. GESTION DE LA BIBLIOTHEQUE                                                                ||\n");
    printf("||                                                           2. GESTION DES EMPRUNTS                                                                      ||\n");
    printf("||                                                           3. STATISTIQUES                                                                              ||\n");
    printf("||========================================================================================================================================================||\n");
    printf("||                                                           4. QUITTER L'APPLICATION                                                                     ||\n");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
}

void gestionbibliotheque() {
    system("cls");
    int choix;
    do {
        system("cls");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
        printf("||----------------------------------------------------             GESTION DE LA BIBLIOTHEQUE             ------------------------------------------------||\n");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
        printf("||----------------------------------------------------               Veuillez choisir               ------------------------------------------------------||\n");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
        printf("||                                                           1. AFFICHER TOUS LES LIVRES                                                                  ||\n");
        printf("||                                                           2. AJOUTER UN NOUVEAU LIVRE                                                                  ||\n");
        printf("||                                                           3. SUPPRIMER UN LIVRE                                                                        ||\n");
        printf("||                                                           4. MODIFIER LE NOMBRE D'EXEMPLAIRES                                                          ||\n");
        printf("||                                                           5. RECHERCHER UN LIVRE                                                                       ||\n");
        printf("||                                                           6. AFFICHER LES LIVRES DISPONIBLES                                                           ||\n");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
        printf("||                                                           7. MENU PRINCIPAL                                                                            ||\n");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
        printf("Votre choix : ");
        while(scanf("%d", &choix) != 1) {
            while(getchar() != '\n');
            printf("Votre choix : ");
        }

        switch(choix) {
            case 1:
                afflivres();
                break;
            case 2:
                ajouterLivre();
                break;
            case 3:
                supprimerLivre();
                break;
            case 4:
                modifnbexemp();
                break;
            case 5:
                rechercherLivre();
                break;
            case 6:
                livdispo();
                printf("retour a la gestion de bibliotheque...");
                Sleep(5000);
                system("cls");
                break;
            case 7:
                return;
            default:
                printf("\nChoix invalide!\n");
        }
    } while(choix != 7);
}

void afflivres() {
    int choix1;
    system("cls");

    if (nbLivres == 0) {
        printf("\nAucun livre dans la bibliotheque.\n");
        return;
    }

    printf("||========================================================================================================================================================||\n");
    printf("||=====================================================           AFFICHAGE DES LIVRES           =========================================================||\n");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
    printf("|| %-15s | \t\t\t\t\t%-80s| %14s  ||\n", "Numero", "Titre du Livre", "Exemplaires");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");

    for(int i = 0; i < nbLivres; i++) {
        printf("|| %-15d | \t\t\t\t\t%-70s \t\t| %-15d ||\n", numeros[i], titres[i], nbexemplaires[i]);
    }

    printf("||========================================================================================================================================================||\n");

    do {
        printf("si vous voulez retourner a la gestion du bibliothèque tapez 1 \n ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("si vous voulez retourner a la gestion du bibliothèque tapez 1 \n ");
        }
        Sleep(1000);
    } while (choix1 != 1);

    if (choix1 == 1) {
        printf("Retour a la gestion du bibliothèque....");
        Sleep(2000);
        return;
    }
}

void ajouterLivre() {
    int numero, i, choix1, existe;

    do {
        printf("Choix correct ! , tapez 1\n");
        printf("Mauvais choix ! , Si vous voulez retourner tapez 0 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("Mauvais choix ! , Si vous voulez retourner tapez 0 : ");
        }
        Sleep(1000);
    } while (choix1 != 0 && choix1 != 1);

    if (choix1 == 0) {
        Sleep(2000);
        gestionbibliotheque();
        return;
    }

    if (choix1 == 1) {
        if (nbLivres >= MAX_LIVRES) {
            printf("\nLa bibliotheque est pleine!\n");
            return;
        }

        do {
            existe = 0;
            printf("\nNumero du livre: ");
            while(scanf("%d", &numero) != 1) {
                while(getchar() != '\n');
                printf("\nNumero du livre: ");
            }

            for (i = 0; i < nbLivres; i++) {
                if (numeros[i] == numero) {
                    printf("Ce numero existe deja!\n");
                    existe = 1;
                    Sleep(1000);
                }
            }
        } while(existe == 1);

        printf("Titre du livre: ");
        while(getchar() != '\n');
        scanf(" %[^\n]", titres[nbLivres]);

        printf("Nombre d'exemplaires: ");
        while(scanf("%d", &nbexemplaires[nbLivres]) != 1) {
            while(getchar() != '\n');
            printf("Nombre d'exemplaires: ");
        }

        numeros[nbLivres] = numero;
        nbLivres++;
        printf("\nLivre ajoute avec succes!\n");
        Sleep(2000);
        return;
    }
}

void supprimerLivre() {
    int numero, i, j,choix1;

    do{
        printf("Pour supprimer un livre, tapez 1, pour retourner tapez 0 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("Pour supprimer un livre, tapez 1, pour retourner tapez 0 : ");
        }
        Sleep(1000);
    }while (choix1!=0 && choix1!=1);

    if (choix1==0){
        Sleep(2000);
        gestionbibliotheque();
    }

    if (choix1==1){
        do{
            printf("\nNumero du livre a supprimer: ");
            while(scanf("%d", &numero) != 1) {
                while(getchar() != '\n');
                printf("\nNumero du livre a supprimer: ");
            }

            for (i = 0; i < nbLivres; i++) {
                if (numeros[i] == numero) {
                    for (j = i; j < nbLivres - 1; j++) {
                        numeros[j] = numeros[j + 1];
                        strcpy(titres[j], titres[j + 1]);
                        nbexemplaires[j] = nbexemplaires[j + 1];
                    }
                    nbLivres--;
                    printf("\nLivre supprime avec succes!\n");
                    Sleep(3000);
                    return;
                }
            }
            if (numeros[i] != numero){
                printf("\nLivre non trouve!\n");
                Sleep(1000);
            }
            Sleep(1000);
            return;

        } while (numeros[i] != numero);
    }
}

void modifnbexemp() {
    int numero, nouveauNb, i, trouve,choix1;

    do{
        printf("Pour modifier le nombre d'exemplaires, tapez 1, pour retourner tapez 0 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("Pour modifier le nombre d'exemplaires, tapez 1, pour retourner tapez 0 : ");
        }
        Sleep(1000);
    }while (choix1!=0 && choix1!=1);

    if (choix1==0){
        Sleep(2000);
        return;
    }

    if (choix1==1){
        printf("\nNumero du livre: ");
        while(scanf("%d", &numero) != 1) {
            while(getchar() != '\n');
            printf("\nNumero du livre: ");
        }

        trouve = 0;
        for (i = 0; i < nbLivres; i++) {
            if (numeros[i] == numero) {
                trouve = 1;
                printf("Nombre actuel d'exemplaires: %d\n", nbexemplaires[i]);
                printf("Nouveau nombre d'exemplaires: ");
                while(scanf("%d", &nouveauNb) != 1) {
                    while(getchar() != '\n');
                    printf("Nouveau nombre d'exemplaires: ");
                }
                nbexemplaires[i] = nouveauNb;
                printf("\nNombre d'exemplaires modifie avec succes!\n");
                printf("Retour au gestion du bibliotheque...");
                Sleep(3000);
                return;
            }
        }

        if (trouve == 0) {
            printf("\nLivre non trouve!\n");
        }
    }
}

void rechercherLivre() {
    int choixRecherche, numero, trouve = 0, i;
    char titreRecherche[MAX_TITRE];
    int choix1;

    do {
        printf("Pour rechercher un livre, tapez 1, pour retourner tapez 0 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("Pour rechercher un livre, tapez 1, pour retourner tapez 0 : ");
        }
    } while (choix1 != 0 && choix1 != 1);

    if (choix1 == 0) {
        Sleep(2000);
        return;
    }

    system("cls");
    printf("||========================================================================================================================================================||\n");
    printf("||=============================================================     RECHERCHE D'UN LIVRE     =============================================================||\n");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
    printf("||                                                             1. RECHERCHER PAR NUMERO                                                                   ||\n");
    printf("||                                                             2. RECHERCHER PAR TITRE                                                                    ||\n");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");

    do{
        printf("Votre choix : ");
        while(scanf("%d", &choixRecherche) != 1) {
            while(getchar() != '\n');
            printf("Votre choix : ");
        }
    }while (choixRecherche!=1 && choixRecherche!=2);

    if (choixRecherche == 1) {
        printf("\nEntrez le numero du livre : ");
        while(scanf("%d", &numero) != 1) {
            while(getchar() != '\n');
            printf("\nEntrez le numero du livre : ");
        }

        for (i = 0; i < nbLivres; i++) {
            if (numeros[i] == numero) {
                trouve = 1;
                printf("||========================================================================================================================================================||\n");
                printf("||=================================================================     LIVRE TROUVE     =================================================================||\n");
                printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
                printf("|| Numero du livre      : %-15d                                                                                                                 ||\n", numeros[i]);
                printf("|| Titre du livre       : %-127s ||\n", titres[i]);
                printf("|| Nombre d'exemplaires : %-15d                                                                                                                 ||\n", nbexemplaires[i]);
                printf("||========================================================================================================================================================||\n");
            }
        }

        if (trouve==0) {
            printf("\n>>> Livre non trouve avec le numero %d !\n", numero);
            Sleep(2000);
            return;
        }

    } else if (choixRecherche == 2) {
        printf("\nEntrez le titre du livre : ");
        while(getchar() != '\n');
        scanf(" %[^\n]", titreRecherche);

        printf("||========================================================================================================================================================||\n");
        printf("||====================================================     RESULTATS DE RECHERCHE     ====================================================================||\n");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");

        for (i = 0; i < nbLivres; i++) {
            if (strstr(titres[i], titreRecherche) != NULL) {
                printf("||========================================================================================================================================================||\n");
                printf("||=================================================================     LIVRE TROUVE     =================================================================||\n");
                printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
                printf("|| Numero du livre      : %-15d                                                                                                                 ||\n", numeros[i]);
                printf("|| Titre du livre       : %-127s ||\n", titres[i]);
                printf("|| Nombre d'exemplaires : %-15d                                                                                                                 ||\n", nbexemplaires[i]);
                printf("||========================================================================================================================================================||\n");
                trouve = 1;
            }
        }

        if (trouve==0) {
            printf("\n>>> Aucun livre trouve contenant \"%s\" !\n", titreRecherche);
            Sleep(2000);
            return;
        }

    } else {
        printf("\nChoix invalide!\n");
    }

    if (trouve) {
        printf("\n");
        do {
            printf("Pour retourner a la gestion de la bibliotheque, tapez 1 : ");
            while(scanf("%d", &choix1) != 1) {
                while(getchar() != '\n');
                printf("Pour retourner a la gestion de la bibliotheque, tapez 1 : ");
            }
        } while (choix1 != 1);
        return;
    }
}

void livdispo() {
    int choix1;
    int livredispo ;
    system("cls");

    if (nbLivres == 0) {
        printf("\nAucun livre dans la bibliotheque.\n");
        return;
    }

    livredispo=0;
    for(int i = 0; i < nbLivres; i++) {
        if(nbexemplaires[i] > 0) {
            livredispo++;
        }
    }

    if (livredispo == 0) {
        printf("\nAucun livre disponible dans la bibliotheque.\n");
        return;
    }

    printf("||========================================================================================================================================================||\n");
    printf("||===================================================           LIVRES DISPONIBLES           =============================================================||\n");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
    printf("|| %-15s | \t\t\t\t\t%-80s| %14s  ||\n", "Numero", "Titre du Livre", "Exemplaires");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");

    for(int i = 0; i < nbLivres; i++) {
        if(nbexemplaires[i] > 0) {
            printf("|| %-15d | \t\t\t\t\t%-70s \t\t| %-15d ||\n", numeros[i], titres[i], nbexemplaires[i]);
        }
    }

    printf("||========================================================================================================================================================||\n");
    printf("\nNombre total de livres disponibles : %d\n", livredispo);
    printf("----------------------------------------------------------------------------------\n");

}

void gestionemprunts() {
    system("cls");
    int choix;
    do {
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
        printf("||----------------------------------------------------               GESTION DES EMPRUNTS                 ------------------------------------------------||\n");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
        printf("||----------------------------------------------------               Veuillez choisir               ------------------------------------------------------||\n");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
        printf("||                                                           1. AJOUTER UN EMPRUNT                                                                        ||\n");
        printf("||                                                           2. CONSULTER LES EMPRUNTS D'UN ADHERENT                                                      ||\n");
        printf("||                                                           3. ENREGISTRER LE RETOUR D'UN LIVRE                                                          ||\n");
        printf("||                                                           4. AFFICHER LA LISTE DES EMPRUNTS EN COURS                                                   ||\n");
        printf("||                                                           5. AFFICHER LES LIVRES EN RETARD DE RETOUR                                                   ||\n");
        printf("||                                                           6. AFFICHER LES EMPRUNTS RELATIFS A UNE DATE DE RETOUR PREVUE                                ||\n");
        printf("||                                                           7. SUPPRIMER UN ENSEMBLE D'EMPRUNTS                                                          ||\n");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
        printf("||                                                           8. MENU PRINCIPAL                                                                            ||\n");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");

        printf("Votre choix : ");
        while(scanf("%d", &choix) != 1) {
            while(getchar() != '\n');
            printf("Votre choix : ");
        }

        switch(choix) {
            case 1:
                ajouterEmprunt();
                break;
            case 2:
                empruntsdunadherant();
                break;
            case 3:
                enregistrerRetour();
                break;
            case 4:
                empruntsencours();
                break;
            case 5:
                livresenretard();
                break;
            case 6:
                affempdateretour();
                break;
            case 7:
                supprimerEnsembleEmprunts();
                break;
            case 8:
                return;
            default:
                printf("\nChoix invalide!\n");
                getchar();
                getchar();
        }

    } while(choix != 8);
}

void ajouterEmprunt() {
    system("cls");
    int trouve;
    int choix1, i, j;
    int cin, numLivre, j1, m1, a1, j2, m2, a2;
    int dispo;
    int valideperiode, differencemois, differencejours;
    int nbEmpruntsAdherent;
    int jourAujourdhui, moisAujourdhui, anneeAujourdhui;
    obtenirDateActuelle(&jourAujourdhui, &moisAujourdhui, &anneeAujourdhui);

    do {
        system("cls");
        printf("||========================================================================================================================================================||\n");
        printf("||=======================================================     AJOUTER UN EMPRUNT     =====================================================================||\n");
        printf("||========================================================================================================================================================||\n\n");
        printf("Pour ajouter un emprunt, tapez 1, pour retourner tapez 0 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("Pour ajouter un emprunt, tapez 1, pour retourner tapez 0 : ");
        }
        Sleep(1000);
    } while (choix1 != 0 && choix1 != 1);

    if (choix1 == 0) {
        Sleep(2000);
        return;
    }

    if (nbEmprunts >= MAX_EMPRUNTS) {
        printf("\nLa base d'emprunts est pleine!\n");
        Sleep(2000);
        return;
    }

    livdispo();

    do {
        printf("Numero de CIN de l'emprunteur (8 chiffres) : ");
        while(scanf("%d", &cin) != 1) {
            while(getchar() != '\n');
            printf("Numero de CIN de l'emprunteur (8 chiffres) : ");
        }

        if (cin < 10000000 || cin > 99999999) {
            printf("Erreur : Le CIN doit contenir exactement 8 chiffres!\n");
            Sleep(1000);
        }
    } while (cin < 10000000 || cin > 99999999);

    nbEmpruntsAdherent = 0;
    for (i = 0; i < nbEmprunts; i++) {
        if (matriceEmprunts[i][0] == cin) {
            nbEmpruntsAdherent++;
        }
    }

    if (nbEmpruntsAdherent >= 7) {
        printf("\n>> Erreur : Cet adherent a deja atteint la limite de 7 emprunts!\n");
        printf(" Nombre d'emprunts en cours : %d/7\n", nbEmpruntsAdherent);
        printf(" Veuillez retourner un livre avant d'en emprunter un autre.\n");
        Sleep(3000);
        return;
    }

    printf(">>> Emprunts en cours pour cet adherent : %d/7\n\n", nbEmpruntsAdherent);

    do {
        do {
            printf("Numero du livre a emprunter : ");
            while(scanf("%d", &numLivre) != 1) {
                while(getchar() != '\n');
                printf("Numero du livre a emprunter : ");
            }

            trouve = 0;
            for (i = 0; i < nbLivres; i++) {
                if (numeros[i] == numLivre) {
                    trouve = 1;
                }
            }

            if (trouve == 0) {
                printf("Ce livre n'existe pas!\n");
                Sleep(1000);
            }
        } while (trouve == 0);

        dispo = 0;
        for (i = 0; i < nbLivres; i++) {
            if (numeros[i] == numLivre && nbexemplaires[i] > 0) {
                dispo = 1;
            }
        }

        if (dispo == 0) {
            printf("\nCe livre n'est pas disponible actuellement!\n");

            int jourMin = 32, moisMin = 13, anneeMin = 2100;
            int datetrouve = 0;

            for (i = 0; i < nbEmprunts; i++) {
                if (matriceEmprunts[i][1] == numLivre) {
                    datetrouve = 1;
                    int j = matriceEmprunts[i][5];
                    int m = matriceEmprunts[i][6];
                    int a = matriceEmprunts[i][7];

                    if (a < anneeMin) {
                        anneeMin = a;
                        moisMin = m;
                        jourMin = j;
                    } else if (a == anneeMin && m < moisMin) {
                        moisMin = m;
                        jourMin = j;
                    } else if (a == anneeMin && m == moisMin && j < jourMin) {
                        jourMin = j;
                    }
                }
            }

            if (datetrouve==1) {
                printf(">>> Ce livre sera disponible a partir du : %02d/%02d/%04d\n\n", jourMin, moisMin, anneeMin);
            }
            Sleep(2000);
        }
    } while (dispo == 0);

    valideperiode = 0;
    do {
        printf("\n--- Date d'emprunt ---\n");
        int validedate = 0;
        do {
            printf("Jour (JJ) : ");
            while(scanf("%d", &j1) != 1) {
                while(getchar() != '\n');
                printf("Jour (JJ) : ");
            }

            printf("Mois (MM) : ");
            while(scanf("%d", &m1) != 1) {
                while(getchar() != '\n');
                printf("Mois (MM) : ");
            }

            printf("Annee (AAAA) : ");
            while(scanf("%d", &a1) != 1) {
                while(getchar() != '\n');
                printf("Annee (AAAA) : ");
            }

            if (j1 < 1 || j1 > 31 || m1 < 1 || m1 > 12 || a1 < 2000) {
                printf("Date invalide! Reessayez.\n");
                Sleep(2000);
            }

            if (a1 < anneeAujourdhui) {
                printf("La date d'emprunt doit etre >= %d/%d/%d!\n", jourAujourdhui, moisAujourdhui, anneeAujourdhui);
                Sleep(2000);
            } else if (a1 == anneeAujourdhui && m1 < moisAujourdhui) {
                printf("La date d'emprunt doit etre >= %d/%d/%d!\n", jourAujourdhui, moisAujourdhui, anneeAujourdhui);
                Sleep(2000);
            } else if (a1 == anneeAujourdhui && m1 == moisAujourdhui && j1 < jourAujourdhui) {
                printf("La date d'emprunt doit etre >= %d/%d/%d!\n", jourAujourdhui, moisAujourdhui, anneeAujourdhui);
                Sleep(2000);
            }

            validedate = 1;
        } while (validedate == 0);

        printf("\n--- Date de retour prevue ---\n");
        int validedate1 = 0;
        do {
            printf("Jour (JJ) : ");
            while(scanf("%d", &j2) != 1) {
                while(getchar() != '\n');
                printf("Jour (JJ) : ");
            }

            printf("Mois (MM) : ");
            while(scanf("%d", &m2) != 1) {
                while(getchar() != '\n');
                printf("Mois (MM) : ");
            }

            printf("Annee (AAAA) : ");
            while(scanf("%d", &a2) != 1) {
                while(getchar() != '\n');
                printf("Annee (AAAA) : ");
            }

            if (j2 < 1 || j2 > 31 || m2 < 1 || m2 > 12 || a2 < 2000) {
                printf("Date invalide! Reessayez.\n");
                Sleep(2000);
                validedate1 = 0;
            }

            if (a2 > a1) {
                validedate1 = 1;
            } else if (a2 == a1 && m2 > m1) {
                validedate1 = 1;
            } else if (a2 == a1 && m2 == m1 && j2 > j1) {
                validedate1 = 1;
            } else {
                validedate1 = 0;
            }

            if (validedate1 == 0) {
                printf("La date de retour doit etre posterieure a la date d'emprunt!\n");
                Sleep(2000);
            }
        } while (validedate1 == 0);

        differencemois = (a2 - a1) * 12 + (m2 - m1);
        differencejours = j2 - j1;

        valideperiode = 0;
        if (differencemois == 0) {
            if (differencejours <= 31) {
                valideperiode = 1;
            }
        } else if (differencemois == 1) {
            if (differencejours <= 0) {
                valideperiode = 1;
            }
        }

        if (valideperiode == 0) {
            printf("Pour chaque livre, la periode d'emprunt autorisee ne peut pas depasser un mois!\n");
            Sleep(2000);
        }
    } while (valideperiode == 0);

    matriceEmprunts[nbEmprunts][0] = cin;
    matriceEmprunts[nbEmprunts][1] = numLivre;
    matriceEmprunts[nbEmprunts][2] = j1;
    matriceEmprunts[nbEmprunts][3] = m1;
    matriceEmprunts[nbEmprunts][4] = a1;
    matriceEmprunts[nbEmprunts][5] = j2;
    matriceEmprunts[nbEmprunts][6] = m2;
    matriceEmprunts[nbEmprunts][7] = a2;
    nbEmprunts++;

    for (i = 0; i < nbLivres; i++) {
        if (numeros[i] == numLivre) {
            nbexemplaires[i]--;
        }
    }

    printf("\n>>> Emprunt enregistre avec succes!\n");
    printf("retour au Gestion des emprunts...");
    Sleep(2000);
    system("cls");
    return;
}

void empruntsencours() {
    system("cls");
    int choix1, i, j;

    printf("||========================================================================================================================================================||\n");
    printf("||=================================================     LISTE DES EMPRUNTS EN COURS     ==================================================================||\n");
    printf("||========================================================================================================================================================||\n\n");

    if (nbEmprunts == 0) {
        printf("Aucun emprunt enregistre.\n");
        Sleep(2000);
        return;
    }

    printf("Nombre total d'emprunts : %d\n\n", nbEmprunts);

    printf("||========================================================================================================================================================||\n");
    printf("||  Index  |        N_CIN         |       N_livre        |      J1      |      M1      |      A1      |      J2      |      M2      |          A2         ||\n");
    printf("||========================================================================================================================================================||\n");

    for (i = 0; i < nbEmprunts; i++) {
        printf("|| %6d  | %18d   | %18d   | %10d    | %10d    | %10d    | %10d     | %10d   | %13d  ||\n",
               i + 1,
               matriceEmprunts[i][0],
               matriceEmprunts[i][1],
               matriceEmprunts[i][2],
               matriceEmprunts[i][3],
               matriceEmprunts[i][4],
               matriceEmprunts[i][5],
               matriceEmprunts[i][6],
               matriceEmprunts[i][7]);
    }
    printf("||========================================================================================================================================================||\n");

    do {
        printf("\nPour retourner a la gestion des emprunts, tapez 1 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("\nPour retourner a la gestion des emprunts, tapez 1 : ");
        }
    } while (choix1 != 1);

    printf("retour au Gestion des emprunts...");
    Sleep(2000);
    system("cls");
    return;
}

void empruntsdunadherant(){
    system("cls");
    int choix1, i;
    int cin, trouve = 0;

    do {
        system("cls");
        printf("||========================================================================================================================================================||\n");
        printf("||================================================     CONSULTER LES EMPRUNTS D'UN ADHERENT     ========================================================||\n");
        printf("||========================================================================================================================================================||\n\n");
        printf("Pour consulter les emprunts d'un adherent, tapez 1, pour retourner tapez 0 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("Pour consulter les emprunts d'un adherent, tapez 1, pour retourner tapez 0 : ");
        }
        Sleep(1000);
    } while (choix1 != 0 && choix1 != 1);

    if (choix1 == 0) {
        Sleep(2000);
        return;
    }

    if (nbEmprunts == 0) {
        printf("\nAucun emprunt enregistre dans le systeme!\n");
        Sleep(2000);
        return;
    }

    do {
        printf("Numero de CIN de l'adherent (8 chiffres) : ");
        while(scanf("%d", &cin) != 1) {
            while(getchar() != '\n');
            printf("Numero de CIN de l'adherent (8 chiffres) : ");
        }

        if (cin < 10000000 || cin > 99999999) {
            printf("Erreur : Le CIN doit contenir exactement 8 chiffres!\n");
            Sleep(1000);
        }
    } while (cin < 10000000 || cin > 99999999);

    system("cls");
    printf("||========================================================================================================================================================||\n");
    printf("||================================================     EMPRUNTS DE L'ADHERENT CIN: %d     =======================================================||\n", cin);
    printf("||========================================================================================================================================================||\n");

    trouve = 0;
    for (i = 0; i < nbEmprunts; i++) {
        if (matriceEmprunts[i][0] == cin) {
            trouve = 1;
        }
    }

    if (trouve == 0) {
        printf("\n||                                           Aucun emprunt trouve pour le CIN : %d                                                                  ||\n", cin);
        printf("||========================================================================================================================================================||\n");
    } else {
        printf("|| %-12s | %-25s | %-22s | %-22s ||\n", "N_Livre", "Titre du Livre", "Date Emprunt", "Date Retour Prevue");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");

        for (i = 0; i < nbEmprunts; i++) {
            if (matriceEmprunts[i][0] == cin) {
                int numLivre = matriceEmprunts[i][1];
                char titreLivre[MAX_TITRE] = "Livre inconnu";

                for (int j = 0; j < nbLivres; j++) {
                    if (numeros[j] == numLivre) {
                        strcpy(titreLivre, titres[j]);
                    }
                }

                printf("|| %-12d | %-25s | %02d/%02d/%04d            | %02d/%02d/%04d            ||\n",
                       numLivre,
                       titreLivre,
                       matriceEmprunts[i][2], matriceEmprunts[i][3], matriceEmprunts[i][4],
                       matriceEmprunts[i][5], matriceEmprunts[i][6], matriceEmprunts[i][7]);
            }
        }
        printf("||========================================================================================================================================================||\n");
    }

    do {
        printf("\nPour retourner au menu des emprunts, tapez 1 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("\nPour retourner au menu des emprunts, tapez 1 : ");
        }
    } while (choix1 != 1);
    printf("retour au Gestion des emprunts...");
    Sleep(2000);
    system("cls");
    return;
}

void affempdateretour() {
    system("cls");
    int choix1, i, j;
    int jour,mois,annee;
    int trouve = 0;
    int cin,numLivre;

    do {
        system("cls");
        printf("||========================================================================================================================================================||\n");
        printf("||==========================================     EMPRUNTS RELATIFS A UNE DATE DE RETOUR PREVUE     ====================================================||\n");
        printf("||========================================================================================================================================================||\n\n");
        printf("Pour afficher les emprunts par date de retour, tapez 1, pour retourner tapez 0 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("Pour afficher les emprunts par date de retour, tapez 1, pour retourner tapez 0 : ");
        }
        Sleep(1000);
    } while (choix1 != 0 && choix1 != 1);

    if (choix1 == 0) {
        Sleep(2000);
        return;
    }

    if (nbEmprunts == 0) {
        printf("\nAucun emprunt enregistre dans le systeme!\n");
        Sleep(2000);
        return;
    }

    printf("\n--- Entrez la date de retour prevue a rechercher ---\n");
    do {
        printf("Jour (JJ) : ");
        while(scanf("%d", &jour) != 1) {
            while(getchar() != '\n');
            printf("Jour (JJ) : ");
        }

        printf("Mois (MM) : ");
        while(scanf("%d", &mois) != 1) {
            while(getchar() != '\n');
            printf("Mois (MM) : ");
        }

        printf("Annee (AAAA) : ");
        while(scanf("%d", &annee) != 1) {
            while(getchar() != '\n');
            printf("Annee (AAAA) : ");
        }

        if (jour < 1 || jour > 31 || mois < 1 || mois > 12 || annee < 2000) {
            printf("Date invalide! Reessayez.\n");
            Sleep(2000);
        } else {
        }
    } while (jour < 1 || jour > 31 || mois < 1 || mois > 12 || annee < 2000);

    system("cls");
    printf("||========================================================================================================================================================||\n");
    printf("||========================================     EMPRUNTS AVEC DATE DE RETOUR : %02d/%02d/%04d     =======================================================||\n", jour,mois,annee);
    printf("||========================================================================================================================================================||\n");

    trouve = 0;
    for (i = 0; i < nbEmprunts; i++) {
        if (matriceEmprunts[i][5] == jour && matriceEmprunts[i][6] == mois && matriceEmprunts[i][7] == annee) {
            trouve = 1;
        }
    }

    if (trouve == 0) {
        printf("\n||                                  Aucun emprunt trouve avec la date de retour : %02d/%02d/%04d                                                     ||\n", jour, mois, annee);
        printf("||========================================================================================================================================================||\n");
    } else {
        printf("|| %-12s | %-12s | %-25s | %-22s | %-22s ||\n", "N_CIN", "N_Livre", "Titre du Livre", "Date Emprunt", "Date Retour Prevue");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");

        for (i = 0; i < nbEmprunts; i++) {
            if (matriceEmprunts[i][5] == jour && matriceEmprunts[i][6] == mois && matriceEmprunts[i][7] == annee) {

                cin = matriceEmprunts[i][0];
                numLivre = matriceEmprunts[i][1];
                char titreLivre[MAX_TITRE] = "Livre inconnu";

                for (j = 0; j < nbLivres; j++) {
                    if (numeros[j] == numLivre) {
                        strcpy(titreLivre, titres[j]);
                    }
                }

                printf("|| %-12d | %-12d | %-25s | %02d/%02d/%04d            | %02d/%02d/%04d            ||\n",
                       cin,
                       numLivre,
                       titreLivre,
                       matriceEmprunts[i][2], matriceEmprunts[i][3], matriceEmprunts[i][4],
                       matriceEmprunts[i][5], matriceEmprunts[i][6], matriceEmprunts[i][7]);
            }
        }
        printf("||========================================================================================================================================================||\n");
    }

    do {
        printf("\nPour retourner au menu des emprunts, tapez 1 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("\nPour retourner au menu des emprunts, tapez 1 : ");
        }
    } while (choix1 != 1);
    printf("retour au Gestion des emprunts...");
    Sleep(2000);
    system("cls");
    return;
}

void enregistrerRetour() {
    system("cls");
    int choix1, i, j;
    int cin, numLivre;
    int trouve = 0;

    do {
        system("cls");
        printf("||========================================================================================================================================================||\n");
        printf("||===================================================     ENREGISTRER LE RETOUR D'UN LIVRE     =========================================================||\n");
        printf("||========================================================================================================================================================||\n\n");
        printf("Pour enregistrer un retour, tapez 1, pour retourner tapez 0 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("Pour enregistrer un retour, tapez 1, pour retourner tapez 0 : ");
        }
        Sleep(1000);
    } while (choix1 != 0 && choix1 != 1);

    if (choix1 == 0) {
        Sleep(2000);
        return;
    }

    if (nbEmprunts == 0) {
        printf("\nAucun emprunt enregistre dans le systeme!\n");
        Sleep(2000);
        return;
    }

    do {
        printf("Numero de CIN de l'emprunteur (8 chiffres) : ");
        while(scanf("%d", &cin) != 1) {
            while(getchar() != '\n');
            printf("Numero de CIN de l'emprunteur (8 chiffres) : ");
        }

        if (cin < 10000000 || cin > 99999999) {
            printf("Erreur : Le CIN doit contenir exactement 8 chiffres!\n");
            Sleep(1000);
        }
    } while (cin < 10000000 || cin > 99999999);

    printf("Numero du livre a retourner : ");
    while(scanf("%d", &numLivre) != 1) {
        while(getchar() != '\n');
        printf("Numero du livre a retourner : ");
    }

    trouve = 0;
    for (i = 0; i < nbEmprunts; i++) {
        if (matriceEmprunts[i][0] == cin && matriceEmprunts[i][1] == numLivre) {
            trouve = 1;

            printf("\n||========================================================================================================================================================||\n");
            printf("||                                                         EMPRUNT TROUVE                                                                                 ||\n");
            printf("||========================================================================================================================================================||\n");
            printf("|| CIN Emprunteur       : %-12d                                                                                                                 ||\n", matriceEmprunts[i][0]);
            printf("|| Numero du Livre      : %-12d                                                                                                                 ||\n", matriceEmprunts[i][1]);
            printf("|| Date d'emprunt       : %02d/%02d/%04d                                                                                                                   ||\n", matriceEmprunts[i][2], matriceEmprunts[i][3], matriceEmprunts[i][4]);
            printf("|| Date de retour prevue: %02d/%02d/%04d                                                                                                                   ||\n",matriceEmprunts[i][5], matriceEmprunts[i][6], matriceEmprunts[i][7]);
            printf("||========================================================================================================================================================||\n");

            for (j = i; j < nbEmprunts - 1; j++) {
                matriceEmprunts[j][0] = matriceEmprunts[j + 1][0];
                matriceEmprunts[j][1] = matriceEmprunts[j + 1][1];
                matriceEmprunts[j][2] = matriceEmprunts[j + 1][2];
                matriceEmprunts[j][3] = matriceEmprunts[j + 1][3];
                matriceEmprunts[j][4] = matriceEmprunts[j + 1][4];
                matriceEmprunts[j][5] = matriceEmprunts[j + 1][5];
                matriceEmprunts[j][6] = matriceEmprunts[j + 1][6];
                matriceEmprunts[j][7] = matriceEmprunts[j + 1][7];
            }
            nbEmprunts--;

            for (j = 0; j < nbLivres; j++) {
                if (numeros[j] == numLivre) {
                    nbexemplaires[j]++;
                }
            }

            printf("\n>>> Retour enregistre avec succes!\n");
            printf(">>> Le livre a ete remis en stock.\n");
        }
    }

    if (trouve == 0) {
        printf("\n>>> Erreur : Aucun emprunt trouve pour ce CIN et ce livre!\n");
        printf(">>> Verifiez les informations saisies.\n");
    }

    printf("retour au Gestion des emprunts...");
    Sleep(2000);
    system("cls");
    return;
}

void livresenretard() {
    system("cls");
    int choix1, i, j;
    int jourAujourdhui, moisAujourdhui, anneeAujourdhui;
    int trouve ;
    int retard;
    int cin , numLivre ;
    char titreLivre[MAX_TITRE];

    do {
        system("cls");
        printf("||========================================================================================================================================================||\n");
        printf("||===================================================     AFFICHER LES LIVRES EN RETARD     =============================================================||\n");
        printf("||========================================================================================================================================================||\n\n");
        printf("Pour afficher les livres en retard, tapez 1, pour retourner tapez 0 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("Pour afficher les livres en retard, tapez 1, pour retourner tapez 0 : ");
        }
        Sleep(1000);
    } while (choix1 != 0 && choix1 != 1);

    if (choix1 == 0) {
        Sleep(2000);
        return;
    }

    if (nbEmprunts == 0) {
        printf("\nAucun emprunt enregistre dans le systeme!\n");
        Sleep(2000);
        return;
    }

    printf("\n--- Entrez la date d'aujourd'hui (JJ/MM/AAAA) ---\n");
    do {
        printf("Jour (JJ) : ");
        while(scanf("%d", &jourAujourdhui) != 1) {
            while(getchar() != '\n');
            printf("Jour (JJ) : ");
        }

        printf("Mois (MM) : ");
        while(scanf("%d", &moisAujourdhui) != 1) {
            while(getchar() != '\n');
            printf("Mois (MM) : ");
        }

        printf("Annee (AAAA) : ");
        while(scanf("%d", &anneeAujourdhui) != 1) {
            while(getchar() != '\n');
            printf("Annee (AAAA) : ");
        }

        if (jourAujourdhui < 1 || jourAujourdhui > 31 || moisAujourdhui < 1 || moisAujourdhui > 12 || anneeAujourdhui < 2000) {
            printf("Date invalide! Reessayez.\n");
            Sleep(2000);
        }
    } while (1);

    system("cls");
    printf("||========================================================================================================================================================||\n");
    printf("||===============================================     LIVRES EN RETARD AU %02d/%02d/%04d     ============================================================||\n", jourAujourdhui, moisAujourdhui, anneeAujourdhui);
    printf("||========================================================================================================================================================||\n");

    trouve = 0;
    for (i = 0; i < nbEmprunts; i++) {
        retard = 0;

        if (anneeAujourdhui > matriceEmprunts[i][7]) {
            retard = 1;
        } else if (anneeAujourdhui == matriceEmprunts[i][7]) {
            if (moisAujourdhui > matriceEmprunts[i][6]) {
                retard = 1;
            } else if (moisAujourdhui == matriceEmprunts[i][6]) {
                if (jourAujourdhui > matriceEmprunts[i][5]) {
                    retard = 1;
                }
            }
        }
        trouve = 0 ;
        if (retard == 1) {
            trouve = 1;
        }
    }

    if (trouve == 0) {
        printf("\n||                                              Aucun livre en retard actuellement!                                                                   ||\n");
        printf("||========================================================================================================================================================||\n");
    } else {
        printf("|| %-12s | %-12s | %-25s | %-22s | %-15s ||\n", "N_CIN", "N_Livre", "Titre du Livre", "Date Retour Prevue", "Jours de Retard");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");

        for (i = 0; i < nbEmprunts; i++) {
            retard = 0;

            if (anneeAujourdhui > matriceEmprunts[i][7]) {
                retard = 1;
            } else if (anneeAujourdhui == matriceEmprunts[i][7]) {
                if (moisAujourdhui > matriceEmprunts[i][6]) {
                    retard = 1;
                } else if (moisAujourdhui == matriceEmprunts[i][6]) {
                    if (jourAujourdhui > matriceEmprunts[i][5]) {
                        retard = 1;
                    }
                }
            }

            if (retard == 1) {
                int cin = matriceEmprunts[i][0];
                int numLivre = matriceEmprunts[i][1];
                char titreLivre[MAX_TITRE] = "Livre inconnu";

                for (j = 0; j < nbLivres; j++) {
                    if (numeros[j] == numLivre) {
                        strcpy(titreLivre, titres[j]);
                    }
                }

                int joursRetard = 0;
                if (anneeAujourdhui == matriceEmprunts[i][7] && moisAujourdhui == matriceEmprunts[i][6]) {
                    joursRetard = jourAujourdhui - matriceEmprunts[i][5];
                }
                else if (anneeAujourdhui == matriceEmprunts[i][7]) {
                    joursRetard = (moisAujourdhui - matriceEmprunts[i][6]) * 30 + (jourAujourdhui - matriceEmprunts[i][5]);
                }
                else {
                    joursRetard = (anneeAujourdhui - matriceEmprunts[i][7]) * 365;
                }

                printf("|| %-12d | %-12d | %-25s | %02d/%02d/%04d            | %-15d ||\n",
                       cin,
                       numLivre,
                       titreLivre,
                       matriceEmprunts[i][5], matriceEmprunts[i][6], matriceEmprunts[i][7],
                       joursRetard);
            }
        }
        printf("||========================================================================================================================================================||\n");
    }

    do {
        printf("\nPour retourner au menu des emprunts, tapez 1 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("\nPour retourner au menu des emprunts, tapez 1 : ");
        }
    } while (choix1 != 1);
    printf("retour au Gestion des emprunts...");
    Sleep(2000);
    system("cls");
    return;
}

void supprimerEnsembleEmprunts() {
    system("cls");
    int choix1, i, j;
    int jour_debut, mois_debut, annee_debut;
    int jour_fin, mois_fin, annee_fin;
    int empruntsupprime = 0;

    do {
        system("cls");
        printf("||========================================================================================================================================================||\n");
        printf("||===============================================     SUPPRIMER UN ENSEMBLE D'EMPRUNTS     ===============================================================||\n");
        printf("||========================================================================================================================================================||\n\n");
        printf("Pour supprimer un ensemble d'emprunts, tapez 1, pour retourner tapez 0 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("Pour supprimer un ensemble d'emprunts, tapez 1, pour retourner tapez 0 : ");
        }
        Sleep(1000);
    } while (choix1 != 0 && choix1 != 1);

    if (choix1 == 0) {
        Sleep(2000);
        return;
    }

    if (nbEmprunts == 0) {
        printf("\nAucun emprunt enregistre dans le systeme!\n");
        Sleep(2000);
        return;
    }

    system("cls");
    printf("||========================================================================================================================================================||\n");
    printf("||===============================================     EMPRUNTS AVANT SUPPRESSION     =====================================================================||\n");
    printf("||========================================================================================================================================================||\n");
    printf("|| %-12s | %-12s | %-15s | %-15s ||\n", "N_CIN", "N_Livre", "Date Emprunt", "Date Retour");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");

    for (i = 0; i < nbEmprunts; i++) {
        printf("|| %-12d | %-12d | %02d/%02d/%04d      | %02d/%02d/%04d      ||\n",
               matriceEmprunts[i][0],
               matriceEmprunts[i][1],
               matriceEmprunts[i][2], matriceEmprunts[i][3], matriceEmprunts[i][4],
               matriceEmprunts[i][5], matriceEmprunts[i][6], matriceEmprunts[i][7]);
    }
    printf("||========================================================================================================================================================||\n\n");

    printf("\n--- Date d'emprunt (debut de la periode) ---\n");
    do {
        printf("Jour (JJ) : ");
        while(scanf("%d", &jour_debut) != 1) {
            while(getchar() != '\n');
            printf("Jour (JJ) : ");
        }

        printf("Mois (MM) : ");
        while(scanf("%d", &mois_debut) != 1) {
            while(getchar() != '\n');
            printf("Mois (MM) : ");
        }

        printf("Annee (AAAA) : ");
        while(scanf("%d", &annee_debut) != 1) {
            while(getchar() != '\n');
            printf("Annee (AAAA) : ");
        }

        if (jour_debut < 1 || jour_debut > 31 || mois_debut < 1 || mois_debut > 12 || annee_debut < 2000) {
            printf("Date invalide! Reessayez.\n");
            Sleep(2000);
        }
    } while (jour_debut < 1 || jour_debut > 31 || mois_debut < 1 || mois_debut > 12 || annee_debut < 2000);

    printf("\n--- Date de retour prevue (fin de la periode) ---\n");
    int validedate1 = 0;
    do {
        printf("Jour (JJ) : ");
        while(scanf("%d", &jour_fin) != 1) {
            while(getchar() != '\n');
            printf("Jour (JJ) : ");
        }

        printf("Mois (MM) : ");
        while(scanf("%d", &mois_fin) != 1) {
            while(getchar() != '\n');
            printf("Mois (MM) : ");
        }

        printf("Annee (AAAA) : ");
        while(scanf("%d", &annee_fin) != 1) {
            while(getchar() != '\n');
            printf("Annee (AAAA) : ");
        }

        if (jour_fin < 1 || jour_fin > 31 || mois_fin < 1 || mois_fin > 12 || annee_fin < 2000) {
            printf("Date invalide! Reessayez.\n");
            Sleep(2000);
        }

        if (annee_fin > annee_debut) {
            validedate1 = 1;
        } else if (annee_fin == annee_debut && mois_fin > mois_debut) {
            validedate1 = 1;
        } else if (annee_fin == annee_debut && mois_fin == mois_debut && jour_fin >= jour_debut) {
            validedate1 = 1;
        } else {
            validedate1 = 0;
        }

        if (validedate1 == 0) {
            printf("La date de retour doit etre >= date d'emprunt!\n");
            Sleep(2000);
        }
    } while (validedate1 == 0);

    empruntsupprime = 0;

    for (i = 0; i < nbEmprunts; i++) {
        int jEmprunt = matriceEmprunts[i][2];
        int mEmprunt = matriceEmprunts[i][3];
        int aEmprunt = matriceEmprunts[i][4];
        int jRetour = matriceEmprunts[i][5];
        int mRetour = matriceEmprunts[i][6];
        int aRetour = matriceEmprunts[i][7];

        int dansPeriode = 0;

        int empruntApresDebut = 0;
        if (aEmprunt > annee_debut) {
            empruntApresDebut = 1;
        } else if (aEmprunt == annee_debut && mEmprunt > mois_debut) {
            empruntApresDebut = 1;
        } else if (aEmprunt == annee_debut && mEmprunt == mois_debut && jEmprunt >= jour_debut) {
            empruntApresDebut = 1;
        }

        int retourAvantFin = 0;
        if (aRetour < annee_fin) {
            retourAvantFin = 1;
        } else if (aRetour == annee_fin && mRetour < mois_fin) {
            retourAvantFin = 1;
        } else if (aRetour == annee_fin && mRetour == mois_fin && jRetour <= jour_fin) {
            retourAvantFin = 1;
        }

        if (empruntApresDebut && retourAvantFin) {
            dansPeriode = 1;
        }

        if (dansPeriode == 1) {
            for (j = i; j < nbEmprunts - 1; j++) {
                matriceEmprunts[j][0] = matriceEmprunts[j + 1][0];
                matriceEmprunts[j][1] = matriceEmprunts[j + 1][1];
                matriceEmprunts[j][2] = matriceEmprunts[j + 1][2];
                matriceEmprunts[j][3] = matriceEmprunts[j + 1][3];
                matriceEmprunts[j][4] = matriceEmprunts[j + 1][4];
                matriceEmprunts[j][5] = matriceEmprunts[j + 1][5];
                matriceEmprunts[j][6] = matriceEmprunts[j + 1][6];
                matriceEmprunts[j][7] = matriceEmprunts[j + 1][7];
            }
            nbEmprunts--;
            empruntsupprime++;
            i--;
        }
    }

    printf("\n||========================================================================================================================================================||\n");
    if (empruntsupprime > 0) {
        printf("||                    >>> %d emprunt(s) supprime(s) avec succes pour la periode du %02d/%02d/%04d au %02d/%02d/%04d <<<                                ||\n",empruntsupprime, jour_debut, mois_debut, annee_debut, jour_fin, mois_fin, annee_fin);
    } else {
        printf("||                                    >>> Aucun emprunt trouve dans cette periode! <<<                                                                ||\n");
    }
    printf("||========================================================================================================================================================||\n\n");

    if (nbEmprunts > 0) {
        printf("||========================================================================================================================================================||\n");
        printf("||===============================================     EMPRUNTS APRES SUPPRESSION     ======================================================================||\n");
        printf("||========================================================================================================================================================||\n");
        printf("|| %-12s | %-12s | %-15s | %-15s ||\n", "N_CIN", "N_Livre", "Date Emprunt", "Date Retour");
        printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");

        for (i = 0; i < nbEmprunts; i++) {
            printf("|| %-12d | %-12d | %02d/%02d/%04d      | %02d/%02d/%04d      ||\n",matriceEmprunts[i][0],matriceEmprunts[i][1],matriceEmprunts[i][2], matriceEmprunts[i][3], matriceEmprunts[i][4],matriceEmprunts[i][5], matriceEmprunts[i][6], matriceEmprunts[i][7]);
        }
        printf("||========================================================================================================================================================||\n");
    } else {
        printf("\n||========================================================================================================================================================||\n");
        printf("||                                              >>> Plus aucun emprunt dans le systeme! <<<                                                            ||\n");
        printf("||========================================================================================================================================================||\n");
    }

    do {
        printf("\nPour retourner au menu gestion des emprunts, tapez 1 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("\nPour retourner au menu gestion des emprunts, tapez 1 : ");
        }
    } while (choix1 != 1);
    printf("retour au Gestion des emprunts...");
    Sleep(2000);
    system("cls");
    return;
}

void menustatistique() {
    system("cls");
    int choix;
    do{
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
    printf("||----------------------------------------------------                 STATISTIQUES                       ------------------------------------------------||\n");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
    printf("||----------------------------------------------------               Veuillez choisir               ------------------------------------------------------||\n");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
    printf("||                                             1. AFFICHER LE NOMBRE TOTAL DE LIVRES, D'ADHERENTS ET D'EMPRUNT                                            ||\n");
    printf("||                                             2. AFFICHER LE(S) LIVRE(S) LE(S) PLUS EMPRUNTE(S)                                                          ||\n");
    printf("||                                             3. AFFICHER LE(S) LIVRE(S) JAMAIS EMPRUNTE(S))                                                             ||\n");
    printf("||                                             4. AFFICHER LE(S) LIVRE(S) LE(S) PLUS EMPRUNTE(S) DANS UNE PERIODE DONNEE                                  ||\n");
    printf("||                                             5. AFFICHER LE(S) EMPRUNTEUR(S) LE(S) PLUS FREQUENT(S)                                                     ||\n");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
    printf("||                                                           6. MENU PRINCIPAL                                                                            ||\n");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
     printf("Votre choix : ");
        while(scanf("%d", &choix) != 1) {
            while(getchar() != '\n');
            printf("Votre choix : ");
        }

        switch(choix) {

            case 1:
                compte();
                break;
            case 2:
                livresplusempruntes();
                break;
            case 3:
                livresjamaisempruntes();
                break;
            case 4:
                livresplusempruntesperiode();
                break;
            case 5:
                emprunteursplusfrequent();
                break;
            case 6:
                return;
            default:
                printf("\nChoix invalide!\n");
                getchar();
                getchar();
        }

    } while(choix != 6);
}

void compte() {
    system("cls");
    int choix1, i;
    int nbAdherents1 = 0;
    int cin1[MAX_EMPRUNTS];
    int totalExemplaires = 0;

    do {
        system("cls");
        printf("||========================================================================================================================================================||\n");
        printf("||=====================================     LE NOMBRE TOTAL DE LIVRES, D ADHERENTS ET D EMPRUNTS     =====================================================||\n");
        printf("||========================================================================================================================================================||\n\n");
        printf("Pour afficher les comptes, tapez 1, pour retourner tapez 0 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("Pour afficher les comptes, tapez 1, pour retourner tapez 0 : ");
        }
        Sleep(1000);
    } while (choix1 != 0 && choix1 != 1);

    if (choix1 == 0) {
        Sleep(2000);
        return;
    }

    for (i = 0; i < nbLivres; i++) {
        totalExemplaires += nbexemplaires[i];
    }

    for (i = 0; i < nbEmprunts; i++) {
        int cin = matriceEmprunts[i][0];
        int existe = 0;
        for (int j = 0; j < nbAdherents1; j++) {
            if (cin1[j] == cin) {
                existe = 1;
            }
        }
        if (existe == 0) {
            cin1[nbAdherents1] = cin;
            nbAdherents1++;
        }
    }

    system("cls");
    printf("||========================================================================================================================================================||\n");
    printf("||=====================================     LE NOMBRE TOTAL DE LIVRES, D ADHERENTS ET D EMPRUNTS     =====================================================||\n");
    printf("||========================================================================================================================================================||\n");
    printf("||                                                                                                                                                        ||\n");
    printf("||   Nombre total de titres de livres          : %-15d                                                                                          ||\n", nbLivres);
    printf("||   Nombre total d'exemplaires disponibles    : %-15d                                                                                          ||\n", totalExemplaires);
    printf("||   Nombre total d'adherents                  : %-15d                                                                                          ||\n", nbAdherents1);
    printf("||   Nombre total d'emprunts en cours          : %-15d                                                                                          ||\n", nbEmprunts);
    printf("||                                                                                                                                                        ||\n");
    printf("||========================================================================================================================================================||\n");

    do {
        printf("\nPour retourner au menu statistiques, tapez 1 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("\nPour retourner au menu statistiques, tapez 1 : ");
        }
    } while (choix1 != 1);
    printf("retour au menu statistiques...");
    Sleep(2000);
    system("cls");
    return;
}

void livresplusempruntes() {
    system("cls");
    int choix1, i, j;
    int nbEmpruntsPlivre[MAX_LIVRES] = {0};
    int maxEmprunts = 0;

    do {
        system("cls");
        printf("||========================================================================================================================================================||\n");
        printf("||===============================================     LIVRE(S) LE(S) PLUS EMPRUNTE(S)     ================================================================||\n");
        printf("||========================================================================================================================================================||\n\n");
        printf("Pour afficher les livres les plus empruntes, tapez 1, pour retourner tapez 0 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("Pour afficher les livres les plus empruntes, tapez 1, pour retourner tapez 0 : ");
        }
        Sleep(1000);
    } while (choix1 != 0 && choix1 != 1);

    if (choix1 == 0) {
        Sleep(2000);
        return;
    }

    if (nbEmprunts == 0) {
        printf("\nAucun emprunt enregistre dans le systeme!\n");
        Sleep(2000);
        return;
    }

    for (i = 0; i < nbEmprunts; i++) {
        int numLivre = matriceEmprunts[i][1];
        for (j = 0; j < nbLivres; j++) {
            if (numeros[j] == numLivre) {
                nbEmpruntsPlivre[j]++;
                if (nbEmpruntsPlivre[j] > maxEmprunts) {
                    maxEmprunts = nbEmpruntsPlivre[j];
                }
            }
        }
    }

    if (maxEmprunts == 0) {
        printf("\nAucun livre n'a ete emprunte!\n");
        Sleep(2000);
        menustatistique();
        return;
    }

    system("cls");
    printf("||========================================================================================================================================================||\n");
    printf("||===============================================     LIVRE(S) LE(S) PLUS EMPRUNTE(S)     ================================================================||\n");
    printf("||========================================================================================================================================================||\n");
    printf("|| Nombre maximum d'emprunts : %02d                                                                                                                         ||\n", maxEmprunts);
    printf("||========================================================================================================================================================||\n");
    printf("|| %-15s | \t\t\t\t %-80s \t | %-14s ||\n", "Numero", "Titre du Livre", "Nb Emprunts");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");

    for (i = 0; i < nbLivres; i++) {
        if (nbEmpruntsPlivre[i] == maxEmprunts) {
            printf("|| %-15d | \t\t\t\t %-80s \t | %-14d ||\n", numeros[i], titres[i], nbEmpruntsPlivre[i]);
        }
    }
    printf("||========================================================================================================================================================||\n");

    do {
        printf("\nPour retourner au menu statistiques, tapez 1 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("\nPour retourner au menu statistiques, tapez 1 : ");
        }
    } while (choix1 != 1);
    printf("retour au menu statistiques...");
    Sleep(2000);
    system("cls");
    return;
}

void livresjamaisempruntes() {
    system("cls");
    int choix1, i, j;
    int dejaEmprunte;
    int premierLivreTrouve = 0;

    do {
        system("cls");
        printf("||========================================================================================================================================================||\n");
        printf("||==========================================     LIVRE(S) JAMAIS EMPRUNTE(S)     ====================================================================||\n");
        printf("||========================================================================================================================================================||\n\n");
        printf("Pour afficher les livres jamais empruntes, tapez 1, pour retourner tapez 0 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("Pour afficher les livres jamais empruntes, tapez 1, pour retourner tapez 0 : ");
        }
        Sleep(1000);
    } while (choix1 != 0 && choix1 != 1);

    if (choix1 == 0) {
        Sleep(2000);
        return;
    }

    system("cls");
    printf("||========================================================================================================================================================||\n");
    printf("||==========================================     LIVRE(S) JAMAIS EMPRUNTE(S)     =========================================================================||\n");
    printf("||========================================================================================================================================================||\n");

    for (i = 0; i < nbLivres; i++) {
        dejaEmprunte = 0;

        for (j = 0; j < nbEmprunts; j++) {
            if (matriceEmprunts[j][1] == numeros[i]) {
                dejaEmprunte = 1;
            }
        }

        if (dejaEmprunte == 0 && premierLivreTrouve == 0) {
            printf("|| %-15s | \t\t\t\t %-80s \t | %-14s ||\n", "N_Livre", "Titre du Livre", "Exemplaires");
            printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
            premierLivreTrouve = 1;
        }

        if (dejaEmprunte == 0) {
            printf("|| %-15d | \t\t\t\t %-80s \t | %-14d ||\n", numeros[i], titres[i], nbexemplaires[i]);
        }
    }

    if (premierLivreTrouve == 0) {
        printf("\n||                                              Tous les livres ont ete empruntes au moins une fois!                                                 ||\n");
    }
    printf("||========================================================================================================================================================||\n");

    do {
        printf("\nPour retourner au menu statistiques, tapez 1 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("\nPour retourner au menu statistiques, tapez 1 : ");
        }
        printf("Retour au menu statistique...");
        Sleep(2000);
    } while (choix1 != 1);
    printf("retour au menu statistiques...");
    Sleep(2000);
    system("cls");
    return;
}

void livresplusempruntesperiode() {
    system("cls");
    int choix1, i, j;
    int jour_debut, mois_debut, annee_debut;
    int jour_fin, mois_fin, annee_fin;
    int maxEmprunts = 0;

    do {
        system("cls");
        printf("||========================================================================================================================================================||\n");
        printf("||=====================================     LIVRE(S) LE(S) PLUS EMPRUNTE(S) DANS UNE PERIODE DONNEE     ==================================================||\n");
        printf("||========================================================================================================================================================||\n\n");
        printf("Pour afficher les livres les plus empruntes par periode, tapez 1, pour retourner tapez 0 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("Pour afficher les livres les plus empruntes par periode, tapez 1, pour retourner tapez 0 : ");
        }
        Sleep(1000);
    } while (choix1 != 0 && choix1 != 1);

    if (choix1 == 0) {
        Sleep(2000);
        return;
    }

    if (nbEmprunts == 0) {
        printf("\nAucun emprunt enregistre dans le systeme!\n");
        Sleep(2000);
        return;
    }

    printf("\n--- Date de debut de la periode ---\n");
    int validedate = 0;
    do {
        printf("Jour (JJ) : ");
        while(scanf("%d", &jour_debut) != 1) {
            while(getchar() != '\n');
            printf("Jour (JJ) : ");
        }

        printf("Mois (MM) : ");
        while(scanf("%d", &mois_debut) != 1) {
            while(getchar() != '\n');
            printf("Mois (MM) : ");
        }

        printf("Annee (AAAA) : ");
        while(scanf("%d", &annee_debut) != 1) {
            while(getchar() != '\n');
            printf("Annee (AAAA) : ");
        }

        if (jour_debut < 1 || jour_debut > 31 || mois_debut < 1 || mois_debut > 12 || annee_debut < 2000) {
            printf("Date invalide! Reessayez.\n");
            Sleep(2000);
            validedate = 0;
        }

        if (mois_debut == 2) {
            if ((annee_debut % 4 == 0 && annee_debut % 100 != 0) || (annee_debut % 400 == 0)) {
                if (jour_debut > 29) {
                    printf("Fevrier a maximum 29 jours (annee bissextile)! Reessayez.\n");
                    Sleep(2000);
                    validedate = 0;
                }
            } else {
                if (jour_debut > 28) {
                    printf("Fevrier a maximum 28 jours! Reessayez.\n");
                    Sleep(2000);
                    validedate = 0;
                }
            }
        }

        if ((mois_debut == 4 || mois_debut == 6 || mois_debut == 9 || mois_debut == 11) && jour_debut > 30) {
            printf("Le mois %d a maximum 30 jours! Reessayez.\n", mois_debut);
            Sleep(2000);
            validedate = 0;
        }

        validedate = 1;

    } while (validedate == 0);

    printf("\n--- Date de fin de la periode ---\n");
    int validedate1 = 0;

    do {
        printf("Jour (JJ) : ");
        while(scanf("%d", &jour_fin) != 1) {
            while(getchar() != '\n');
            printf("Jour (JJ) : ");
        }

        printf("Mois (MM) : ");
        while(scanf("%d", &mois_fin) != 1) {
            while(getchar() != '\n');
            printf("Mois (MM) : ");
        }

        printf("Annee (AAAA) : ");
        while(scanf("%d", &annee_fin) != 1) {
            while(getchar() != '\n');
            printf("Annee (AAAA) : ");
        }

        if (jour_fin < 1 || jour_fin > 31 || mois_fin < 1 || mois_fin > 12 || annee_fin < 2000) {
            printf("Date invalide! Reessayez.\n");
            Sleep(2000);
            validedate1 = 0;
        }

        if (mois_fin == 2) {
            if ((annee_fin % 4 == 0 && annee_fin % 100 != 0) || (annee_fin % 400 == 0)) {
                if (jour_fin > 29) {
                    printf("Fevrier a maximum 29 jours (annee bissextile)! Reessayez.\n");
                    Sleep(2000);
                    validedate1 = 0;
                }
            } else {
                if (jour_fin > 28) {
                    printf("Fevrier a maximum 28 jours! Reessayez.\n");
                    Sleep(2000);
                    validedate1 = 0;
                }
            }
        }

        if ((mois_fin == 4 || mois_fin == 6 || mois_fin == 9 || mois_fin == 11) && jour_fin > 30) {
            printf("Le mois %d a maximum 30 jours! Reessayez.\n", mois_fin);
            Sleep(2000);
            validedate1 = 0;
        }

        if (annee_fin > annee_debut) {
            validedate1 = 1;
        } else if (annee_fin == annee_debut && mois_fin > mois_debut) {
            validedate1 = 1;
        } else if (annee_fin == annee_debut && mois_fin == mois_debut && jour_fin >= jour_debut) {
            validedate1 = 1;
        } else {
            validedate1 = 0;
            printf("La date de fin doit etre >= date de debut!\n");
            Sleep(2000);
        }

    } while (validedate1 == 0);

    int nblivresemprutesperiode[MAX_LIVRES] = {0};

    int date_debut_comp = annee_debut * 10000 + mois_debut * 100 + jour_debut;
    int date_fin_comp = annee_fin * 10000 + mois_fin * 100 + jour_fin;

    for (i = 0; i < nbEmprunts; i++) {
        int numLivre = matriceEmprunts[i][1];
        int dateempruntjour = matriceEmprunts[i][2];
        int dateempruntmois = matriceEmprunts[i][3];
        int dateempruntannee = matriceEmprunts[i][4];

        int date_emprunt_comp = dateempruntannee * 10000 + dateempruntmois * 100 + dateempruntjour;

        if (date_emprunt_comp >= date_debut_comp && date_emprunt_comp <= date_fin_comp) {
            for (j = 0; j < nbLivres; j++) {
                if (numeros[j] == numLivre) {
                    nblivresemprutesperiode[j]++;
                    if (nblivresemprutesperiode[j] > maxEmprunts) {
                        maxEmprunts = nblivresemprutesperiode[j];
                    }
                }
            }
        }
    }
        int compteLivresMax = 0;
        for (int i = 0; i < nbLivres; i++) {
        if (nblivresemprutesperiode[i] == maxEmprunts) {
            compteLivresMax++;
        }
    }


    if (maxEmprunts == 0) {
        printf("\nAucun livre n'a ete emprunte dans cette periode !\n");
        Sleep(2000);
        return;
    }

    system("cls");
    printf("||========================================================================================================================================================||\n");
    printf("||=========================================     LIVRE(S) LE(S) PLUS EMPRUNTE(S) DANS UNE PERIODE DONNEE     ==============================================||\n");
    printf("||========================================================================================================================================================||\n");
    printf("|| Periode : %02d/%02d/%04d  --  %02d/%02d/%04d                                                                                                                   ||\n",jour_debut, mois_debut, annee_debut, jour_fin, mois_fin, annee_fin);
    if (compteLivresMax==1){
    printf("|| le livre le plus emprunte a ete emprunte %2d fois                                                                                                        ||\n", maxEmprunts);}
    else{
        printf("|| les livres les plus empruntes ont ete empruntes %2d fois                                                                                    ||\n", maxEmprunts);}

    printf("||========================================================================================================================================================||\n");
    printf("|| %-15s | \t\t\t\t %-80s \t| %-15s ||\n", "Numero", "Titre du Livre", "Nb Emprunts");
    printf("||========================================================================================================================================================||\n");

    for (i = 0; i < nbLivres; i++) {
        if (nblivresemprutesperiode[i] == maxEmprunts) {
            printf("|| %-15d | \t\t\t\t %-80s \t| %-15d ||\n", numeros[i], titres[i], nblivresemprutesperiode[i]);
        }
    }
    printf("||========================================================================================================================================================||\n");

    do {
        printf("\nPour retourner au menu statistiques, tapez 1 : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("\nPour retourner au menu statistiques, tapez 1 : ");
        }
        Sleep(1000);
    } while (choix1 != 1);
    printf("Retour au menu Statistique...");
    Sleep(2000);
    return;
}

void emprunteursplusfrequent() {
    system("cls");
    int choix1;
    int empruntsParCIN[MAX_EMPRUNTS] = {0};
    int CINu[MAX_EMPRUNTS] = {0};
    int nbEmprunteurs = 0;
    int maxEmprunts = 0;
    int cin ;
    int trouve;


    do {
        printf("||========================================================================================================================================================||\n");
        printf("||===============================================     EMPRUNTEUR(S) LE(S) PLUS FREQUENT(S)     ===========================================================||\n");
        printf("||========================================================================================================================================================||\n\n");
        printf("Tapez 1 pour continuer, 0 pour retourner : ");
        while(scanf("%d", &choix1) != 1) {
            while(getchar() != '\n');
            printf("Tapez 1 pour continuer, 0 pour retourner : ");
        }
        Sleep(1000);
    } while (choix1 != 0 && choix1 != 1);

    if (choix1 == 0) {
        menustatistique();
        return;
    }

    if (nbEmprunts == 0) {
        printf("\nAucun emprunt enregistre dans le systeme!\n");
        printf("Retour au menu statistique...");
        Sleep(3000);
        return;
    }

    for (int i = 0; i < nbEmprunts; i++) {
        cin = matriceEmprunts[i][0];
        trouve = 0;

        for (int j = 0; j < nbEmprunteurs; j++) {
            if (CINu[j] == cin) {
                empruntsParCIN[j]++;
                trouve = 1;
                if (empruntsParCIN[j] > maxEmprunts) {
                    maxEmprunts = empruntsParCIN[j];
                }
            }
        }

        if (!trouve) {
            CINu[nbEmprunteurs] = cin;
            empruntsParCIN[nbEmprunteurs] = 1;
            if (1 > maxEmprunts) maxEmprunts = 1;
            nbEmprunteurs++;
        }
    }

    system("cls");
    printf("||========================================================================================================================================================||\n");
    printf("||                                                    EMPRUNTEURS LES PLUS ACTIFS                                                                         ||\n");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
    printf("|| Record d'emprunts : %3d livre(s)                                                                                                                       ||\n", maxEmprunts);
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");
    printf("|| %-74s | %-73s ||\n", "CIN", "Nb Emprunts");
    printf("||--------------------------------------------------------------------------------------------------------------------------------------------------------||\n");

for (int i = 0; i < nbEmprunteurs; i++) {
    if (empruntsParCIN[i] == maxEmprunts) {
        printf("|| %-74d | %-73d ||\n", CINu[i], empruntsParCIN[i]);
    }
}

    printf("||========================================================================================================================================================||\n");
    do{
    printf("\nPour retourner au menu statistiques, tapez 1 : ");
    while(scanf("%d", &choix1) != 1) {
        while(getchar() != '\n');
        printf("\nPour retourner au menu statistiques, tapez 1 : ");
    }
    }while(choix1!=1);
    printf("retour au menu statistiques...");
    Sleep(2000);
    system("cls");
    return;
}
