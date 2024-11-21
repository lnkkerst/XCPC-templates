# Vim

vimrc：

```vim
" 设置 leader 为空格键
let mapleader = " "

" 设置 UFT-8 编码
set enc=utf-8
set fenc=utf-8
set termencoding=utf-8

" 关闭 vi 兼容
set nocompatible

" 显示相对行号
set number
set relativenumber

" 启用语法高亮
set t_Co=256
syntax on

" 高亮当前行和当前列
"set cursorline
"set cursorcolumn
"highlight CursorLine ctermbg=darkgray guibg=lightgray
"highlight CursorColumn ctermbg=darkgray guibg=lightgray

" 自动缩进
set autoindent
set smartindent

" 设置合适的缩进宽度
set tabstop=2        " 设置 Tab 键宽度为 2
set shiftwidth=2     " 设置缩进宽度为 2
set expandtab        " 用空格替代Tab

" 开启行内搜索时的高亮
set hlsearch

" 关闭错误的响铃提示
set noerrorbells

" 搜索时逐字符匹配
set incsearch
set ignorecase       " 搜索忽略大小写
set smartcase        " 如果包含大写字符，则区分大小写

" 设置颜色主题
set background=dark
colorscheme default

" 显示匹配的括号
set showmatch

" 开启剪切板支持
set clipboard=unnamedplus

" 设置取消回滚时最大操作数
set undolevels=1000

" 鼠标支持
set mouse=a

" 快速保存和退出命令
nnoremap <leader>w :w<CR>       " 用 \w 快速保存
nnoremap <leader>q :q<CR>       " 用 \q 快速退出

" 复制当前 buffer
nmap <leader>y ggVGy
"nmap <leader>y ggVG"+y''

" {} 括号补全
inoremap {<CR> {<CR>}<ESC>O

" 使用 x 删除时不自动复制
nnoremap x "_x
nnoremap X "_X
vnoremap x "_x
vnoremap X "_X

" 关闭搜索高亮
nnoremap <leader>l :noh<cr>

" 行内移动
nnoremap H ^
nnoremap L g_
vnoremap H ^
vnoremap L g_
```

常用操作：

```vim
" 在下方打开一个终端
:belowright terminal
```

```bash
# bash 指令

# X 下交换 esc 和 capslock，防止队友写代码
setxkbmap -option "caps:swapescape"
```
