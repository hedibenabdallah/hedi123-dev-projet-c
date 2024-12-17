/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"

int
main (int argc, char *argv[])
{
  GtkWidget *sign_in_;
  GtkWidget *gestion_reservation;
  GtkWidget *gestion_compte;
  GtkWidget *gestion_des_agents_;
  GtkWidget *gestion_de_service_;
  GtkWidget *point_de_vue_client_;
  GtkWidget *point_de_vue_agent;
  GtkWidget *gestion_des_avis___reclamations_;
  GtkWidget *window1;
  GtkWidget *gestion_parking_;

#ifdef ENABLE_NLS
  bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);
#endif

  gtk_set_locale ();
  gtk_init (&argc, &argv);

  add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");

  /*
   * The following code was added by Glade to create one of each component
   * (except popup menus), just so that you see something after building
   * the project. Delete any components that you don't want shown initially.
   */
  sign_in_ = create_sign_in_ ();
 /* gtk_widget_show (sign_in_);
  gestion_reservation = create_gestion_reservation ();
  gtk_widget_show (gestion_reservation);
  gestion_compte = create_gestion_compte ();
  gtk_widget_show (gestion_compte);
  gestion_des_agents_ = create_gestion_des_agents_ ();
  gtk_widget_show (gestion_des_agents_);*/
  gestion_de_service_ = create_gestion_de_service_ ();
  gtk_widget_show (gestion_de_service_);
 /* point_de_vue_client_ = create_point_de_vue_client_ ();
  gtk_widget_show (point_de_vue_client_);
  point_de_vue_agent = create_point_de_vue_agent ();
  gtk_widget_show (point_de_vue_agent);
  gestion_des_avis___reclamations_ = create_gestion_des_avis___reclamations_ ();
  gtk_widget_show (gestion_des_avis___reclamations_);
  window1 = create_window1 ();
  gtk_widget_show (window1);
  gestion_parking_ = create_gestion_parking_ ();
  gtk_widget_show (gestion_parking_);*/

  gtk_main ();
  return 0;
}
