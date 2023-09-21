from PIL import Image
dosya = open('glpyhs_textures.txt', 'w') 
# Open an image file
alphabet_list= {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","space"}
numbers_and_point_list = {"0","1","2","3","4","5","6","7","8","9","point"}
turkish_letters_and_two_ponints = {"twopoint",
                                   "turkish_c","turkish_g","turkish_i","turkish_o","turkish_s","turkish_u",
                                   "turkishC","turkishG","turkishO","turkishS","turkishU"}

sizeofnumbers = len(numbers_and_point_list)
sizeofarray = len(alphabet_list)
sizeofturkish = len(turkish_letters_and_two_ponints)

for alphabet in range(sizeofturkish):
    variable_alphabet = turkish_letters_and_two_ponints.pop()
    image_path = f'{variable_alphabet}.png'
    image = Image.open(image_path)
    # Get the RGB values of each pixel
    rgb_values = list(image.getdata())
    # Print the RGB values of the first few pixels
    dosya.write(f"\nunsigned char {variable_alphabet}[]\n")
    dosya.write("{")
    for pixel in rgb_values:
        dosya.write(f"{ round((pixel[0] * 0.2126) + (pixel[1]*0.7152) +(pixel[2]*0.0722)) },")
    dosya.write("};")

#will write the pixels without \n

dosya.close()
 
