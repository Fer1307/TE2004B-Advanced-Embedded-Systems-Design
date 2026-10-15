import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

data = pd.read_csv("histograma.csv")

x = data["Intensidad"]

r = data["Rojo"].to_numpy()
g = data["Verde"].to_numpy()
b = data["Azul"].to_numpy()

# Juntar los valores interiores (1 a 254)
valores = np.concatenate([
    r[1:255],
    g[1:255],
    b[1:255]
])

# Altura visual: ignorar los picos extremos muy grandes
limite = np.percentile(valores, 99)

plt.fill_between(x, r, color="red", alpha=0.6, label="Rojo")
plt.fill_between(x, g, color="green", alpha=0.6, label="Verde")
plt.fill_between(x, b, color="blue", alpha=0.6, label="Azul")

plt.xlim(0, 255)
plt.ylim(0, limite)

plt.xlabel("Intensidad")
plt.ylabel("Número de píxeles")
plt.title("Histograma RGB")

plt.legend()
plt.show()