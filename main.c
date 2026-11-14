#include <stdio.h>
#include <string.h>

#include "src/note.h"

static void usage(void)
{
    printf("c-notes-cli - a tiny command line note manager\n\n");
    printf("usage:\n");
    printf("  notes-cli add <title> <tag> <body>   add a note\n");
    printf("  notes-cli list                       list all notes\n");
    printf("  notes-cli search <keyword>           search by keyword\n");
    printf("  notes-cli export <file>              export notes to a txt file\n");
    printf("  notes-cli help                       show this help\n");
}

int main(int argc, char **argv)
{
    Note notes[NOTE_MAX];
    int count;

    count = note_load(notes, NOTE_MAX);

    if (argc < 2 || strcmp(argv[1], "help") == 0) {
        usage();
        return 0;
    }

    if (strcmp(argv[1], "add") == 0) {
        if (argc < 5) {
            fprintf(stderr, "error: add needs <title> <tag> <body>\n");
            return 1;
        }
        count = note_add(notes, count, argv[2], argv[3], argv[4]);
        if (count < 0) {
            return 1;
        }
        if (note_save(notes, count) != 0) {
            return 1;
        }
        printf("added note #%d: %s\n", notes[count - 1].id, argv[2]);
        return 0;
    }

    if (strcmp(argv[1], "list") == 0) {
        note_list(notes, count);
        return 0;
    }

    if (strcmp(argv[1], "search") == 0) {
        if (argc < 3) {
            fprintf(stderr, "error: search needs a keyword\n");
            return 1;
        }
        note_search(notes, count, argv[2]);
        return 0;
    }

    if (strcmp(argv[1], "export") == 0) {
        if (argc < 3) {
            fprintf(stderr, "error: export needs a file path\n");
            return 1;
        }
        return note_export_txt(notes, count, argv[2]) < 0 ? 1 : 0;
    }

    fprintf(stderr, "error: unknown command \"%s\"\n", argv[1]);
    usage();
    return 1;
}
