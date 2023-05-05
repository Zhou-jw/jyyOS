The Shell Programming Language
基于文本替换的快速工作流搭建

重定向: cmd > file < file 2> /dev/null
顺序结构: cmd1; cmd2, cmd1 && cmd2, cmd1 || cmd2
管道: cmd1 | cmd2
预处理: $(), <()
变量/环境变量、控制流……
Job control

类比窗口管理器里的 “叉”、“最小化”
jobs, fg, bg, wait
(今天的 GUI 并没有比 CLI 多做太多事)

查看shell手册
man sh 