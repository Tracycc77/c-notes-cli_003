# 贡献指南

感谢你愿意为 c-notes-cli 提交改进。为了让协作过程清晰可控，请遵循以下流程。

## 一、报告问题

在 Issues 页面新建 Issue，标题写清楚现象，正文尽量包含：

1. 运行环境（Windows / Linux、gcc 版本）
2. 复现步骤与执行的完整命令
3. 期望结果与实际结果
4. 相关截图或报错输出

## 二、分支约定

| 分支 | 用途 |
| --- | --- |
| `main` | 始终保持可运行的稳定版本，不直接提交功能代码 |
| `feature/<名称>` | 新功能开发，如 `feature/tag-search` |
| `bugfix/<名称>` | 缺陷修复，如 `bugfix/export-encoding` |

## 三、提交改动

```bash
git checkout main
git pull
git checkout -b feature/your-feature
# 修改代码
git add .
git commit -m "feat: 一句话说明本次改动"
git push -u origin feature/your-feature
```

提交信息建议使用 `feat:`、`fix:`、`docs:`、`chore:` 前缀。

## 四、发起 Pull Request

1. 在 GitHub 上以 `main` 为基准分支发起 Pull Request
2. 说明改动内容、测试方式与影响范围
3. 至少一位维护者查看后合并，合并后删除已合并的功能分支

## 五、代码风格

- 遵循 C99，缩进 4 个空格
- 函数命名使用 `note_` 前缀，如 `note_add`
- 新增函数需在 `src/note.h` 中声明
- 提交前请用 `gcc -std=c99 -Wall` 编译，确保无警告
