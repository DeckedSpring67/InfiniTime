# Fonts

* [Jetbrains Mono](https://www.jetbrains.com/fr-fr/lp/mono/)
* [Awesome font from LVGL](https://lvgl.io/assets/others/FontAwesome5-Solid+Brands+Regular.woff)

## Generate the fonts:

* Open the [LVGL font converter](https://lvgl.io/tools/fontconverter)
* Name : jetbrains_mono_bold_20
* Size : 20
* Bpp : 1 bit-per-pixel
* Do not enable font compression and horizontal subpixel hinting
* Load the file `JetBrainsMono-Bold.tff` and specify the following range : `0x20-0x17f, 0x410-0x44f` (end the first range with 0x7f if you're not interested in euro symbols) 
* Add a 2nd font, load the file `FontAwesome5-Solid+Brands+Regular.woff` and specify the following
  range : `0xf293, 0xf294, 0xf244, 0xf240, 0xf242, 0xf243, 0xf241, 0xf54b, 0xf21e, 0xf1e6, 0xf54b, 0xf017, 0xf129, 0xf03a, 0xf185, 0xf560, 0xf001, 0xf3fd, 0xf069, 0xf1fc, 0xf45d, 0xf59f, 0xf5a0, 0xf029, 0xf027, 0xf028, 0xf6a9, 0xf04b, 0xf04c, 0xf048, 0xf051, 0xf095, 0xf3dd, 0xf04d, 0xf2f2, 0xf024, 0xf252`
* Click on Convert, and download the file `jetbrains_mono_bold_20.c` and copy it in `src/DisplayApp/Fonts`

Add new symbols:

* Browse the [cheatsheet](https://fontawesome.com/cheatsheet/free/solid) and find your new symbols
* For each symbol, add its hex code (0xf641 for the 'Ad' icon, for example) to the *Range* list (Remember to keep this
  readme updated with newest range list)
* Convert this hex value into a UTF-8 code
  using [this site](http://www.ltg.ed.ac.uk/~richard/utf-8.cgi?input=f185&mode=hex)
* Define the new symbols in `src/displayapp/screens/Symbols.h`:

```
static constexpr const char* newSymbol = "\xEF\x86\x85";
```

#### Navigation font

To create the navigtion.ttf I use the web app [icomoon](https://icomoon.io/app)
this app can import the svg files from the folder *src/displayapp/icons/navigation/unique* and creat a ttf file the
project for the site is *lv_font_navi_80.json* you can import it to add or remove icons

You can also use the online LVGL tool to create the .c

ttf file : navigation.ttf name : lv_font_navi_80 size : 80px Bpp : 2 bit-per-pixel range : 0xe900-0xe929

$lv_font_conv --font navigation.ttf -r '0xe900-0xe929' --size 80 --format lvgl --bpp 2 --no-prefilter -o
lv_font_navi_80.c

#### I use the method above to create the other ttf
