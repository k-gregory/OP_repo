from gi.repository import Gtk, GLib


class Notifier(Gtk.Window):

    def get_time(self):
        if(self.working):
            return self.work_time
        else:
            return self.free_time

    def get_message(self):
        if self.working:
            new_mode = "rest"
        else:
            new_mode = "working"
        return "It's " + new_mode + " time!"

    def __init__(self, free_time=5 * 60, work_time=20 * 60):
        self.working = False
        self.free_time = free_time
        self.work_time = work_time

        Gtk.Window.__init__(self, title="Be effective!")
        self.set_keep_above(True)

        self.box = Gtk.VBox(spacing=5)

        self.label = Gtk.Label(label=self.get_message())
        self.ok_button = Gtk.Button(label="Ok, I'll do it!")
        self.ok_button.connect('clicked', self.mode_accepted)
        self.exit_button = Gtk.Button(label="Fuck it all!")
        self.exit_button.connect('clicked', Gtk.main_quit)

        self.box.pack_start(self.label, True, True, 0)
        self.box.pack_start(self.ok_button, True, True, 0)
        self.box.pack_start(self.exit_button, True, True, 0)

        self.add(self.box)

    def mode_accepted(self, widget):
        self.ok_button.set_sensitive(False)
        self.set_keep_above(False)
        self.iconify()
        self.working = not self.working

        def time_to_change_mode():
            self.set_keep_above(True)
            self.ok_button.set_sensitive(True)
            self.label.set_text(self.get_message())
            self.deiconify()
            self.set_focus(self.ok_button)
            return False  # Do not repeat

        GLib.timeout_add_seconds(self.get_time(), time_to_change_mode)


wnd = Notifier()
wnd.connect('delete-event', Gtk.main_quit)
wnd.show_all()

Gtk.main()
