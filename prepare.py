# code by userElaina

# config consola
import os
dpi=128
ascii_x=15
ascii_y=32
fout_size=26
offset=5
if os.name=='posix':
    f_font='~/test/BadApple/consola.ttf'
else:
    f_font='C:\\test\\BadApple\\1\\consola.ttf'
chars='ascii'
# cmd: offset=5

# preprocess
ascii_x*=dpi
ascii_y*=dpi
fout_size*=dpi
offset*=dpi
f_font=os.path.abspath(f_font)
name=os.path.basename(f_font).split('.')[0].replace(' ','_')
fs_bmp=os.path.join(os.path.dirname(f_font),'temp',name)
os.makedirs(fs_bmp,exist_ok=True)

import string
if chars=='ascii':
    char_list=sorted(string.printable[:-5])
else:
    raise Exception('chars not supported: %s'%chars)

# draw
from PIL import Image,ImageDraw,ImageFont
fnt=ImageFont.truetype(f_font,fout_size)

def draw_ascii(c:str)->None:
    img=Image.new('RGB',(ascii_x,ascii_y),color=(0,0,0))
    d=ImageDraw.Draw(img)
    d.text((0,offset),c,font=fnt,fill=(255,255,255))
    img.save(open(os.path.join(fs_bmp,'%d.bmp'%ord(c)),'wb'))
    print(c,end='',flush=True)

for c in char_list:
    draw_ascii(c)
print()
