# code by userElaina

# conf
import os
if os.name=='posix':
    f_video='~/test/BadApple/1080p.mp4'
else:
    f_video='C:\\test\\BadApple\\1\\1080p.mp4'

# preprocess
f_video=os.path.abspath(f_video)
name=os.path.basename(f_video).split('.')[0].replace(' ','_')
fs_frame=os.path.join(os.path.dirname(f_video),'temp',name)
os.makedirs(fs_bmp,exist_ok=True)

import subprocess

def ffprobe(pth)->float:
    order='ffprobe -v quiet -print_format json -show_format -show_streams "%s">"%s"'%(pth,file_json)
    subprocess.call(order,shell=True)
    j=json.load(open(file_json,'rb'))
    return j['streams'][0]['nb_frames'],j['streams'][0]['duration']

def frame(pth,fps=None):
    order='ffmpeg -i "%s" '%pth
    if fps:
        order+='-vf fps=%d '%fps
    order+='"%s"'%file_frame
    subprocess.call(order,shell=True,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)
    return order

vpth=os.path.join(PTH,'Video',"1080p.mp4")
print(ffprobe(vpth))
print(frame(vpth))
# ffprobe -show_streams -select_streams v ./1080p.mp4 2>&1 | grep -E 'duration=|nb_frames=' | awk -F= '{print $2}' > 2.txt