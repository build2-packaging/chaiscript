<h1 align="center">
    build2 Package for ChaiScript
</h1>

<p align="center">
    <a href="https://chaiscript.com/index.html">ChaiScript</a> is a header-only C++ embedded scripting language loosely based on ECMA script. It is designed for ease of use and tight integration with C++.
</p>

<p align="center">
    <a href="https://chaiscript.com/index.html">
        <img src="https://img.shields.io/website/https/chaiscript.com/index.html.svg?down_message=offline&label=Official&style=for-the-badge&up_color=blue&up_message=online">
    </a>
    <a href="https://github.com/build2-packaging/chaiscript">
        <img src="https://img.shields.io/website/https/github.com/build2-packaging/chaiscript.svg?down_message=offline&label=build2&style=for-the-badge&up_color=blue&up_message=online">
    </a>
    <a href="https://cppget.org/chaiscript">
        <img src="https://img.shields.io/website/https/cppget.org/chaiscript.svg?down_message=offline&label=cppget.org&style=for-the-badge&up_color=blue&up_message=online">
    </a>
    <a href="https://queue.cppget.org/chaiscript">
        <img src="https://img.shields.io/website/https/queue.cppget.org/chaiscript.svg?down_message=empty&down_color=blue&label=queue.cppget.org&style=for-the-badge&up_color=orange&up_message=running">
    </a>
</p>

## Usage
The dependency to the package `chaiscript` in your `manifest` file should look like the following.

    depends: chaiscript ^ 6.1.0

It provides several targets for importation.
The header-only C++ library to use ChaiScript as an embedded language can be imported by the following declaration in the `buildfile`.

    import chaiscript = chaiscript%lib{chaiscript}

To import the dynamically loadable module which provides the standard library for a ChaiScript instance, do the following.

    import chaiscript_stdlib += chaiscript%lib{chaiscript_stdlib}

Also, using the `chai` interpreter for ChaiScript as build-time dependency with immediate importation is supported.

    import! [metadata] chai = chaiscript%exe{chai}

## Configuration

## Issues
- Some tests are not compilable or runnable (catch2 compile error, build2 error reading multiline strings).
- Not all tests have been wrapped.
- To fix the strange inclusion scheme of the statically generated libraries `parser` and `stdlib`, their content actually needed to be copied and adjusted.
- Currently, multithreading is not handled correctly.
- The build2 testscript dependencies are fully provided, which results in an error when only running `b test`.
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
