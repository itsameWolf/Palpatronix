import numpy as np
from matplotlib import pyplot as plt

compressionFileName = r"C:\Users\Lupo\Documents\GitHub\Palpatronix\compression soft sensor\Ecoflex 00-20 Compression Test new_without screws.is_comp_RawData\Specimen_RawData_2.csv"
hallEffectFileName = r"C:\Users\Lupo\Documents\GitHub\Palpatronix\compression soft sensor\compression 9 - 20 - raw.txt"

compressionData = np.loadtxt(compressionFileName, delimiter=",", skiprows=2)
hallEffectData  = np.loadtxt(hallEffectFileName,delimiter=",")

hallEffectData[:,1] /= 1000

title, compression = plt.subplots(3,1,sharex=True)

title.suptitle("Compression Test with Hall Effect Sensor")

compression[0].scatter(compressionData[:,0],compressionData[:,1])
compression[1].scatter(compressionData[:,0],compressionData[:,2])
compression[2].scatter(hallEffectData[:,1],hallEffectData[:,0])

compression[0].set_title("Displacement")
compression[1].set_title("Load")
compression[2].set_title("Hall Effect")

plt.show()