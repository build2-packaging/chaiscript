# build2 Packages for ChaiScript Library and Interpreter

[ChaiScript](https://chaiscript.com/index.html) is a header-only C++ embedded scripting language loosely based on ECMA script. It is designed for ease of use and tight integration with C++.

[![Official](https://img.shields.io/website/https/chaiscript.com/index.html.svg?down_message=offline&label=Official&style=for-the-badge&up_color=blue&up_message=online)](https://chaiscript.com/index.html)
[![build2](https://img.shields.io/website/https/github.com/build2-packaging/chaiscript.svg?down_message=offline&label=build2&style=for-the-badge&up_color=blue&up_message=online)](https://github.com/build2-packaging/chaiscript)
[![cppget.org](https://img.shields.io/website/https/cppget.org/chaiscript.svg?down_message=offline&label=cppget.org&style=for-the-badge&up_color=blue&up_message=online)](https://cppget.org/chaiscript)
[![queue.cppget.org](https://img.shields.io/website/https/queue.cppget.org/chaiscript.svg?down_message=empty&down_color=blue&label=queue.cppget.org&style=for-the-badge&up_color=orange&up_message=running)](https://queue.cppget.org/chaiscript)

## Usage
The [original ChaiScript repository](https://github.com/ChaiScript/ChaiScript) has been split into multiple build2 packages to allow for the greater flexibility.
Mainly `libchaiscript` is used to get access to the header-only library and the ChaiScript standard library module that can be loaded at runtime.
The package `chaiscript` makes ChaiScript's own interpreter `chai` available to be used.
`chaiscript-stdlib` exports the compiled and dynamically loadable standard library module for the basic ChaiScript engine.
Typically, you will not need to use it.

Make sure to add the stable `cppget.org` repositories to your project's `repositories.manifest` to be able to fetch the packages.

    :
    role: prerequisite
    location: https://pkg.cppget.org/1/stable
    # trust: ...

Add the respective dependencies in your project's `manifest` file to make those packages available for import.
Hereby, all packages should use the same version constraint.

    depends: libchaiscript ^ 6.1.0
    # or
    depends: { libchaiscript chaiscript chaiscript-stdlib } ^ 6.1.0

The header-only C++ library to use ChaiScript as an embedded language can be imported by the following declaration in the `buildfile`.

    import chaiscript = libchaiscript%lib{chaiscript}

Using the `chai` interpreter for ChaiScript scripts, as a REPL, or as build-time dependency with immediate and standard importation is supported.
Because it is not able to change the code of `chai`, there is no way for now to provide any metadata in the executable.

    import chai = chaiscript%exe{chai}
    # or
    import! chai = chaiscript%exe{chai}

To import the dynamically loadable module which provides the standard library for a ChaiScript instance, we need to rely on metadata.
A dynamic module should not be linked to your executable but instead loaded at runtime.
Hence, to use it properly for running ChaiScript scripts for tests or other things, you would need the module as a prerequisite but only use its directory as input.
This can be accomplished by immediate importation with metadata support.

    import! [metadata, rule_hint=cxx.link] \
        stdlib_module = chaiscript-stdlib%libs{chaiscript_stdlib}
    stdlib_dir = $($stdlib_module: chaiscript_stdlib.dir)

## Configuration

<!-- ### Installation of the Standard Library Module
To be able to automatically find the standard library, its installation directory should also follow the patterns given by the implementation of ChaiScript itself where it seems to be basically hardcoded.
To not run into problems with the `pkg-config` files and other methods to reimport the `chaiscript_stdlib` module, we leave this part up to configuration.
The following option is the recommended way of configuring the install command inside the `config.build` file that lies in the `build` directory of your project's configuration.

    config.install.lib = exec_root/lib/chaiscript/
 -->
### Multithread Support
Multithread support is unconditionally enabled by default and may be turned off.

    config [bool] config.libchaiscript.multithread_support_enabled ?= true

### Dynamic Module Loading
The support to dynamically load ChaiScript modules is unconditionally enabled by default and may be turned off.

    config [bool] config.libchaiscript.dynload_enabled ?= true

### Use of GNU readline
For now, the use of the GNU `readline` library for the ChaiScript interpreter `chai` is unconditionally disabled by default.
This is mainly the case to remove system dependencies for CI.
If `readline` is available on the system, we recommend to enable it.

    config [bool] config.chaiscript.use_readline ?= false


## Issues
<!-- - The installation path of `chaiscript_stdlib` is basically hardcoded. Look into `libchaiscript/chaiscript_stdlib/buildfile` for some notes what could be changed. -->
- ChaiScript is not made for C++20 and higher language standards. As the library is header-only, we do not restrict the language standard of the library package `libchaiscript` but instead keep it to be `cxx.std = latest`. This may result in compilation errors in a project that uses ChaiScript, such as it has been with its own samples and tests. In those, we are forcing the C++17 standard to get rid of most of these errors.
- In nearly all configurations, a lot of warnings are emitted when building libraries or tests. We should not disable them to be aware of potential problems, though.
- Some CI configurations exhibit the `inconsistent C++ compiler behavior` error. As other configurations quite fine with this package, this might be the result from compiler bugs when preprocessing raw string literals.
- Using Clang on Windows with MSVC, the object copy count test given in the `compiled_tests.cpp` file fails due to the wrong number of destructor and move calls. This is most likely an implementation issue of ChaiScript.
- This package does not build or execute the `fuzzer` test.
- This package does not build or execute the performance tests because `valgrind` would be needed.
- Not all unit tests based on ChaiScript scripts are sucessfull when using Clang with `libc++`. This seems to be an implementation issue of the ChaiScript library itself.
- To fix the strange inclusion scheme of the statically generated libraries `parser` and `stdlib`, their content actually needed to be copied and adjusted.
- If there would ever be a new version, check against new script files for testing and adjust all the symbolic links.

## Contributing
Thanks in advance for your help and contribution to keep this package up-to-date.
For now, please, file an issue on [GitHub](https://github.com/build2-packaging/chaiscript/issues) for everything that is not described below.

### Recommend Updating Version
Please, file an issue on [GitHub](https://github.com/build2-packaging/chaiscript/issues) with the new recommended version.

### Update Version by Pull Request
1. Fork the repository on [GitHub](https://github.com/build2-packaging/chaiscript) and clone it to your local machine.
2. Run `git submodule init` and `git submodule update` to get the current upstream directory.
3. Inside the `upstream` directory, checkout the new library version `X.Y.Z` by calling `git checkout vX.Y.Z` that you want to be packaged.
4. If needed, change source files, `buildfiles`, and symbolic links accordingly to create a working build2 package. Make sure not to directly depend on the upstream directory inside the build system but use symbolic links instead.
5. Test if the packages compile and execute examples and tools.
6. Update library version in all `manifest` files if it has changed or add package update by using `+n` for the `n`-th update.
7. Make an appropriate commit message by using imperative mood and a capital letter at the start and push the new commit to the `master` branch.
8. Run `bdep ci` and test for errors.
9. If everything works fine, make a pull request on GitHub and write down the `bdep ci` link to your CI tests.
10. After a successful pull request, we will run the appropriate commands to publish a new package version.

### Update Version Directly if You Have Permissions
1. Inside the `upstream` directory, checkout the new library version `X.Y.Z` by calling `git checkout vX.Y.Z` that you want to be packaged.
2. If needed, change source files, `buildfiles`, and symbolic links accordingly to create a working build2 package. Make sure not to directly depend on the upstream directory inside the build system but use symbolic links instead.
3. Test if the packages compile and execute examples and tools.
4. Update library version in all `manifest` files if it has changed or add package update by using `+n` for the `n`-th update.
5. Make an appropriate commit message by using imperative mood and a capital letter at the start and push the new commit to the `master` branch.
6. Run `bdep ci` and test for errors and warnings.
7. When successful, run `bdep release --tag --push` to push new tag version to repository.
8. Run `bdep publish` to publish the package to [cppget.org](https://cppget.org).
