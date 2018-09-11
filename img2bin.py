import sys
from pathlib import Path
from PIL import Image

if len(sys.argv) > 1:
    path = sys.argv[1]
else:
    path = str(Path.home()) + "/Sourcetree/fan-display/img/nudes.png"

im = Image.open(path)
px = im.load()

print("Image Size: " + str(im.size))

lines = []
for w in range(0, im.size[0]):
    line = 0
    for h in range(0, im.size[1]):
        line += 1 << h if px[w, h][0] == 0 else 0
    lines.append(line)

print("Array: " + str(lines))
