import numpy as np 
import matplotlib.pyplot as plt 

def plotheatmap(u, tf, Dx, Dy):
	plt.clf()
	plt.title(f"Temperature at t = {tf:.4f} unit time")
	plt.xlabel("x")
	plt.ylabel("y")
	plt.imshow(u, cmap=plt.cm.jet, origin='lower', extent=(0, Dx, 0, Dy))
	ax1 = plt.gca()
	ax1.set_xlim(0, Dx)
	ax1.set_ylim(0, Dy)
	plt.colorbar()
	return plt

def main():
	f = open("./output.txt")
	u = np.loadtxt(f, skiprows=0)
	hd = u[0,0:]
	nx, ny, dx, dy, tf, alpha = hd[0:6]
	nx = int(nx)
	ny = int(ny)
	#print(f"nx = {nx}; ny = {ny}")
	#print(f"nt = {nt}; dt = {dt}; tf = {dt * (nt-3)}")
	Dx = (nx-1)*dx
	Dy = (ny-1)*dy
	u = u[1:,:].T
	plt = plotheatmap(u, tf, Dx, Dy)
	plt.savefig("./img/Plate.svg", format="svg")
	plt.savefig("./img/Plate.png", format="png")
	plt.show()
	
main()