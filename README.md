# Photo To Ascii
This terminal program uses the stb_image library to convert any image to Ascii Art!!

<img src="https://github.com/yoboyali/Photo-To-Ascii/blob/main/Assets/cover.png"/>

## How It Works

This program is built around the stb_image library, which enables support for common image formats such as PNG, JPG, and JPEG.

1️⃣ Image Loading

The program loads the image file and extracts its pixel data into a raw byte array.

2️⃣ Image Resizing

To match the desired output resolution, the image is downscaled according to user input.
For each output pixel, the program samples a corresponding block of source pixels and computes the average color (box filtering).

This averaging step preserves overall luminance and prevents aliasing artifacts.

3️⃣ Brightness Mapping to ASCII

Each resized pixel is converted to grayscale using a luminance approximation:

```python
int CharIndex = (int)((Average / 255) * CharacterLen - 1);
```

The brightness value is then mapped to an ASCII character from a predefined gradient string (" .-=+*x#$X@"), where:

Darker pixels → denser characters ($, X, @)

Brighter pixels → lighter characters (. , space)

4️⃣ Color Output

If enabled, the program prints each character using ANSI 24-bit RGB escape sequences:

```python
printf("\33[38;2;%d;%d;%dm%c]" , r , g , b ,Characters[CharIndex]);
```

This allows the ASCII characters to retain the original pixel color.

Note: RGB ANSI escape codes require a terminal that supports 24-bit true color.

<img src="https://github.com/yoboyali/Photo-To-Ascii/blob/main/Assets/cover2.png"/>

## Running the Program

1️⃣ Compile

this program can be compiled using the make command.
Navigate to the directory containing the source file and compile it:

```python
make
```

2️⃣ Run

Execute the compiled program by passing the image path as a command-line argument:

```python
./ascii [ImageFilePath.png]
```

Example:

```python
./ascii example.png
```

3️⃣ Resize Option

After launching, the program will prompt you to choose whether you would like to resize the image before converting it to ASCII.

4️⃣ Cleaning the Build Files

After you are finished using the program, you can remove the compiled executable with:

```python
make clean
```

This deletes the generated binary file while leaving your source code intact.

## Credits

This project would not have been possible without this video from Xander Gouws

```python
https://youtu.be/t8aSqlC_Duo?si=K8bgxEIfLrEUVE4M
```



