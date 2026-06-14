# NHL95DBEditor

NHL95DBEditor is a console program for editing the database files of EA Sports NHL Hockey 95 for PC.

See the [GitHub page](https://peruukki.github.io/NHL95DBEditor/) for more details.

## Development

Setup for a couple IDEs/editors is included.

### IDE support

#### Visual Studio Code (only macOS configuration)

Install at least the [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) extension,
you can find other useful extensions from the
[C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack).

To compile the project:

1. Select some `.c` file as the active file, e.g. [`main.c`](NHL95DBEditor/src/main.c)
2. Click *Terminal > Run Build Task* and choose **Build NHL95DBEditor**.
3. The compiled executable should be at `NHL95DBEditor/target/NHL95DBEditor`.

#### Visual Studio (Windows)

Use [`NHL95DBEditor-VS2015.sln`](NHL95DBEditor-VS2015.sln) for Visual Studio 2015 and newer.

### Code formatting

Most IDEs should support the project's [`.clang-format`](.clang-format) configuration.

However, Visual Studio's smart indenting may interfere with desired indentation, but you can turn it off via
_Tools > Options > Languages > C/C++ > Tabs > Indenting_ by switching from _Smart_ to _Block_.

You can also format all files on the command line. For example, if you have Node.js installed:

```shell
npx clang-format -i NHL95DBEditor/src/*.c NHL95DBEditor/src/*.h
```

The current files have been formatted with clang-format version 15.0.0.

## Resources

The [`NHL95DBEditor/res`](NHL95DBEditor/res) directory contains some possibly useful files:

- The original game database files (`*.DB`)
- Exported player attribute files for further analysis (`*.csv` and `*.json`)
