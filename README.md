For installation via Docker, follow the directions below.

Docker ps : gives you what container you’re running in and a number of related details

Docker cp: copies a file and then if you give a second path, it will copy the first path into the second path.

Current steps for loading a dev environment via Docker with MacieK SGDK:https://hub.docker.com/r/maciekbaron/sgdk
create the docker container with your CLI: docker pull maciekbaron/sgdk

Then run the container via docker:
docker run -it maciekbaron/sgdk 

Then install nano to create a text editor:
apt install nano

Navigate to the gendev folder:
cd gendev

Create a project_dir folder: 
mkdir project_dir

Then inside of your project_dir folder, create a src and out folder where all of your code will live:
cd project_dir
mkdir src 
mkdir out 

Then navigate back to your gendev/sgdk/SGDK folder:
cd /gendev/sgdk/SGDK

Then you want to copy and past the inc folder into your project_dir: 
cp -R inc/ /gendev/project_dir

Then navigate back into your gendev/project_dir folder:
cd /gendev/project_dir

Then navigate to your src folder and start adding your code there: 
For example you can do: cd src
nano main.c - then use sgdk functions to build text to display on the screen - see below for example:
#include <genesis.h>

int main (){
        VDP_drawText("Hello World”, 14, 12);
        while(1){
                VDP_waitVSync();
        }
        return (0);
}

Then navigate back out to your project_dir folder and use the below command to compile everything in your out folder: 
make -f $GENDEV/sgdk/mkfiles/makefile.gen clean all

You can then manage your files using the remote explorer extension via VS Code. To do so, click on remote explorer in VS Code and then right click the running container and click on “Open in new window” to pick what parent director you’re going to work out of
