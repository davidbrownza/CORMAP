<img src="https://travis-ci.org/davidbrownza/CORMAP.svg?branch=master" align="right">

# CORMAP
Simple C++ classes for Object Relational Mapping

### Dependencies:
`sudo apt-get install libmysqlcppconn-dev`

### Developer guidelines
Cormap has been developed using the following code guidelines:

1. Use spaces, not tabs.
2. Variable names use camelCase instead of snake_case.
3. All private member variables get an underscore in front of them.
   * Users cannot access these variables directly, so rather they be ugly than the method parameters.
   * Private member functions are exceptions to this.
4. Boolean variable names start with "is".
   * e.g. `isPrimaryKey` and `isUnique` rather than `primaryKey` and `unique`.
   * Exceptions to this include variable names shared by similar classes (e.g. `defaultValue` in the `BooleanField` class).
5. Avoid the use of `this`.
6. Method signatures are made as pretty as possible, meaning full-length words and consistency throughout.
7. All files end on a new line.
8. A blank line is kept open between methods.
9. Curly braces are as follows:
```
if (condition) {
    ...
}
```
10. Spaces are included before opening parentheses or curly braces, e.g. between `if` and `(`, `)` and `{`, etc.
    * An exception to this is the declaration and use functions and classes. 
11. Curly braces should always be used, even when not necessary.
    * e.g. Single-line if-statement, for-loops, etc.
   
