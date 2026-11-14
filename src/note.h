#ifndef NOTE_H
#define NOTE_H

#define NOTE_TITLE_MAX 64
#define NOTE_TAG_MAX 32
#define NOTE_BODY_MAX 256
#define NOTE_MAX 256
#define NOTE_DB_DIR "data"
#define NOTE_DB_PATH "data/notes.db"

/* 一条学习笔记 */
typedef struct {
    int  id;                     /* 自增编号 */
    char created[20];            /* 创建时间，格式 YYYY-MM-DD HH:MM */
    char tag[NOTE_TAG_MAX];      /* 分类标签，如 c、mysql、算法 */
    char title[NOTE_TITLE_MAX];  /* 笔记标题 */
    char body[NOTE_BODY_MAX];    /* 笔记正文 */
} Note;

/* 从 data/notes.db 读取全部笔记，返回实际条数；文件不存在时返回 0 */
int  note_load(Note *notes, int max);

/* 将内存中的笔记整体写回 data/notes.db，成功返回 0 */
int  note_save(const Note *notes, int count);

/* 新增一条笔记，返回新的总条数；失败返回 -1 */
int  note_add(Note *notes, int count, const char *title,
              const char *tag, const char *body);

/* 打印笔记列表 */
void note_list(const Note *notes, int count);

/* 按标题或正文关键词查找，返回命中条数 */
int  note_search(const Note *notes, int count, const char *keyword);

/* 按标签查找，返回命中条数 */
int  note_search_tag(const Note *notes, int count, const char *tag);

/* 导出为纯文本文件，返回成功导出的条数；失败返回 -1 */
int  note_export_txt(const Note *notes, int count, const char *path);

#endif /* NOTE_H */
