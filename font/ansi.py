
s='\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dm[(%d,%d,%d)(%d,%d,%d)]\x1b[0m'

rl=[0,127,255]
gl=[0,127,255]
bl=[0,127,255]

rrl=[0,127,255]
ggl=[0,127,255]
bbl=[0,127,255]

for r in rl:
    for g in gl:
        for b in bl:
            for rr in rrl:
                for gg in ggl:
                    for bb in bbl:
                        print(r,g,b,rr,gg,bb,s%(r,g,b,rr,gg,bb,r,g,b,rr,gg,bb,))

