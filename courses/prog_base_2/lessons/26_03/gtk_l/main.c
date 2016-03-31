#include <gtk/gtk.h>

struct AgroButtonState {
  GtkWidget* button;
  GtkWidget* label;
  int is_aggresive;
} agro_button_state;


static void on_agro_button_press(GtkWidget* w, gpointer user_data){
  struct AgroButtonState* s = user_data;
  s->is_aggresive = ! s->is_aggresive;
  if(s->is_aggresive){
    gtk_button_set_label((GtkButton*)s->button,"Now you are very sorry!");
    gtk_widget_show(s->label);
  } else {
    gtk_button_set_label((GtkButton*)s->button, "Don't push me, friend!");
    gtk_widget_hide(s->label);
  }
}

static void activate(GtkApplication* app, gpointer user_data){
  GtkWidget* window;
  GtkWidget* button_box;
  GtkWidget* button;
  GtkWidget* aggresive_label;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Hello!");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
  gtk_button_box_set_layout((GtkButtonBox*) button_box, GTK_BUTTONBOX_CENTER);

  gtk_container_add(GTK_CONTAINER(window), button_box);

  button = gtk_button_new_with_label("Don't push me, friend!");
  aggresive_label = gtk_label_new("You pushed a wrong button!!!11one");

  g_signal_connect(button,
                   "clicked",
		   G_CALLBACK(on_agro_button_press),
		   &agro_button_state);

  gtk_container_add(GTK_CONTAINER(button_box), button);
  gtk_container_add(GTK_CONTAINER(button_box), aggresive_label);

  gtk_widget_show_all(window);
  gtk_widget_hide(aggresive_label);

  agro_button_state.button = button;
  agro_button_state.label = aggresive_label;
  agro_button_state.is_aggresive = 0;

  GdkWindow* win = gtk_widget_get_parent_window(button);
  GdkCursor* watchCursor = gdk_cursor_new(GDK_WATCH);
  gdk_window_set_cursor(win, watchCursor);

}

int main(int argc, char* argv[]){
  GtkApplication* app;
  int status;

  app = gtk_application_new("atommed.github.io.learn_gtk",
                             G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
