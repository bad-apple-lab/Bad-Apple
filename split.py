import os
import json
import subprocess

PTH=os.path.dirname(__file__)
dir_frame=os.path.join(PTH,'Frame')
os.makedirs(dir_frame,exist_ok=True)
file_framelog=os.path.join(dir_frame,'frame.log')
file_frame=os.path.join(dir_frame,'%d.bmp')

file_json=os.path.join(PTH,'v.json')
file_conf=os.path.join(PTH,'v.conf')

def ffprobe(pth)->float:
    order='ffprobe -v quiet -print_format json -show_format -show_streams "%s">"%s"'%(pth,file_json)
    subprocess.call(order,shell=True)
    j=json.load(open(file_json,'rb'))
    open(file_conf,'wb').write(('%s %s\n'%(j['streams'][0]['nb_frames'],j['streams'][0]['duration'])).encode('utf8'))
    return j['streams'][0]['width'],j['streams'][0]['height'],eval(j['streams'][0]['r_frame_rate'])

def frame(pth,fps=None):
    order='ffmpeg -i "%s" '%pth
    if fps:
        order+='-vf fps=%d '%fps
    order+='"%s"  >"%s" 2>&1'%(file_frame,file_framelog)
    subprocess.call(order,shell=True)
    return order

vpth=os.path.join(PTH,'Video',"1080p.mp4")
print(ffprobe(vpth))
print(frame(vpth))
