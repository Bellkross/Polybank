# Polybank code convetions

## Header Files

### The #define Guard

- All header files should have #define guards to prevent multiple inclusion. The format of the symbol name should be \<FILE>\_H_.
___
    #ifndef FOO_BAR_BAZ_H_
    #define FOO_BAR_BAZ_H_
    // some implementation .. 
    #endif  // FOO_BAR_BAZ_H_


### Forward Declarations

- Avoid using forward declarations where possible. Just #include the headers you need.

### Names and Order of Includes

- Use standard order for readability and to avoid hidden dependencies: Related header, C library, C++ library, other libraries' .h, your project's .h. 
- In dir/foo.cc or dir/foo_test.cc, whose main purpose is to implement or test the stuff in dir2/foo2.h, order your includes as follows:
1. dir2/foo2.h.
2.  A blank line
3. C system files.
4. C++ system files.
5. A blank line
6. Other libraries' .h files.
7. Your project's .h files.

## Scoping

### Namespaces

- Do not use using-directives (e.g. using namespace foo). 

### Local Variables

- Place a function's variables in the narrowest scope possible, and initialize variables in the declaration.
___
    int i;
    i = f();     // Bad -- initialization separate from declaration.

    int j = g();  // Good -- declaration has initialization.
___
    std::vector<int> v;
    v.push_back(1);  // Prefer initializing using brace initialization.
    v.push_back(2);

    std::vector<int> v = {1, 2};  // Good -- v starts initialized.

## Classes

### Doing Work in Constructors

- Avoid virtual method calls in constructors, and avoid initialization that can fail if you can't signal an error.

### Implicit Conversions

- Type conversion operators, and constructors that are callable with a single argument, must be explicit in the class definition. As an exception, copy and move constructors should not be explicit, since they do not perform type conversion. However, implicit conversions can sometimes be necessary and appropriate for types that are designed to transparently wrap other types, and those situations must be discussed between team members.

### Structs vs Classes
- Use a struct only for passive objects that carry data; everything else is a class.

### Inheritance

- All inheritance should be public. If you want to do private inheritance, you should be including an instance of the base class as a member instead (in most cases).

- Do not overuse implementation inheritance. Composition is often more appropriate. Try to restrict use of inheritance to the "is-a" case: Bar subclasses Foo if it can reasonably be said that Bar "is a kind of" Foo.

- Limit the use of protected to those member functions that might need to be accessed from subclasses. Note that data members should be private.

### Operator Overloading

- Define overloaded operators only if their meaning is obvious, unsurprising, and consistent with the corresponding built-in operators.

- Define operators only on your own types. If possible, avoid defining operators as templates, because they must satisfy this rule for any possible template arguments. If you define an operator, also define any related operators that make sense, and make sure they are defined consistently.

### Access Control

- Make classes' data members private, unless they are static const.

### Declaration Order

- Group similar declarations together, placing public parts earlier.

- A class definition should usually start with a `public:` section, followed by `protected:`, then `private:`. Omit sections that would be empty.

- Within each section, generally prefer grouping similar kinds of declarations together, and generally prefer the following order: types (including typedef, using, and nested structs and classes), constants, factory functions, constructors, assignment operators, destructor, all other methods, data members.

- Do not put large method definitions inline in the class definition. Usually, only trivial or performance-critical, and very short, methods may be defined inline. See Inline Functions for more details.

## Functions

### Output Parameters

- Prefer using return values rather than output parameters. If output-only parameters are used they should appear after input parameters.

### Reference Arguments

- All parameters passed by lvalue reference must be labeled const.

## Casting

- Use C++-style casts like static_cast<float>(double_value), or brace initialization for conversion of arithmetic types like int64 y = int64{1} << 42. Do not use cast formats like int y = (int)x or int y = int(x) (but the latter is okay when invoking a constructor of a class type).

## Preincrement and Predecrement

- For simple scalar (non-object) values there is no reason to prefer one form and we allow either. For iterators and other template types, use pre-increment.

## Use of const

- Use const whenever it makes sense

## Friends

- We allow use of friend classes and functions, within reason.

## File Names

- Filenames should be all lowercase and can include underscores (_) or dashes (-). Follow the convention that your project uses. If there is no consistent local pattern to follow, prefer "_".

## Type Names
- Type names start with a capital letter and have a capital letter for each new word, with no underscores: `MyExcitingClass`, `MyExcitingEnum`.

## Variable Names

### Common Variable names
- Camel case.
___
    string tableName;   // OK - camel case.

    string table_name;  // Bad - uses underscore.
    string tablename;   // Bad - all lowercase.

### Class and Struct Data Members

- Data members of classes, both static and non-static, are named like ordinary nonmember variables, but with a preceding underscore.
___
    class TableInfo 
    {
    ...
    private:
    string _tableName;  // OK - underscore at beginning.
    string tablename_;   // Bad.
    static Pool<TableInfo>* _pool;  // OK.
    };

## Constant Names

- Const variables are named with a leading "k" followed by camel case.
___
    const int kConstVariableExample = 11;

## Function Names

- Function names are in camel case and start with a small letter.
___
    add()
    deleteUrl()
    openFileOrDie()

## Enumerator Names

- Enumerators (for both scoped and unscoped enums) should be named like constants.

- The enumeration name, UrlTableErrors (and AlternateUrlTableErrors), is a type, and therefore mixed case.
___
    enum UrlTableErrors 
    {
    kOK = 0,
    kErrorOutOfMemory,
    kErrorMalformedInput,
    };

## Comment Style

- Use the // syntax inside function body and /* */ in other cases.

## Spaces vs Tabs

- Tabs.

## Function Declarations and Definitions

- Return type on the same line as function name, parameters on the same line if they fit. Wrap parameter lists which do not fit on a single line as you would wrap arguments in a function call.

Functions look like this:
___
    ReturnType ClassName::FunctionName(Type par_name1, Type par_name2) 
    {
    DoSomething();
    ...
    }
If you have too much text to fit on one line:
___
    ReturnType ClassName::ReallyLongFunctionName(Type par_name1, Type par_name2,
                                                Type par_name3) 
    {
    DoSomething();
    ...
    }
or if you cannot fit even the first parameter:
___
    ReturnType LongClassName::ReallyReallyReallyLongFunctionName(
        Type par_name1,  // 4 space indent
        Type par_name2,
        Type par_name3) 
    {
    DoSomething();  // 2 space indent
    ...
    }

Unused parameters that are obvious from context may be omitted:
___
    class Foo 
    {
    public:
        Foo(Foo&&);
        Foo(const Foo&);
        Foo& operator=(Foo&&);
        Foo& operator=(const Foo&);
        Foo& objectSize(int width, int height, int length); // non-obvious case
    };

## Function calls

- Wrap parameter lists which do not fit on a single line as you would wrap arguments in a function declaration/definition.

## Conditionals and loops

- Prefer no spaces inside parentheses. The if and else keywords belong on separate lines.
___
    if (condition) {  // no spaces inside parentheses
    ...  // 2 space indent.
    } else if (...) {  // The else goes on the same line as the closing brace.
    ...
    } else {
    ...
    }
___
    for (int i = 0; i < kSomeNumber; ++i) {
        printf("I take it back\n");
    }

- Short conditional statements may be written on one line if this enhances readability. You may use this only when the line is brief and the statement does not use the else clause.
___
    if (x == kFoo) return new Foo();
    if (x == kBar) return new Bar();

- Curly braces are required even for single-line statements.
___
    if (condition) {
        DoSomething();  // 2 space indent.
    } else {
        DoSomething2();
    }

## Pointer and Reference Expressions

- No spaces around period or arrow. Pointer operators do not have trailing spaces.

The following are examples of correctly-formatted pointer and reference expressions:
___
    x = *p;
    p = &x;
    x = r.y;
    x = r->y;

- There are no spaces around the period or arrow when accessing a member.

- Pointer operators have no space after the * or &.

- When declaring a pointer variable or argument, you may place the asterisk adjacent to the type:
___
    char* c;
    const string& str;

## Boolean Expressions

- When you have a boolean expression that is longer than the standard line length (80), break up the lines with logical operators at the end.
___
    if (this_one_thing > this_other_thing &&
        a_third_thing == a_fourth_thing &&
        yet_another && last_one) {
    ...
    }

## Return Values

- Do not needlessly surround the return expression with parentheses.

- Use parentheses in return expr; only where you would use them in x = expr;.
___
    return result;                  // No parentheses in the simple case.
    // Parentheses OK to make a complex expression more readable.
    return (some_long_condition &&
            another_condition);

## Constructor Initializer Lists
- Constructor initializer lists can be all on one line or with subsequent lines indented one tab.

The acceptable formats for initializer lists are:
___
    // When everything fits on one line:
    MyClass::MyClass(int var): some_var_(var) 
    {
        DoSomething();
    }
___
    // If the signature and initializer list are not all on one line:
    MyClass::MyClass(int var):
        some_var_(var), some_other_var_(var + 1) 
    {
        DoSomething();
    }

    // When the list spans multiple lines, put each member on its own line:
    MyClass::MyClass(int var):
        some_var_(var), // 1 tab indent
        some_other_var_(var + 1) // lined up
    {
        DoSomething();
    }
___
    // As with any other code block, the close curly can be on the same
    // line as the open curly, if it fits.
    MyClass::MyClass(int var): some_var_(var) {}

## Horizontal whitespace

### Operators
___
    // Assignment operators always have spaces around them.
    x = 0;
___
    // Other binary operators usually have spaces around them, but it's
    // OK to remove spaces around factors.  Parentheses should have no
    // internal padding.
    v = w * x + y / z;
    v = w*x + y/z;
    v = w * (x + z);
___
    // No spaces separating unary operators and their arguments.
    x = -5;
    ++x;
    if (x && !y)
    ...

### Templates and Casts
___
    // No spaces inside the angle brackets (< and >), before
    // <, or between >( in a cast
    std::vector<string> x;
    y = static_cast<char*>(x);

## Vertical Whitespace

- Minimize use of vertical whitespace.

- This is more a principle than a rule: don't use blank lines when you don't have to. In particular, don't put more than one or two blank lines between functions, resist starting functions with a blank line, don't end functions with a blank line, and be sparing with your use of blank lines. A blank line within a block of code serves like a paragraph break in prose: visually separating two thoughts.

- The basic principle is: The more code that fits on one screen, the easier it is to follow and understand the control flow of the program. Use whitespace purposefully to provide separation in that flow.

- Some rules of thumb to help when blank lines may be useful:

    - Blank lines at the beginning or end of a function do not help readability.
    - Blank lines inside a chain of if-else blocks may well help readability.
    - A blank line before a comment line usually helps readability — the introduction of a new comment suggests the start of a new thought, and the blank line makes it clear that the comment goes with the following thing instead of the preceding.