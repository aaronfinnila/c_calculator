#include <gtk/gtk.h>

void print_num(GtkWidget *button, gpointer user_data) {
  const char *label = gtk_widget_get_name(button);
  int num = 0;

  g_print ("%d\n", num);
}

void react_click(GtkWidget *button, gpointer user_data) {
  const gchar *usertext = gtk_editable_get_text(GTK_EDITABLE(user_data));
  g_print("%s\n", usertext);
}

static void activate(GtkApplication *app) {
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *box;
  GtkWidget *entry;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "calc");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (box, GTK_ALIGN_CENTER);

  gtk_window_set_child (GTK_WINDOW (window), box);

  button = gtk_button_new_with_label("click to print");
  entry = gtk_entry_new();

  g_signal_connect(button, "clicked", G_CALLBACK (react_click), entry);

  gtk_box_append (GTK_BOX (box), button);
  gtk_box_append (GTK_BOX (box), entry);
  gtk_window_present (GTK_WINDOW (window));
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
