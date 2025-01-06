# Conventions

## Naming

- Files: `snake_case`.
- Folders: `snake_case`.
- Macros: `UPPER_SNAKE_CASE`.
- Constants: `UPPER_SNAKE_CASE`.
- Structs: `snake_case`.
- Struct members: `snake_case`.
- Unions: `snake_case`.
- Enums: `snake_case`.
- Enum members: `UPPER_SNAKE_CASE`.
- Functions: `snake_case`.
- Private (static) functions: `prv_snake_case`, `prv_` name prefix [^1].
- Parameters: `snake_case`.
- Variables: `snake_case`.
- Namespaces: `NS_`, a short prefix, usually 1-3 characters, followed by an underscore [^2].

**Notes:**
- Do not use `__` or `_` prefix for variables, functions, macros and types [^1]. They are used by the compiler and standard library. Here's what [the C standard](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf) says (section 7.1.3) [^3]:
  > - All identifiers that begin with an underscore and either an uppercase letter or another underscore are always reserved for any use.
  > - All identifiers that begin with an underscore are always reserved for use as identifiers with file scope in both the ordinary and tag name spaces.
- Do not use `typedef` for structures and pointers.

[^1]: [General rules | MaJerle/c-code-style: Recommended C style and coding rules](https://github.com/MaJerle/c-code-style?tab=readme-ov-file#general-rules)
[^2]: [Codebase Introduction | EpicGamesExt/raddebugge: The RAD Debugger Project](https://github.com/EpicGamesExt/raddebugger?tab=readme-ov-file#codebase-introduction)
[^3]: [use _ and __ in C programs](https://stackoverflow.com/a/25090719)
