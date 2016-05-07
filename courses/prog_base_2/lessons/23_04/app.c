#include <gtk/gtk.h>
#include <string.h>

typedef struct click_data {
  GtkWidget* list;
  GtkWidget* label;
  GtkWidget* name_in;
  GtkWidget* data_in;
  char* name;
  char* data;
} click_data;

static void on_select(GtkWidget* wgt, gpointer ptr){
  click_data* d = ptr;
  gtk_label_set_text(d->label, d->data);
}

static void on_add_btn_press(GtkWidget* wgt, gpointer ptr){
  GtkWidget* list;
  GtkWidget* label;
  click_data* new;
  click_data* d;

  d = ptr;

  new = malloc(sizeof(click_data));
  new->label = d->label;

  label = gtk_button_new_with_label(gtk_entry_buffer_get_text(
	gtk_entry_get_buffer(d->name_in)
	));
  d->data = gtk_entry_buffer_get_text(gtk_entry_get_buffer(d->data_in));
  new->data = malloc(strlen(d->data)+1);
  new->data[0]='\0';
  strcpy(new->data,d->data);
  g_signal_connect(label,"clicked", G_CALLBACK(on_select), new);
  puts("hell");
  gtk_list_box_prepend(d->list,label);
  gtk_widget_show(label);
}

static void activate(GtkApplication* app, gpointer user_data){
  GtkWidget* window;
  GtkWidget* wgt_box;
  GtkWidget* disp_label;
  GtkWidget* add_btn;
  GtkWidget* name_input;
  GtkWidget* data_input;
  GtkWidget* list;
  click_data* d;

  d= malloc(sizeof(click_data));
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "List!");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

  wgt_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
  gtk_button_box_set_layout((GtkButtonBox*) wgt_box, GTK_BUTTONBOX_CENTER);
  gtk_container_add(GTK_CONTAINER(window), wgt_box);

  add_btn = gtk_button_new_with_label("Add to list");
  disp_label = gtk_label_new("You pushed a wrong button!!!11one");
  name_input = gtk_entry_new();
  data_input = gtk_entry_new();
  list = gtk_list_box_new();

  d->label = disp_label;
  d->list = list;
  d->name_in = name_input;
  d->data_in = data_input;

  g_signal_connect(add_btn,
                   "clicked",
		   G_CALLBACK(on_add_btn_press),
		   d);

  gtk_container_add(GTK_CONTAINER(wgt_box), disp_label);
  gtk_container_add(GTK_CONTAINER(wgt_box), add_btn);
  gtk_container_add(GTK_CONTAINER(wgt_box), name_input);
  gtk_container_add(GTK_CONTAINER(wgt_box), data_input);
  gtk_container_add(GTK_CONTAINER(wgt_box), list);

  gtk_widget_show_all(window);
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
