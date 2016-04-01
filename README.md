# ofxLSystem

This addon has a dependency on [ofxLSystemGrammar](https://github.com/edap/ofxLSystemGrammar). Download it and add it to your addon folder

ofxLSystem is a 3D graphic turtle graphic interpretation of L-Syestems. In the readme of ofxLSystemGrammar you can find some information about L-System.
This addon can be used to generate meshes as the following ones:

![example](img/violet.png)
![example](img/green.png)
![example](img/yellow.png)

## Examples

- *guiExample* contains ~10 differents L-Systems, with a GUI to change colors,
  rotation angle, n steps ecc. It saves the settings for each tree on
  a separate xml file
- ** It use a `vector<ofxLSystem>` to create a forest. It uses internally 
