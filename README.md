# sos

A **C++20 header-only library** to automate runtime checks using the type system. An official documentation and guide on how to use this library are in development.


## Features

- [x] Predicates library
- [x] Polimorphic **"check"** function with tag dispatched error handling policies
- [x] Wrapper type **"checked"** to automatically check construction and assignments
- [ ] Specialization type **"checked_with"** to add a default policy used by "checked"
- [ ] Types **"required"** and **"required_with"** to prevent null assignments at compile time
- [ ] Commonly used type aliases like **"required_unique_ptr"** and **"required_string"**


## Build and install

### Copying header files

Since this is a header-only library, the simplest way to embed it in a project is to copy the [sos/](include/sos/) directory under [include/](include/), which contains all the header files, to the include directory of the project and make sure to compile with the **C++20 standard** or later.

### Using CMake

Alternativelly, this project has a [CMakeLists.txt](CMakeLists.txt) file that sets the required configurations for using the library. Because of that, it is possible to add this repository as a **git submodule** in your project and include it as a CMake subdirectory.

The easiest way to unit test this library is to use CMake. To generate build instructions for the tests, use CMake with the variable **SOS_BUILD_TESTS** set to **ON**. After building the targets, use **CTest** to run the test cases.

Under the [scripts/](scripts/) directory, there are scripts to generate build files with Cmake, build the targets, run the tests and clean the build files.

```shell
# Using the Linux scripts to build and run unit tests
./generate.sh ON # The ON parameter sets SOS_BUILD_TESTS
./build.sh
./test.sh
```

> **Note:** Currently, there are no build scripts for Windows


## About this project

### Why C++20

The C++20 [concepts](https://en.cppreference.com/w/cpp/language/constraints) feature allows the implementation to have compile-time guarantees that instantiated objects will behave as expected. Although compiler error messages are still not as clear as we hoped, the error will occur at the instantiation site rather than in the middle of an internal template, facilitating development and debugging.

### Design decisions

In other libraries, similar features, such as [GSL's not_null](https://github.com/microsoft/GSL/blob/main/include/gsl/pointers), decide what error handling mechanism to use based on macro definitions. This approach is limited because it not only restricts the code to always use the same handler, but it could also force a dependent library to make this decision instead of their final users.

To avoid this issue, this library defines the basic **"checked"** and **"required"** types that could be used by other libraries without choosing an error handler as long as they don't perform construction or assignment from non-checked types. At the same time, the end-user code could instantiate the **"checked_with"** and **"required_with"** specializations to use checks without having to specify the policy multiple times.

### Downsides

To boost performance, copies and moves between a **"checked"** type don't call **"check"** or add an invalidated flag. For this reason, use after move is still undefined behavior if the underlying type doesn't have protection for it.

The wrappers defined in this library also don't have any knowledge about ownership, so using raw **"required_ptr"** types would require manual resource cleaning and could lead to leaks.

### Future

Currently, this is a header-only library mainly because of the easy integration, but once C++20 [modules](https://en.cppreference.com/w/cpp/language/modules) become widely supported by compilers and build systems, it could be an alternative option with potentially faster compilation times.

The C++23 standard adds the option to create [static operator()](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p1169r4.html). Once this feature is widely supported by compilers, it could be used by all predicates defined in this library to further optimize them.

If the [contracts proposal](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2695r0.pdf) (hopefully) gets into the C++ standard, this library will become obsolete since contracts would be a standard and more general way of achieving the same goals, but until then, development continues.
