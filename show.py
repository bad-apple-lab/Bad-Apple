
def consloe_size(x:int,y:int):
    order='mode con cols=%d lines=%d'%(x,y)
    subprocess.call(order,shell=True)
    return
