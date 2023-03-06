To work with the latest version of SGDK please visit the below link and clone the SGDK repo into your desired file directory: 

https://github.com/Stephane-D/SGDK

Once the repo has been cloned, create a Projects folder in the SGDK-MASTER folder. 

```mkdir Projects```

Finally clone this repo in your Projects folder: 

```git clone https://github.com/izzy1090/adventure-rpg.git```

Once you've cloned the repo in your Projects folder you're ready to test the build and compile it with Docker. If you don't have Docker installed please visit this [link](https://www.docker.com/) to install Docker.

To build the SGDK image run this command: 

```docker build -t sgdk .```

Then navigate to the Projects folder and then into your project session: 

```cd Projects```

```cd (project session name)```

You're almost ready, now while in your Project Session Name directory run the below command to compile your project! 

```docker run --rm -v "$PWD":/src sgdk```

If you're going to build your own project from scratch I encourage you to refer to the SGDK repository for instructions on how to build your own. However because that's not what we're here for, I'm not going to discuss that in this ReadMe.
