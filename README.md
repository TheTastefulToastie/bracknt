# Brackn't
Brackn't is a dusting of syntactic sugar on top of c-like programming languages that use { braces } to denote scopes such as C, C++, Java, JavaScript, etc. With Brackn't you can instead denote scope with indentation and the braces will be inserted automatically.
It will also generate the surrounding brackets for `if`, `for`, `while` and `switch` statements.

Example
=======
**Input source file**
```javascript
function greet(name)
    if name === undefined
        return
    console.log(`Hello ${name}`)

greet('Dave')
```

**Terminal command**
`bracknt file.js`

**stdout**
```javascript
function greet(name) {
    if( name === undefined ){
        return
    }
    console.log(`Hello ${name}`)
}
greet('Dave')
```

Program Output
===============================
The result is written to stdout for you to do what you want with it.
Save it to a file:
`bracknt example.br > example.c`
or execute it:
`bracknt example.js | node`
`bracknt example.c | gcc -xc -o example - && ./example`

Single Responsibility Principle
===============================
Bracknt has one job, and it does this as quickly and efficiently as possible, and as such it makes no effort to format the output and make it look pretty. The only concern is that the output compiles and runs correctly and Brackn't aims to be as language agnostic as possible.
If you want nicely formatted output simply use your formatter of choice for your language e.g.
`bracknt file.js | js-beautify`
`bracknt file.c | clang-format`
