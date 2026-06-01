import tkinter as tk
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from scipy.integrate import solve_ivp


class evolutiondumouv:

    def __init__(self, fenetre):

        self.fenetre = fenetre
        fenetre.attributes("-fullscreen", True)
        self.fenetre.title("Simulation RLC - Courant et tension")

        # paramètres physiques
        self.resistance = tk.DoubleVar(value=2.0)
        self.inductance = tk.DoubleVar(value=1.0)
        self.capacite = tk.DoubleVar(value=1.0)

        # sliders
        tk.Scale(
            fenetre, from_=0.1, to=10, resolution=0.1,
            label="Résistance R",
            variable=self.resistance,
            command=self.mettre_a_jour_courbe
        ).pack()

        tk.Scale(
            fenetre, from_=0.1, to=10, resolution=0.1,
            label="Inductance L",
            variable=self.inductance,
            command=self.mettre_a_jour_courbe
        ).pack()

        tk.Scale(
            fenetre, from_=0.1, to=10, resolution=0.1,
            label="Capacité C",
            variable=self.capacite,
            command=self.mettre_a_jour_courbe
        ).pack()

        # label info
        self.label = tk.Label(self.fenetre, text="")
        self.label.pack()

        # graphique
        self.fig, self.ax = plt.subplots()
        self.canvas = FigureCanvasTkAgg(self.fig, master=fenetre)
        self.canvas.get_tk_widget().pack()

        self.mettre_a_jour_courbe()

    #système différentiel RLC
    def model(self, t, y):

        i,v= y  # i=courant, v=di/dt

        R= self.resistance.get()
        L= self.inductance.get()
        C =self.capacite.get()

        Ve =np.sin(t)  # tension d'entrée

        di_dt= v
        dv_dt=(1 / L) * (Ve - R * v - i / C)

        return [di_dt, dv_dt]

    def mettre_a_jour_courbe(self, event=None):

        t_span=(0, 20)
        t=np.linspace(0, 20, 1000)

        sol= solve_ivp(self.model, t_span, [0, 0], t_eval=t)

        i= sol.y[0]
        Ve= np.sin(t)

        R= self.resistance.get()
        L= self.inductance.get()
        C =self.capacite.get()

        self.label.config(text=f"R={R:.2f}  L={L:.2f}  C={C:.2f}")

        self.ax.clear()
        self.ax.plot(t, Ve, label="Ve(t)", color="red")
        self.ax.plot(t, i, label="i(t)", color="blue")

        self.ax.set_title("Circuit RLC - simulation dynamique\n" r" $L\frac{d^2 i}{dt^2} + R\frac{di}{dt} + \frac{1}{C}i = V_e(t)$")
        self.ax.legend()
        self.ax.grid(True)

        self.canvas.draw()


# lancement
fenetre = tk.Tk()
app = evolutiondumouv(fenetre)
fenetre.mainloop()