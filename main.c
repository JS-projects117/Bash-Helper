#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>


#include <gtk/gtk.h>

static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
   // g_print ("Hello World\n");
}
static GtkTextIter start, end;
static GtkTextBuffer *buffer;
static char userPrompt[256];
static GtkTextMark *textMark;

static void LoadCommand(char input[]) {
    char charBuffer[512];
    chdir("/home");
    while (1) {

        //fgets(charBuffer, 1024000, stdin);
strcpy(charBuffer, input);

        int length;
        for (int i = 0; charBuffer[i] != '\0'; i++) {
            if (charBuffer[i] == '\n') {
                charBuffer[i] = '\0';
                length = i;;
                break;
            }
        }

        if (strcmp(charBuffer, "exit") == 0) {
            break;
        }

        char* command[100];
        char* stringPart = strtok(charBuffer, " ");
        int index = 0;
        while (stringPart != NULL) {
            command[index] = stringPart;
            // printf("%s\n",  command[index]);
            stringPart = strtok(NULL, " ");
            ++index;
        }

        if (strcmp(command[0], "cd") == 0) {
            char buffer[1024];
            chdir(command[1]);
            printf("%s\n", getcwd(buffer, sizeof(buffer)));
        }

        pid_t pid = fork();
        command[index] = NULL;

        if (pid == 0)

            if (strcmp(command[0], "cd") == 0) {
                char buffer[1024];
                chdir(command[1]);
                printf("%s\n", getcwd(buffer, sizeof(buffer)));
            }else if (strcmp(command[0], "apt") == 0) {
                printf("%s\n", "password: ");

            }
            else {
                execvp(command[0], command);
            }



        for (int j = 0; command[j] != NULL; j++) {
            printf("%s\n", command[j]);
        }
    }
}


gboolean key_press_event(GtkWidget * widget, GdkEventKey * event)
{
    (void)widget;
    if (event->keyval == GDK_KEY_Return) {
        if (buffer != NULL) {

            gtk_text_buffer_get_end_iter(buffer, &end);
            gtk_text_buffer_get_iter_at_mark(buffer, &start, textMark);

            char *command = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
            printf( "%s\n", command);


            gtk_text_buffer_insert(buffer, &end, userPrompt, -1);

            gtk_text_buffer_move_mark(buffer,textMark, &end);

//LoadCommand();
        }
        return TRUE;
    }else {
        return FALSE;
    }
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
    struct passwd *pw = getpwuid (getuid ());
    const char *username = pw ? pw->pw_name : "unknown";
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    snprintf(userPrompt, sizeof(userPrompt), "\n%s@%s:~$ ", username, hostname);


printf ("Username: %s\n", userPrompt);

    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button_box;
    GtkWidget *gtk_text_view;
    GtkWidget *terminalBox;



    window = gtk_application_window_new (app);


    gtk_window_set_title (GTK_WINDOW (window), "Bash Helper Terminal");
    gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);

    terminalBox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_text_view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtk_text_view));

    gtk_text_buffer_set_text(buffer, userPrompt, -1);

    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_get_start_iter(buffer, &start);
textMark = gtk_text_buffer_create_mark(buffer, "start_input", &start, FALSE );

    printf(gtk_text_buffer_get_text(buffer,&start, &end,FALSE));

    gtk_container_add (GTK_CONTAINER (window), terminalBox);
    gtk_box_pack_start(GTK_BOX(terminalBox), gtk_text_view, TRUE, TRUE,10);
    button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
    //gtk_container_add (GTK_CONTAINER (window), button_box);

    button = gtk_button_new_with_label ("Hello World");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    g_signal_connect (window, "key-press-event", G_CALLBACK (key_press_event), NULL);

    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_container_add (GTK_CONTAINER (button_box), button);

    gtk_widget_show_all (window);



    printf("%p", buffer);
}



int
main (int    argc,
      char **argv) {
    GtkApplication *app;
    int status;



    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}


