#include <gtk/gtk.h>

typedef struct {
  GtkEditable *entry;
  GtkLabel *label;
} EntryAndLabel;

void on_enter_pressed(GtkEditable *entry, gpointer user_data) {
  const char *usertext = gtk_editable_get_text(entry);
  double num = 0.0;
  for (int i = 0; usertext[i] != '\0'; i++) {
    if (usertext[i+1] != '\0') {
      int digitcounter = 0;
      double leftnum;
      double rightnum;
      char oper;
      
      if (sscanf(usertext, "%lf %c %lf", &leftnum, &oper, &rightnum) == 0) {
        g_print("sscanf error\n");
      }
      
     // make it work for multiple operations, parentheses etc
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
          break;
      }
    }
    }
    char str[20];
  if (num == (long long)num) {
    snprintf(str, sizeof(str), "%g", num);
  } else {
    snprintf(str, sizeof(str), "%g", num);
  }
  gtk_label_set_text(GTK_LABEL(user_data), str);
}

void on_button_pressed(GtkButton *button, gpointer user_data) {
  GtkEntry *entry = GTK_ENTRY(user_data);
  const char *entrytext = gtk_editable_get_text(user_data);
  const char *buttontext = gtk_button_get_label(button);
  GString *s = g_string_new(entrytext);
  g_string_append(s, buttontext);
  gtk_editable_set_text(GTK_EDITABLE(entry), s->str);
  g_string_free(s, TRUE);
  gtk_widget_grab_focus(GTK_WIDGET(entry));
}

void on_button_enter(GtkButton *button, gpointer user_data) {
  EntryAndLabel *eal = user_data;
  on_enter_pressed(eal->entry, eal->label);
}

static void activate(GtkApplication *app) {
  GtkWidget *window = gtk_application_window_new(app);
  GtkWidget *grid = gtk_grid_new();
  GtkWidget *label = gtk_label_new("");
  GtkWidget *entry = gtk_entry_new();
  GtkWidget *button1 = gtk_button_new_with_label("1");
  GtkWidget *button2 = gtk_button_new_with_label("2");
  GtkWidget *button3 = gtk_button_new_with_label("3");
  GtkWidget *button4 = gtk_button_new_with_label("4");
  GtkWidget *button5 = gtk_button_new_with_label("5");
  GtkWidget *button6 = gtk_button_new_with_label("6");
  GtkWidget *button7 = gtk_button_new_with_label("7");
  GtkWidget *button8 = gtk_button_new_with_label("8");
  GtkWidget *button9 = gtk_button_new_with_label("9");
  GtkWidget *button0 = gtk_button_new_with_label("0");
  GtkWidget *button_plus = gtk_button_new_with_label("+");
  GtkWidget *button_minus = gtk_button_new_with_label("-");
  GtkWidget *button_divide = gtk_button_new_with_label("/");
  GtkWidget *button_multiply = gtk_button_new_with_label("*");
  GtkWidget *button_power = gtk_button_new_with_label("^");
  GtkWidget *button_enter = gtk_button_new_with_label("=");
  GtkSettings *settings = gtk_settings_get_for_display(gtk_widget_get_display(window));
  g_object_set(settings, "gtk-error-bell", FALSE, NULL);
  gtk_widget_add_css_class(label, "label");
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_string(provider, ".label { font-size: 24px; color: #000000; }");
  gtk_style_context_add_provider_for_display(
    gdk_display_get_default(),
    GTK_STYLE_PROVIDER(provider),
    GTK_STYLE_PROVIDER_PRIORITY_USER
  );

  EntryAndLabel *eal = g_new(EntryAndLabel, 1);
  eal->entry = GTK_EDITABLE(entry);
  eal->label = GTK_LABEL(label);

  gtk_window_set_title(GTK_WINDOW(window), "calc");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
  gtk_window_set_child(GTK_WINDOW(window), grid);
  gtk_grid_attach(GTK_GRID(grid), label, 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), entry, 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button1, 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button2, 1, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button3, 2, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button4, 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button5, 1, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button6, 2, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button7, 0, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button8, 1, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button9, 2, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button0, 0, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button_plus, 1, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button_minus, 2, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button_divide, 0, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button_multiply, 1, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button_power, 2, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button_enter, 0, 7, 1, 1);
  gtk_window_present(GTK_WINDOW(window));
  
  gtk_widget_grab_focus(entry);
  g_signal_connect(entry, "activate", G_CALLBACK(on_enter_pressed), label);
  g_signal_connect(button1, "clicked", G_CALLBACK(on_button_pressed), entry);
  g_signal_connect(button2, "clicked", G_CALLBACK(on_button_pressed), entry);
  g_signal_connect(button3, "clicked", G_CALLBACK(on_button_pressed), entry);
  g_signal_connect(button4, "clicked", G_CALLBACK(on_button_pressed), entry);
  g_signal_connect(button5, "clicked", G_CALLBACK(on_button_pressed), entry);
  g_signal_connect(button6, "clicked", G_CALLBACK(on_button_pressed), entry);
  g_signal_connect(button7, "clicked", G_CALLBACK(on_button_pressed), entry);
  g_signal_connect(button8, "clicked", G_CALLBACK(on_button_pressed), entry);
  g_signal_connect(button9, "clicked", G_CALLBACK(on_button_pressed), entry);
  g_signal_connect(button0, "clicked", G_CALLBACK(on_button_pressed), entry);
  g_signal_connect(button_plus, "clicked", G_CALLBACK(on_button_pressed), entry);
  g_signal_connect(button_minus, "clicked", G_CALLBACK(on_button_pressed), entry);
  g_signal_connect(button_divide, "clicked", G_CALLBACK(on_button_pressed), entry);
  g_signal_connect(button_multiply, "clicked", G_CALLBACK(on_button_pressed), entry);
  g_signal_connect(button_power, "clicked", G_CALLBACK(on_button_pressed), entry);
  g_signal_connect(button_enter, "clicked", G_CALLBACK(on_button_enter), eal);
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
