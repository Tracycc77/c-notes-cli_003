#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <direct.h>
#define NOTE_MKDIR(p) _mkdir(p)
#else
#include <sys/stat.h>
#define NOTE_MKDIR(p) mkdir(p, 0755)
#endif

#include "note.h"

/* 数据库目录不存在时先创建，保证首次运行也能写入 */
static void note_ensure_dir(void)
{
    NOTE_MKDIR(NOTE_DB_DIR);
}

/* 取当前时间，格式化为 YYYY-MM-DD HH:MM */
static void note_now(char *buf, size_t len)
{
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);
    strftime(buf, len, "%Y-%m-%d %H:%M", lt);
}

int note_load(Note *notes, int max)
{
    FILE *fp;
    int count = 0;
    char line[NOTE_TITLE_MAX + NOTE_TAG_MAX + NOTE_BODY_MAX + 64];

    fp = fopen(NOTE_DB_PATH, "r");
    if (fp == NULL) {
        return 0; /* 首次运行时数据库还不存在 */
    }

    while (count < max && fgets(line, sizeof(line), fp) != NULL) {
        Note *n = &notes[count];
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0') {
            continue;
        }
        if (sscanf(line, "%d\t%19[^\t]\t%31[^\t]\t%63[^\t]\t%255[^\n]",
                   &n->id, n->created, n->tag, n->title, n->body) == 5) {
            count++;
        }
    }
    fclose(fp);
    return count;
}

int note_save(const Note *notes, int count)
{
    FILE *fp;
    int i;

    note_ensure_dir();
    fp = fopen(NOTE_DB_PATH, "w");
    if (fp == NULL) {
        fprintf(stderr, "error: cannot open %s for writing\n", NOTE_DB_PATH);
        return -1;
    }
    for (i = 0; i < count; i++) {
        fprintf(fp, "%d\t%s\t%s\t%s\t%s\n",
                notes[i].id, notes[i].created, notes[i].tag,
                notes[i].title, notes[i].body);
    }
    fclose(fp);
    return 0;
}

int note_add(Note *notes, int count, const char *title,
             const char *tag, const char *body)
{
    Note *n;
    int new_id = 1;

    if (count >= NOTE_MAX) {
        fprintf(stderr, "error: note storage is full (%d)\n", NOTE_MAX);
        return -1;
    }
    if (count > 0) {
        new_id = notes[count - 1].id + 1;
    }

    n = &notes[count];
    memset(n, 0, sizeof(Note));
    n->id = new_id;
    note_now(n->created, sizeof(n->created));
    snprintf(n->tag, sizeof(n->tag), "%s", tag == NULL ? "" : tag);
    snprintf(n->title, sizeof(n->title), "%s", title);
    snprintf(n->body, sizeof(n->body), "%s", body == NULL ? "-" : body);

    return count + 1;
}

void note_list(const Note *notes, int count)
{
    int i;

    if (count == 0) {
        printf("(no notes yet)\n");
        return;
    }
    printf("%-4s %-17s %-12s %s\n", "ID", "CREATED", "TAG", "TITLE");
    for (i = 0; i < count; i++) {
        printf("%-4d %-17s %-12s %s\n",
               notes[i].id, notes[i].created, notes[i].tag, notes[i].title);
    }
    printf("%d note(s) in total\n", count);
}

int note_search(const Note *notes, int count, const char *keyword)
{
    int i, hits = 0;

    for (i = 0; i < count; i++) {
        if (strstr(notes[i].title, keyword) != NULL ||
            strstr(notes[i].body, keyword) != NULL) {
            printf("%-4d %-17s %-12s %s\n",
                   notes[i].id, notes[i].created, notes[i].tag, notes[i].title);
            printf("     %s\n", notes[i].body);
            hits++;
        }
    }
    printf("%d hit(s) for \"%s\"\n", hits, keyword);
    return hits;
}

int note_export_txt(const Note *notes, int count, const char *path)
{
    FILE *fp;
    int i;

    fp = fopen(path, "w");
    if (fp == NULL) {
        fprintf(stderr, "error: cannot open %s for writing\n", path);
        return -1;
    }
    fprintf(fp, "c-notes-cli export (%d notes)\n\n", count);
    for (i = 0; i < count; i++) {
        fprintf(fp, "[%d] %s  #%s  %s\n", notes[i].id, notes[i].created,
                notes[i].tag, notes[i].title);
        fprintf(fp, "    %s\n\n", notes[i].body);
    }
    fclose(fp);
    printf("exported %d note(s) to %s\n", count, path);
    return count;
}
