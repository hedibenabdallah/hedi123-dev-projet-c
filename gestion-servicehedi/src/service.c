#include "service.h"
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

// enum pour treeview
enum
{
    EIDSERVICE,
    ENOMSERVICE,
    EDESCRIPTIONSERVICE,
    EPRIXSERVICE,
    COLUMNS,
};


// ajouter une service

int ajouterService(char *filename, Service service) {
    FILE *f = fopen(filename, "a");

    if (f != NULL) {
        fprintf(f, "%s %s %s %s\n", service.id, service.nom, service.description, service.prix);
        fclose(f);
        return 1;
    } else {
        return 0;
    }
}


// modifier une service

int modifierService(char *filename, char id[], Service nouv) {
    int tr = 0;
    Service service;

    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");

    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%s %s %s %s\n", service.id, service.nom, service.description, service.prix) != EOF) {
            if (strcmp(service.id, id) == 0) {
                fprintf(f2, "%s %s %s %s\n", nouv.id, nouv.nom, nouv.description, nouv.prix);
                tr = 1;
            } else {
                fprintf(f2, "%s %s %s %s\n", service.id, service.nom, service.description, service.prix);
            }
        }
    }

    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}


// supprimer une service


int supprimerService(char *filename, char id[]) {
    int tr = 0;
    Service service;

    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");

    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%s %s %s %s\n", service.id, service.nom, service.description, service.prix) != EOF) {
            if (strcmp(service.id, id) == 0) {
                tr = 1;
            } else {
                fprintf(f2, "%s %s %s %s\n", service.id, service.nom, service.description, service.prix);
            }
        }
    }

    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}


// afficher services dans treeview:

void afficherService(GtkWidget *liste)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;

    char id[20];
    char nom[50];
    char description[100];
    char prix[10];
    Service service;

    FILE *f;

    store = gtk_tree_view_get_model(liste);
    if (store == NULL)
    {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Id Service", renderer, "text", EIDSERVICE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", ENOMSERVICE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Description", renderer, "text", EDESCRIPTIONSERVICE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Prix", renderer, "text", EPRIXSERVICE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }
    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    f = fopen("service.txt", "r");

    if (f == NULL)
    {
        return;
    }
    else
    {
        f = fopen("service.txt", "a+");
        while (fscanf(f, "%s %s %s %s\n", service.id, service.nom, service.description, service.prix) != EOF)
        {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, EIDSERVICE, service.id, ENOMSERVICE, service.nom, EDESCRIPTIONSERVICE, service.description, EPRIXSERVICE, service.prix);
        }
        fclose(f);
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }
}


// chercher les services dans treeview


void chercherService(GtkWidget *liste, char idservice[])
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;

    char id[20];
    char nom[50];
    char description[100];
    char prix[10];
    Service service;

    FILE *f;

    store = gtk_tree_view_get_model(liste);
    if (store == NULL)
    {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Id Service", renderer, "text", EIDSERVICE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", ENOMSERVICE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Description", renderer, "text", EDESCRIPTIONSERVICE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Prix", renderer, "text", EPRIXSERVICE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }
    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    f = fopen("service.txt", "r");

    if (f == NULL)
    {
        return;
    }
    else
    {
        f = fopen("service.txt", "a+");
        while (fscanf(f, "%s %s %s %s\n", service.id, service.nom, service.description, service.prix) != EOF)
        {
            if (strcmp(service.id, idservice) == 0)
            {
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter, EIDSERVICE, service.id, ENOMSERVICE, service.nom, EDESCRIPTIONSERVICE, service.description, EPRIXSERVICE, service.prix);
            }
        }
        fclose(f);
        gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
        g_object_unref(store);
    }
}



// Calculer la facture de citoyen:

float calculerFactureMensuelle(char *filename_reservations, char *filename_services, 
                               char *id_citoyen, char *mois, char *annee) {
    FILE *f_res = fopen(filename_reservations, "r");
    FILE *f_serv = fopen(filename_services, "r");

    if (f_res == NULL || f_serv == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return -1;
    }

    char id_reservation[20], id_parking[20], date_reservation[15], id_service[20], id_client[20];
    int duree, tarif;
    float facture = 0;

    // Charger les services dans un tableau pour un accès rapide
    Service services[100];
    int service_count = 0;

    while (fscanf(f_serv, "%s %s %s %s", 
                  services[service_count].id, 
                  services[service_count].nom, 
                  services[service_count].description, 
                  services[service_count].prix) != EOF) {
        service_count++;
    }
    fclose(f_serv);

    // Parcourir les réservations
    while (fscanf(f_res, "%s %s %d %s %d %s %s", 
                  id_reservation, id_parking, &duree, date_reservation, &tarif, id_service, id_client) != EOF) {
        // Vérifier si l'ID du citoyen correspond
        if (strcmp(id_client, id_citoyen) == 0) {
            // Extraire mois et année de la date de réservation
            char mois_res[3], annee_res[5];
            strncpy(mois_res, date_reservation + 3, 2);  // Mois (MM)
            mois_res[2] = '\0';
            strncpy(annee_res, date_reservation + 6, 4); // Année (YYYY)
            annee_res[4] = '\0';

            // Vérifier si le mois et l'année correspondent
            if (strcmp(mois_res, mois) == 0 && strcmp(annee_res, annee) == 0) {
                // Ajouter le coût de la réservation
                facture += duree * tarif;

                // Ajouter le prix du service lié
                for (int i = 0; i < service_count; i++) {
                    if (strcmp(services[i].id, id_service) == 0) {
                        facture += atof(services[i].prix); // Convertir le prix en float
                        break;
                    }
                }
            }
        }
    }
    fclose(f_res);

    return facture;
}
