#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "service.h"


// variables statiques pour preserver l'etat de confirmation (ajout, modif ou supprimer)
static gboolean ajout_service_confirme = FALSE;
static gboolean modif_service_confirme = FALSE;
static gboolean suppr_service_confirme = FALSE;


void
on_buttonAjService_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *input1;
    GtkWidget *input2;
    GtkWidget *input3, *msg;

    GtkWidget *spin;

    Service service;
    int prix;

    // Récupérer ID, nom et description du service
    input1 = lookup_widget(button, "entry40");
    input2 = lookup_widget(button, "entry41");
    input3 = lookup_widget(button, "entry67");
    msg = lookup_widget(button, "label166");

    char message[] = "Un nouveau service a été ajouté avec succès ";

    strcpy(service.id, gtk_entry_get_text(GTK_ENTRY(input1)));
    strcpy(service.nom, gtk_entry_get_text(GTK_ENTRY(input2)));
    strcpy(service.description, gtk_entry_get_text(GTK_ENTRY(input3)));

    // Récupérer prix de service
    spin = lookup_widget(button, "spinbutton35");
    prix = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin));
    sprintf(service.prix, "%d", prix);

    // Ajouter le service dans le fichier "service.txt"
    if (ajout_service_confirme) {
        if (ajouterService("service.txt", service)) { 
            gtk_label_set_text(GTK_LABEL(msg), message);
        } else {
            gtk_label_set_text(GTK_LABEL(msg), "Erreur lors de l'ajout du service.");
        }

        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin), 100);
        gtk_entry_set_text(GTK_ENTRY(input1), "");
        gtk_entry_set_text(GTK_ENTRY(input2), "");
        gtk_entry_set_text(GTK_ENTRY(input3), "");
    } else {
        gtk_label_set_text(GTK_LABEL(msg), "Veuillez confirmer l'ajout !");
    }
}


void
on_checkbuttonAjService_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
ajout_service_confirme = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton));
}


void
on_buttonModService_clicked            (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *input1;
GtkWidget *input2;
GtkWidget *input3;
GtkWidget *msg;
GtkWidget *spin;

Service service;
int prix;
char message[100];

// Récuperer ID, nom et description du service
input1 = lookup_widget(button, "entry68");
input2 = lookup_widget(button, "entry69");
input3 = lookup_widget(button, "entry70");

strcpy(service.id, gtk_entry_get_text(GTK_ENTRY(input1)));
strcpy(service.nom, gtk_entry_get_text(GTK_ENTRY(input2)));
strcpy(service.description, gtk_entry_get_text(GTK_ENTRY(input3)));

// Récuperer prix de service
spin = lookup_widget(button, "spinbutton36");
prix = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin));
sprintf(service.prix, "%d", prix);

// Récuperer label
msg= lookup_widget(button, "label173");
sprintf(message, "Le service avec ID  < %s > a été modifié", service.id);


// Modifier le service
if (modif_service_confirme) {
    if (modifierService("service.txt", service.id, service)) { 
        gtk_label_set_text(GTK_LABEL(msg), message);
    } else {
        gtk_label_set_text(GTK_LABEL(msg), "Erreur lors de la modification du service.");
    }

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin), 100);
    gtk_entry_set_text(GTK_ENTRY(input1), "");
    gtk_entry_set_text(GTK_ENTRY(input2), "");
    gtk_entry_set_text(GTK_ENTRY(input3), "");
} else {
    gtk_label_set_text(GTK_LABEL(msg), "Veuillez confirmer la modification !");
}
}


void
on_checkbuttonModService_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
modif_service_confirme = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton));
}


void
on_buttonSupService_clicked            (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *input1;
GtkWidget *msg;


// Récuperer ID de service à supprimer et label
input1 = lookup_widget(button, "entry45");
msg= lookup_widget(button, "label277");

if (suppr_service_confirme) {

if (supprimerService("service.txt", gtk_entry_get_text(GTK_ENTRY(input1)))) { 
        gtk_label_set_text(GTK_LABEL(msg), "Service supprimé avec succés !");
    } else {
        gtk_label_set_text(GTK_LABEL(msg), "Erreur lors de la suppression du service.");
    }
    gtk_entry_set_text(GTK_ENTRY(input1), "");
} else {
    gtk_label_set_text(GTK_LABEL(msg), "Veuillez confirmer la suppression !");
}
}


void
on_checkbuttonSupService_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
suppr_service_confirme = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton));
}


void
on_buttonAffichService_clicked         (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview;
treeview = lookup_widget(button, "treeview10");
afficherService(treeview);
}


void
on_buttonChercherService_clicked       (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *entrych;
GtkWidget *treeview;

    entrych = lookup_widget(button, "entry71");
    treeview = lookup_widget(button, "treeview10");
    chercherService(treeview, gtk_entry_get_text(GTK_ENTRY(entrych)));

}



void on_buttonCalculerFacture_clicked(GtkWidget *button, gpointer user_data)
{
    GtkWidget *entry1;
    GtkWidget *spin1, *spin2;
    GtkWidget *msg;

    char id_citoyen[100];
    int mois, annee;
    char mois_str[3], annee_str[5];
    float facture = 0;
    char message[100];

    // Récupérer les champs ID citoyen, mois et année
    entry1 = lookup_widget(button, "entry72");
    spin1 = lookup_widget(button, "spinbutton37");
    spin2 = lookup_widget(button, "spinbutton38");

    strcpy(id_citoyen, gtk_entry_get_text(GTK_ENTRY(entry1)));
    mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin1));
    annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin2));

    // Convertir mois et annee en chaînes
    sprintf(mois_str, "%02d", mois);
    sprintf(annee_str, "%04d", annee);

    // Récupérer le label
    msg = lookup_widget(button, "label283");

    // Calculer la facture
    facture = calculerFactureMensuelle("reservations_1.txt", "service.txt", id_citoyen, mois_str, annee_str);
    
    // Formatage du message
    sprintf(message, "La facture de date %d/%d de citoyen %s est %.2f TND", mois, annee, id_citoyen, facture);

    // Afficher le message dans le label
    gtk_label_set_text(GTK_LABEL(msg), message);
}

