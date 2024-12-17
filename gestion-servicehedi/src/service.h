#ifndef SERVICE_H_INCLUDED
#define SERVICE_H_INCLUDED

#include <stdio.h>
#include <gtk/gtk.h>

// Définition de la structure Service
typedef struct {
    char id[20];           // Identifiant unique du service
    char nom[50];          // Nom du service
    char description[100]; // Description du service
    char prix[10];         // Prix du service
} Service;

// CRUD simple
int ajouterService(char *filename, Service service);
int modifierService(char *filename, char id[], Service nouv);
int supprimerService(char *filename, char id[]);


// Treeview (partie afficher et chercher de CRUD)
void afficherService(GtkWidget *liste);
void chercherService(GtkWidget *liste, char idservice[]);

// Stat
float calculerFactureMensuelle(char *filename_reservations, char *filename_services, 
                               char *id_citoyen, char *mois, char *annee);
#endif // SERVICE_H_INCLUDED
