#  Quadratic-Equation-Solver
---
This app is a simple CLI application to solve quadratic equations.  
It has 2 modes:
- interactive
- noninteractive(file)


## Installation
```bash
$ git clone https://github.com/neliudochka/Quadratic-Equation-Solver.git
$ cd Quadratic-Equation-Solver/
```
it is already compiled, but if you want to do it on your own then for gcc compiler run:
```bash
$ gcc -o equation equation.c -lm
```


## Usage
for interactive mode
```bash
$ ./equation
```


for noninteractive(file) mode
```bash
$ ./equation <file_name>
```


## Format of the file for noninteractive(file) mode
you should write coefficients a, b, c this way:  
`<a>\s<b>\s<c>\n`\  
where \s - space character, \n - new line  
If in the format will be some mistakes, the program won't work, so be carefull  

## Revert-commit
You can look on it [here](https://github.com/neliudochka/Quadratic-Equation-Solver/commit/1e1e09a537a14581d6233ac6f18c34727cd591cf)
