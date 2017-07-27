<img src="https://travis-ci.org/davidbrownza/CORMAP.svg?branch=master" align="right">

# CORMAP
Simple C++ classes for Object Relational Mapping

### Dependencies:
`sudo apt-get install libmysqlcppconn-dev`

### Developer guidelines
Cormap has been developed using the following code guidelines:

1. All private member variables get an underscore in front of them.
   * Users cannot access these variables directly, so rather they be ugly than the method parameters.
   * Private member functions are exceptions to this.
2. Avoid the use of `this->` and `this`.
3. Method signatures are made as pretty as possible, meaning full-length words and consistency throughout.
4. All files end on a new line.
5. A blank line is kept open between methods
6. Curly braces are as follows:
```
if (condition) {
    ...
}
```
7. Spaces are included before opening parentheses or curly braces, e.g. between `if` and `(`, `)` and `{`, etc
   * An exception to this is the declaration and use functions and classes. 
