import matplotlib.pyplot as plt

x = list(range(1000, 100001, 1000))
for k in range(5, 101, 5):
    f = open(f"tri_hybride_k{k}", "r")
    vals = list(map(float, f.read().split()))
    f.close()
    # print(len(vals))
    plt.plot(x, vals)


plt.legend(tuple([f"K={k}" for k in range(5, 101, 5)]))
plt.xlabel("Nombre de valeurs")
plt.ylabel("Temps (en ms)")
plt.title("Choix de K: comparaison")
plt.show()
