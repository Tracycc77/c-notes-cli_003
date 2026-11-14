# Changelog

本项目的主要变更记录，格式参考 [Keep a Changelog](https://keepachangelog.com/)。

## [0.2.0] - 2026-11-14

### Added

- 按标签检索笔记（`notes-cli search --tag <tag>`），便于把一个主题下的笔记集中复习
- 导出 Markdown 文档（`notes-cli export notes.md`），每条笔记生成一个二级标题

### Fixed

- 合并 `feature/export-md` 与 `feature/tag-search` 时 `src/note.c`、`docs/usage.md` 出现冲突，
  手工保留双方改动后重新编译通过

## [0.1.0] - 2026-11-14

### Added

- 新增笔记并自动记录创建时间（`notes-cli add`）
- 标签分类字段，便于按主题整理
- 标题与正文关键词检索（`notes-cli search`）
- 笔记列表查看（`notes-cli list`）
- 纯文本导出（`notes-cli export`）
- `data/notes.db` 纯文本存储，首次运行自动创建目录
- README、使用说明、贡献指南等基础文档
- MIT 许可证
