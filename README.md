# BugDepth
Create a sharp image from a set of purposefully unsharp images :)

##How to build

to run the app you need 

- cmake 3.1 and up
- gcc that supports c++14, I have 5.4.0
- qt 5.10.1 and up

Then please follow this:
1. Set Qt5_DIR in build.sh
2. Run build.sh, it builds the project
3. I think you already get how to turn off the tests (look in build.sh)
4. To run the app, just run the binary in ./build/src/bugDepth

Results are in res/result/.

## Algorithm idea

I concluded, that the parts in focus would have more edges than parts not in focus.
So, I found edges with sobel algorithm and then copied all the edges to a blank image.
After that I added the background image to fill the void parts.

As for the depth map, it has not a lot of gradation, because I just run the sobel on
the resulting image again.

## Remarks

I did use QImage, but it's basically a wrapper around uchar\* to data, width, height 
and format of  image, so it will be easy to add my custom Img class to do it, I just 
don't have much time left to do this.

Also, I figured out how to turn 32bpp RGBA to 8bpp grayscale -- the easiest way is to
get the (r + g + b + a)/4, I've started to do this on branch develop.

Thank you for the challenge, I really had a lot of fun.
