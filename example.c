#include <gtk/gtk.h>

void print_num(GtkWidget *button, gpointer user_data) {
  const char *label = gtk_widget_get_name(button);
  int num = 0;

  if (strcmp(label, "1") == 0) {
    num = 1;
  } else if (strcmp(label, "2") == 0) {
    num = 2;
  } else if (strcmp(label, "3") == 0) {
    num = 3;
  }
  g_print ("%d\n", num);
}

static void activate(GtkApplication *app) {
  GtkWidget *window;
  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *button3;
  GtkWidget *box;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (box, GTK_ALIGN_CENTER);

  gtk_window_set_child (GTK_WINDOW (window), box);

  button1 = gtk_button_new_with_label("1");
  gtk_widget_set_name(button1, "1");
  button2 = gtk_button_new_with_label("2");
  gtk_widget_set_name(button2, "2");
  button3 = gtk_button_new_with_label("3");
  gtk_widget_set_name(button3, "3");

  g_signal_connect (button1, "clicked", G_CALLBACK (print_num), NULL);
  g_signal_connect (button2, "clicked", G_CALLBACK (print_num), NULL);
  g_signal_connect (button3, "clicked", G_CALLBACK (print_num), NULL);
/*   g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_destroy), window); */

  gtk_box_append (GTK_BOX (box), button1);
  gtk_box_append (GTK_BOX (box), button2);
  gtk_box_append (GTK_BOX (box), button3);

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
