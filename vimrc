source $VIMRUNTIME/vimrc_example.vim
unlet! skip_deafult_vim

" highlight yara rules
autocmd BufNewFile,BufRead *.yar,*.yara,*rule setlocal filetype=yara

" use the better highlighting for assembly files
autocmd BufNewFile,BufRead *.s setlocal filetype=nasm

" toggle both relative line numbers and normal numbers
set relativenumber
set number

" simulate nano's behavior
set nowrap

" use gruvebox theme, 'yay -S vim-gruvbox-git' for this to work
colorscheme gruvbox
set bg=dark

" highlight the current line
set cursorline

" autocompletion, you have to press ctrl-n for it to show suggestions tho :(
" for a better (agreesive) completion, install coc (rock_look.gif) plugin
filetype plugin on
set omnifunc=syntaxcomplete#Complete

" color trailing whitespanes like nano does
highlight trailing_white_spaces ctermbg=red
match trailing_white_spaces /\s\+$/

" map <Delete> to :nohl to disable highlighting after search
noremap <silent> <Delete> :noh<Enter>

" easy exits
noremap wq :wq<Enter>
noremap qq :q!<Enter>

" easy redo
noremap rr :redo<Enter>

" completion
inoremap ( ()<Left>
inoremap [ []<Left>
inoremap { {}<Left>

" skip over closing characters
inoremap <expr> )  strpart(getline('.'), col('.')-1, 1) == ")" ? "\<Right>" : ")"
inoremap <expr> ]  strpart(getline('.'), col('.')-1, 1) == "]" ? "\<Right>" : "]"
inoremap <expr> }  strpart(getline('.'), col('.')-1, 1) == "}" ? "\<Right>" : "}"

inoremap <expr> "  strpart(getline('.'), col('.')-1, 1) == '"' ? "\<Right>" : '""<Left>'
inoremap <expr> '  strpart(getline('.'), col('.')-1, 1) == "'" ? "\<Right>" : "''<Left>"

