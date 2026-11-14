# c-notes-cli 使用说明

## 一、编译

```bash
gcc -std=c99 -Wall -o notes-cli main.c src/note.c
```

## 二、命令一览

| 命令 | 说明 |
| --- | --- |
| `notes-cli add <title> <tag> <body>` | 新增一条笔记，自动记录创建时间 |
| `notes-cli list` | 列出全部笔记（ID、时间、标签、标题） |
| `notes-cli search <keyword>` | 按标题或正文关键词检索，命中的记录会显示正文 |
| `notes-cli export <file>` | 把全部笔记导出为 Markdown（`.md`）或纯文本（其它后缀） |
| `notes-cli help` | 查看帮助 |

## 三、使用示例

### 1. 新增笔记

```bash
$ ./notes-cli add "指针与数组的区别" c "数组名是常量指针，指针是变量"
added note #1: 指针与数组的区别
```

标题、标签、正文各占一个参数，包含空格时用引号包裹。正文较长时建议先写关键词，方便后续检索。

### 2. 查看列表

```bash
$ ./notes-cli list
ID   CREATED           TAG          TITLE
1    2026-11-14 09:31  c            指针与数组的区别
2    2026-11-14 09:32  mysql        事务的四个特性
2 note(s) in total
```

### 3. 关键词检索

```bash
$ ./notes-cli search 事务
2    2026-11-14 09:32  mysql        事务的四个特性
     原子性、一致性、隔离性、持久性
1 hit(s) for "事务"
```

检索范围是标题和正文，区分英文大小写，中文按字符直接匹配。

### 4. 导出

```bash
$ ./notes-cli export notes.md
exported 2 note(s) to notes.md (markdown)
```

导出文件以 `.md` 结尾时生成 Markdown 文档，每条笔记一个二级标题，标题下依次是编号、创建时间、标签和
正文，便于放进博客或课程总结；以其它后缀导出则为纯文本格式。

## 四、数据文件

`data/notes.db` 每条记录一行，字段以制表符 `\t` 分隔：

```text
id	created	tag	title	body
```

## 五、常见问题

- **首次运行为什么会自动生成 data 目录？** 程序启动时检测到目录不存在会自动创建，避免写入失败。
- **笔记最多能存多少条？** 代码中 `NOTE_MAX` 默认 256 条，可在 `src/note.h` 中调整。
- **中文在 Windows 终端显示乱码？** 请使用支持 UTF-8 的终端（如 VS Code 集成终端）运行。
