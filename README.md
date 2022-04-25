# image processor
This project was given as a big homework assignment at the university. Spend not much time on it and maybe some fundamental things could be done better but it works. So you can play with it a little bit :)
_____
## What can image processor do?
Image processor takes .bmp(only .bmp) file and applies some filters on it.


## How does it work?
Image processor gets description and image from .bmp file and does some funny stuff with it.
Also it can apply many filters on one image.


## How to launch image processor?
First you have to build all files with CMake file from repository.

Then add some .bmp files to directory with `image_processor.exe`
Now you can check its functionality by using console:

`<'project directory'>image_processor "input file name" "output file name" "filter name" "filter arguments(if needed)"`

Also you can write `<'project directory'>image_processor` in console to see all the filters templates.

## Filters names and functional
1. "-crop", arguments: {num} {num} - crops image from top left corner. Arguments are height and width of crop in pixels.
2. "-gs" - GrayScale filter
3. "-blur", argument: {num} - Gaussian blur filter. Blurs image by using argument.
4. "-neg" - negative filter
5. "-sharp" - Sharp filter
6. "-edge", argument: {num} - edge filter. Leaves only white edges of some objects on the image.
7. "-distortion", argument: {num} - Applies distortion on image. Argument is width of distorting area in pixels.
