import os
from PIL import Image,ImageDraw,ImageFont
import string

size=128
x=size*15
y=size*32

pth=os.path.abspath(os.path.dirname(__file__))
font=os.path.join(pth,'Fonts','consola.ttf')
fnt=ImageFont.truetype(font,size*26)

def g(c):
    # cmd: i=5
    for i in range(2,8):
        img=Image.new('RGB',(x,y),color=(0,0,0))
        d=ImageDraw.Draw(img)
        d.text((0,size*i),c,font=fnt,fill=(255,255,255))
        img.save(open(os.path.join(pth,'Char','%d_%d.bmp'%(ord(c),i)),'wb'))
    print(repr(c))


for i in sorted(string.printable[:-5]):
    g(i)
