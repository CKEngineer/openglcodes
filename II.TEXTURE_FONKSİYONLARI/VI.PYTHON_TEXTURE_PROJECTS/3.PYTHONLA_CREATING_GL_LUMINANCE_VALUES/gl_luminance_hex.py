from PIL import Image

# Open an image file
image_path = 'varyometre_jpeg.jpg'
image = Image.open(image_path)

# Get the RGB values of each pixel
rgb_values = list(image.getdata())
dosya = open('varyometre.txt', 'w') 

counter = 0
for pixel in rgb_values:
   dosya.write(f"{ hex(round((pixel[0] * 0.2126) + (pixel[1]*0.7152) +(pixel[2]*0.0722))) },")
   if(counter % 100 == 99):
      dosya.write("\r")
   counter = counter + 1

dosya.close()
 
