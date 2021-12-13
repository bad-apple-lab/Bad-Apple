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
        s1,s2=0,0
        for _i,i in enumerate(img.getdata()):
            if _i<(x*(y>>1)):
                s1+=i[0]
            else:
                s2+=i[0]
        print(c,s2,s1)


for i in '~@':
    j=g(i)
