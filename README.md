# NHL95DBEditor

NHL95DBEditor is a console program for editing the database files of EA Sports NHL Hockey 95 for PC.

See the [GitHub page](https://peruukki.github.io/NHL95DBEditor/) for more details.

## Development

Setup for a couple IDEs/editors is included.

### Visual Studio Code (only macOS configuration)

Install at least the [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) extension,
you can find other useful extensions from the
[C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack).

To compile the project:

1. Select some `.c` file as the active file, e.g. [`main.c`](NHL95DBEditor/src/main.c)
2. Click *Terminal > Run Build Task* and choose **Build NHL95DBEditor**.
3. The compiled executable should be in `NHL95DBEditor/target/NHL95DBEditor`.

### XCode (macOS)

Use the XCode project in [`NHL95DBEditor.xcodeproj`](NHL95DBEditor.xcodeproj).

### Visual Studio (Windows)

Several (old) solution files exist:

1. [`NHL95DBEditor/NHL95DBEditor-VS2015.vcxproj`](NHL95DBEditor/NHL95DBEditor-VS2015.vcxproj) for Visual Studio 2015
2. [`NHL95DBEditor/NHL95DBEditor.vcxproj`](NHL95DBEditor/NHL95DBEditor.vcxproj) for Visual Studio Express 2013
3. [`NHL95DBEditor/NHL95DBEditor.vcproj`](NHL95DBEditor/NHL95DBEditor.vcproj) for Visual Studio Express 2012 or older (?)
