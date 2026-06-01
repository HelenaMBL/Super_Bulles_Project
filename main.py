import tkinter as tk
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg



class evolutiondumouv:

    def __init__(self, fenetre):

        self.fenetre= fenetre
        self.fenetre.title(" |Courbe de l'avolution du mouvement| ")

        # paramètres / data pour la courbe
        self.amplitude= tk.DoubleVar(value=1)
        self.decalage= tk.DoubleVar(value=0)

        # bouton pour faire varier l'amplitude (comme un slider)
        tk.Scale(fenetre,from_= -5, to= 5, resolution=0.1,label="Amplitude (a)", orient="horizontal",variable=self.amplitude,command=self.mettre_a_jour_courbe).pack()

        # bouton pour se faire varier le offset (comme un slider)
        tk.Scale(fenetre,from_=-5, to= 5, resolution=0.1,label="Décalage (b)", orient="horizontal",variable=self.decalage,command=self.mettre_a_jour_courbe).pack()

        # graphique
        self.figure, self.axes = plt.subplots()

        self.canvas = FigureCanvasTkAgg(self.figure, master=fenetre)
        self.canvas.get_tk_widget().pack()

        self.mettre_a_jour_courbe()

    def mettre_a_jour_courbe(self,event=None):

        a= self.amplitude.get()
        b= self.decalage.get()

        x= np.linspace(0, 10, 500)
        y= a*np.sin(x)+ b

        self.axes.clear()
        self.axes.plot(x, y,color="red",linestyle='--', label="Amplitude (a)")

        self.axes.set_title(f"y = {a:.2f} sin(x) + {b:.2f}")
        self.axes.grid(True)

        self.canvas.draw()


# lancement
fenetre= tk.Tk()
app= evolutiondumouv(fenetre)
fenetre.mainloop()