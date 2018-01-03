from scipy import signal
from matplotlib import pyplot as plt
import math

file = open("FuncaoTransferencia.txt","r")
file.readline()
w2_n = float(file.readline())
file.readline()
w_n2csi = float(file.readline())
file.close()

tf = signal.lti([w2_n], [1, w_n2csi, w2_n])

w, mag, phase = signal.bode(tf)

plt.figure()
plt.title("Bode - Diagrama de Ganho")
plt.xlabel("Frequencia (Hz)")
plt.ylabel("Magnitude (dB)")
plt.ylim(-40,5)
plt.semilogx(w/math.pi, mag)    # Bode magnitude plot

plt.figure()
plt.title("Bode -Diagrama de Fase")
plt.xlabel("Frequencia (Hz)")
plt.ylabel("Fase (graus)")
plt.ylim(-200,5)
plt.semilogx(w/math.pi, phase)  # Bode phase plot

t, s = signal.step(tf)

plt.figure()
plt.title("Resposta ao Degrau")
plt.xlabel("Tempo (s)")
plt.ylabel("Amplitude")
plt.plot(t, s)

plt.show()
