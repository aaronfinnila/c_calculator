#include <gtk/gtk.h>

void on_enter_pressed(GtkEditable *entry, gpointer user_data) {
  const char *usertext = gtk_editable_get_text(entry);
  double num = 0.0;
  for (int i = 0; usertext[i] != '\0'; i++) {
    if (usertext[i+1] != '\0') {
      int digitcounter = 0;
      switch (usertext[i]) {
        double leftnum;
        double rightnum;
        char oper;
        
        if (sscanf(usertext, "%lf %c %lf", &leftnum, &oper, &rightnum) == 0) {
          g_print("sscanf error\n");
        }
        
        double rightnum;
        if (num != 0.0) {
          leftnum += num;
        }

        switch (oper) {
          case '+':
            num = leftnum + rightnum;
            break;
          case '-':
            num = leftnum - rightnum;
            break;
          case '*':
            num = leftnum * rightnum;
            break;
          case '/':
            num = leftnum / rightnum;
            break;
          case '^':
            num = pow(leftnum, rightnum);
        }
      }
    }
    }
    char str[20];
  if (num == (long long)num) {
    snprintf(str, sizeof(str), "%.0f", num);
  } else {
    snprintf(str, sizeof(str), "%.1f", num);
  }
  gtk_label_set_text(GTK_LABEL(user_data), str);
}

static void activate(GtkApplication *app) {
  GtkWidget *window;
  GtkWidget *box;
  GtkWidget *entry;
  GtkWidget *label;

  window = gtk_application_window_new (app);
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  label = gtk_label_new("");
  entry = gtk_entry_new();

  gtk_window_set_title(GTK_WINDOW(window), "calc");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_window_set_child(GTK_WINDOW(window), box);
  gtk_box_append(GTK_BOX(box), label);
  gtk_box_append(GTK_BOX(box), entry);
  gtk_window_present(GTK_WINDOW(window));
  
  gtk_widget_grab_focus(entry);
  g_signal_connect(entry, "activate", G_CALLBACK(on_enter_pressed), label);
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
