import matplotlib.pyplot as plt

f=open("nn","r")
f2=open("nlogn","r")
nlogn=f2.read()
nn = f.read()
x=list(range(100,4001,100))

plt.plot(x,list(map(float,nn.split())))
plt.plot(x,list(map(float,nlogn.split())))

plt.show()