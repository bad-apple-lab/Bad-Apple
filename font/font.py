import os
import string
from PIL import Image, ImageDraw, ImageFont, ImageStat

# config consola
dpi = 128
x_ascii = 15
y_ascii = 32
fout_size = 26
offset = 5
f_font = './consola.ttf'
char_type = 'ascii'
# cmd: offset=5

# preprocess
x_ascii *= dpi
y_ascii *= dpi >> 1
fout_size *= dpi
offset *= dpi
fnt = ImageFont.truetype(f_font, fout_size)

list_ascii = sorted(string.printable[:-5])

if char_type == 'ascii':
    None
else:
    raise Exception('Unsupported char type: %s' % char_type)

ans_ascii = dict()
max_ascii = 0
min_ascii = 255
for c in list_ascii:
    i = Image.new('L', (x_ascii, y_ascii))
    d = ImageDraw.Draw(i)
    d.text((0, offset), c, font=fnt, fill=255)
    l = ImageStat.Stat(i).mean[0]
    max_ascii = max(max_ascii, l)
    min_ascii = min(min_ascii, l)

    i = Image.new('L', (x_ascii, y_ascii))
    d = ImageDraw.Draw(i)
    d.text((0, offset - y_ascii), c, font=fnt, fill=255)
    r = ImageStat.Stat(i).mean[0]
    max_ascii = max(max_ascii, r)
    min_ascii = min(min_ascii, r)

    ans_ascii[c] = (l, r)
    print(c, l, r, flush=True)

print()

lc_ascii = max_ascii-min_ascii
for k in ans_ascii:
    ans_ascii[k] = ((ans_ascii[k][0]-min_ascii)/lc_ascii*255,
                    (ans_ascii[k][1]-min_ascii)/lc_ascii*255)

ans_65536 = list()
for i in range(256):
    ans_256 = ''
    for j in range(256):
        ans_ = ''
        d = 512
        for k in ans_ascii:
            _d = abs(ans_ascii[k][0] - i) + abs(ans_ascii[k][1] - j)
            if _d < d:
                ans_ = k
                d = _d
        ans_256 += ans_
    ans_65536.append(ans_256)

s = '#pragma once\n\nchar map65536[0x100][0x101]={'
for i in ans_65536:
    s += '\n    "'+i.replace('\\', '\\\\').replace('"', '\\"')+'",'
s = s[:-1]+'\n};\n'

open(os.path.join(os.path.dirname(os.path.abspath(f_font)), os.path.basename(
    f_font).rsplit('.', 1)[0]+'_'+char_type+'_0_ff.h'), 'w').write(s)
