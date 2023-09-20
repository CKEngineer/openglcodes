from PIL import Image

# Open an image file
image_path = 'asel.png'
image = Image.open(image_path)

# Get the RGB values of each pixel
rgb_values = list(image.getdata())
dosya = open('asel.txt', 'w') 

for pixel in rgb_values:
  dosya.write(f"{pixel[0]},{pixel[1]},{pixel[2]},")

dosya.close()
 
