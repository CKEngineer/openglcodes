from PIL import Image

# Open an image file
image_path = 'indir.png'
image = Image.open(image_path)

# Get the RGB values of each pixel
rgb_values = list(image.getdata())
dosya = open('metin_dosyasi.txt', 'w') 

# Print the RGB values of the first few pixels
for pixel in rgb_values:
    dosya.write(f"{pixel[0]},{pixel[1]},{pixel[2]},")
#will write the pixels without \n

dosya.close()
 
