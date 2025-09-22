#include <stdio.h>
#include <string.h>
#include <unistd.h>



#include <gtk/gtk.h>

static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
    g_print ("Hello World\n");
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button_box;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Bash Helper Terminal");
    gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);

    button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add (GTK_CONTAINER (window), button_box);

    button = gtk_button_new_with_label ("Hello World");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_container_add (GTK_CONTAINER (button_box), button);

    gtk_widget_show_all (window);
}

int
main (int    argc,
      char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}


// int main(void) {
//
//     char charBuffer[1020400];
//     chdir("/home");
//     while (1) {
//
//         fgets(charBuffer, 1024000, stdin);
//
//         int length;
//         for (int i = 0; charBuffer[i] != '\0'; i++) {
//             if (charBuffer[i] == '\n') {
//                 charBuffer[i] = '\0';
//                 length = i;;
//                 break;
//             }
//         }
//
//         if (strcmp(charBuffer, "exit") == 0) {
//             break;
//         }
//
//         char* command[100];
//         char* stringPart = strtok(charBuffer, " ");
//         int index = 0;
//         while (stringPart != NULL) {
//             command[index] = stringPart;
//             // printf("%s\n",  command[index]);
//             stringPart = strtok(NULL, " ");
//             ++index;
//         }
//
//         if (strcmp(command[0], "cd") == 0) {
//             char buffer[1024];
//             chdir(command[1]);
//             printf("%s\n", getcwd(buffer, sizeof(buffer)));
//         }
//
//        pid_t pid = fork();
//         command[index] = NULL;
//
//         if (pid == 0)
//
//             if (strcmp(command[0], "cd") == 0) {
//                 char buffer[1024];
//                 chdir(command[1]);
//                 printf("%s\n", getcwd(buffer, sizeof(buffer)));
//             }else if (strcmp(command[0], "apt") == 0) {
//                 printf("%s\n", "password: ");
//
//             }
//         else {
//                 execvp(command[0], command);
//             }
//
//
//
//         for (int j = 0; command[j] != NULL; j++) {
//             printf("%s\n", command[j]);
//         }
//     }
//
//     return 0;
// }