from PIL import Image

# Open an image file
image_path = 'indir.png'
image = Image.open(image_path)

# Get the RGB values of each pixel
rgb_values = list(image.getdata())
dosya = open('metin_dosyasi.txt', 'w') 

rgba_values = [((r, g, b, a) if image.mode == 'RGBA' else (r, g, b))
               for r, g, b, a in rgb_values]

# Print the RGB values of the first few pixels
for pixel in rgb_values:
    dosya.write(f"{pixel[0]},{pixel[1]},{pixel[2]},\n")


dosya.close()
 