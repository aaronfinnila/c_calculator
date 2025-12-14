#include <gtk/gtk.h>
#include <math.h>

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
  GtkEditable *entry = GTK_EDITABLE(user_data);

  const char *entrytext = gtk_editable_get_text(entry);
  const char *buttontext = gtk_button_get_label(button);

  GString *s = g_string_new(entrytext);
  g_string_append(s, buttontext);

  gtk_editable_set_text(entry, s->str);
  g_string_free(s, TRUE);
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

  GtkWidget *buttons[15];
  char button_labels[] = "1234567890+-/*^";

  for (int i = 0; i < strlen(button_labels); i++) {
    char button_label[2] = {button_labels[i], '\0'};

    buttons[i] = gtk_button_new_with_label(button_label);

    gtk_grid_attach(GTK_GRID(grid), buttons[i], i % 3, 2 + (i / 3), 1, 1);
    gtk_widget_add_css_class(buttons[i], "button");
    gtk_widget_set_hexpand(GTK_WIDGET(buttons[i]), FALSE);
    g_signal_connect(buttons[i], "clicked", G_CALLBACK(on_button_pressed), entry);
  }

  GtkWidget *button_enter = gtk_button_new_with_label("=");
  gtk_grid_attach(GTK_GRID(grid), button_enter, 1, 7, 1, 1);
  gtk_widget_add_css_class(button_enter, "enter-button");
  gtk_widget_set_hexpand(GTK_WIDGET(button_enter), FALSE);

  GtkSettings *settings = gtk_settings_get_for_display(gtk_widget_get_display(window));
  g_object_set(settings, "gtk-error-bell", FALSE, NULL);

  gtk_widget_add_css_class(label, "label");
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_string(provider,
  ".label { font-size: 40px; color: #36454F; min-height: 36px; }"
  ".button { color: #000000; }"
  );
  gtk_style_context_add_provider_for_display(
    gdk_display_get_default(),
    GTK_STYLE_PROVIDER(provider),
    GTK_STYLE_PROVIDER_PRIORITY_USER
  );

  EntryAndLabel *eal = g_new(EntryAndLabel, 1);
  eal->entry = GTK_EDITABLE(entry);
  eal->label = GTK_LABEL(label);


  gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 3, 1);
  gtk_grid_attach(GTK_GRID(grid), entry, 0, 1, 3, 1);

  g_signal_connect(entry, "activate", G_CALLBACK(on_enter_pressed), label);
  g_signal_connect(button_enter, "clicked", G_CALLBACK(on_button_enter), eal);

  gtk_window_set_title(GTK_WINDOW(window), "calc");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
  gtk_window_set_child(GTK_WINDOW(window), grid);
  gtk_window_present(GTK_WINDOW(window));
  gtk_widget_grab_focus(entry);
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
