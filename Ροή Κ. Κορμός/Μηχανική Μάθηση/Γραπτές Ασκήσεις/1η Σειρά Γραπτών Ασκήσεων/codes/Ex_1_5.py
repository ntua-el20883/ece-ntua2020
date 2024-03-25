from PIL import Image, ImageDraw, ImageFont

# Load the image
img_path = '/mnt/data/image.png'
img = Image.open(img_path)

# Prepare to draw on the image
draw = ImageDraw.Draw(img)
font = ImageFont.load_default()

# Annotations to be placed on the image
# (text, xy_position)
annotations = [
    ("(c) Polynomial kernel", (30, 20)),
    ("(e) RBF, tight spread", (250, 20)),
    ("(b) Linear, C=10", (470, 20)),
    ("(a) Linear, C=0.1", (30, 180)),
    ("(d) RBF, larger spread", (250, 180)),
    ("(e) RBF, tight spread", (470, 180))
]

# Draw the annotations on the image
for text, position in annotations:
    draw.text(position, text, (0, 0, 0), font=font)

# Save the annotated image
annotated_img_path = '/mnt/data/annotated_image.png'
img.save(annotated_img_path)
annotated_img_path
