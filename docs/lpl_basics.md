
# Lena Programming Language Documentation

## Introduction

Lena is an intellectually dynamically typed programming language that operates as if it were statically typed. This design allows developers to define variables using two main methods: automatic type inference and manual type specification.

## Data Types

### Primitive Data Types

#### Integers

- **Automatic Type Inference:**

  ```lena
  a = 10
  ```

  In this case, the variable `a` is automatically inferred to be of type `i8` to optimize for resource efficiency, assuming the variable is immutable.

- **Manual Type Specification:**

  ```lena
  a:i32 = 10
  ```

#### Strings

- **Manual Type Specification:**

  ```lena
  a:str = "Hello Lena!"
  ```

  Lena automatically decides whether to use references or value passing, optimizing for performance and resource usage.

### Complex Data Types

#### Arrays

- **One-dimensional Arrays:**

  ```lena
  a = [1, 2, 3, 4]
  ```

- **Multi-dimensional Arrays:**

  ```lena
  a = [[1, 2], [3, 4]]
  ```

  The array syntax is similar to that of Julia.

#### Tuples

- **Automatic Type Inference:**

  ```lena
  a = (45, "Hello!", [123, 345, 535])
  ```

- **Manual Type Specification:**

  ```lena
  a:(i32, str, i32[3]) = (45, "Hello!", [123, 345, 535])
  ```

## Syntax

Lena does not require semicolons at the end of statements, which allows for a cleaner and more readable syntax.

## Conclusion

Lena offers a flexible yet efficient way to handle data types, allowing developers to choose between automatic type inference and manual type specification. Its design ensures optimal performance while maintaining simplicity and ease of use.
