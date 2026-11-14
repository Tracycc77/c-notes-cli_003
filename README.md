# c-notes-cli_003

课程开源实践：C语言命令行学习笔记管理小工具

一个用 C99 编写、无第三方依赖的极简命令行学习笔记管理工具。课程笔记、代码片段和学习资料常常分散在
不同文件夹和聊天记录里，本项目用最基础的文件读写与命令行交互，把「记一条笔记、找一条笔记」这两件事
做得足够简单。

## 功能特性

- 新增笔记，自动记录创建时间
- 用标签给笔记分类，例如 `c`、`mysql`、`算法`
- 按标题或正文关键词检索笔记，也可用 `--tag` 只看某一分类的笔记
- 查看全部笔记列表
- 导出为 Markdown 文档（`export notes.md`），也支持导出纯文本

## 运行环境

- GCC 编译器（MinGW-w64 gcc 或 Linux gcc，C99 标准）
- 无第三方库依赖，不需要联网

## 安装与编译

```bash
git clone https://github.com/Tracycc77/c-notes-cli_003.git
cd c-notes-cli_003
gcc -std=c99 -Wall -o notes-cli main.c src/note.c
```

Windows 下生成 `notes-cli.exe`，Linux / macOS 下生成 `notes-cli`。

## 快速开始

```bash
./notes-cli add "指针与数组的区别" c "数组名是常量指针，指针是变量"
./notes-cli list
./notes-cli search 指针
./notes-cli export notes.md
```

## 目录结构

```text
c-notes-cli_003/
├── main.c              # 命令解析与程序入口
├── src/
│   ├── note.h          # 数据结构与接口声明
│   └── note.c          # 读写、检索、导出等核心实现
├── docs/
│   └── usage.md        # 详细使用说明
├── examples/
│   └── sample-note.txt # 示例笔记数据
├── README.md
├── CONTRIBUTING.md     # 贡献指南
├── CHANGELOG.md        # 版本变更记录
└── LICENSE             # MIT 许可证
```

## 数据存放

笔记默认保存在运行目录下的 `data/notes.db`，纯文本、制表符分隔，可以直接用编辑器打开查看。

## 如何贡献

欢迎提交 Issue 反馈问题或提出改进建议；新功能请在 `feature/` 分支开发，完成后提交 Pull Request。
详细流程见 [CONTRIBUTING.md](CONTRIBUTING.md)。

## 许可证

本项目基于 [MIT License](LICENSE) 开源。
