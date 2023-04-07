ff


Before you clone this repo and get coding you need to setup a local dev environment and all the env required for SGDK as well as associated toolchains.

To setup a env and a local dev. environment, please follow the instructions on [marsdev](https://github.com/andwn/marsdev). 

After marsdev has been installed and setup, you need to replace the contents of [SGDK](https://github.com/Stephane-D/SGDK) with the latest contents of SGDK from the repo. 

Finally clone this repo in your desired project directory within marsdev, and you should be all set to utilize make files and compile your build!

### The following instructions are for Mac OS only. 

After each build compilation, if you want to run your compiled ROM using [OpenEmu](https://openemu.org/) from the terminal to make things easier. Please edit the ```openemu.sh``` to include the file path of where your compiled rom lives. See below for reference.

```
open -a OpenEmu "add the exact filepath of where your rom lives inside these quotes"
```

After you've set your filepath, simply run the ```openemu.sh``` file in your desired terminal. For example, if you're working with VSCode, you can right-click the file and choose "Run Code" and it should run the rom in OpenEmu. 
