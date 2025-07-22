# Cuber Application
author : Anna Gallone
forked and truncated from : https://github.com/iRed4321/IGLego

Small openGL application to display 3D blocks in a nice window.

Blocks are of an arbitrary dimension of 1 x 1 x 1 (no unit).

The view is centered around (0,0,0).

Coordinates of the blocks should be written in a "data.csv" file stored at the root of this repository.
Coordinates are not checked, so it is up to the person generating the csv file to ensure no blocks are overlapping.


## To compile (on unix based systems)
```bash
# if openGL is not installed yet on your computer
$ sudo apt-get install freeglut3-dev

# then
$ cd pathto/cuber

# if it is the first time you're compiling :
pathto/cuber $ mkdir build

# finally, in any case :
pathto/cuber $ make
```

## To run
```bash
pathto/cuber $ make run
```


## Commands

- '+' to zoom in,
- '-' to zoom out
- 'spacebar' to switch on/off the line mode
- click & drag the image to rotate it
- 'F2' to light the scene even more