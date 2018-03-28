# BugDepth
Create a sharp image from a set of purposefully unsharp images :)

## How to build

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
So, I found edges with sobel algorithm and then copied all the edges to a blank image,
and, to achieve better quality I copied all the neighbour pixels, like this

```
-----------------------------
left-up   |    up   |  right-up
left      |  match! |  right
left-down |   down  |  right-down
-----------------------------
```

After that I added the background image to fill the void parts.

As for the depth map, I did essentially the same, looked through images from
back to front, searched for edges and gradually increased the depth color.

## Remarks

I added my custom Img class to handle images to achieve your no-additional-lib
requirement.

Thank you for the challenge, I really had a lot of fun.
