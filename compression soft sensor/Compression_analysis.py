import numpy as np
from matplotlib import pyplot as plt

compressionFileName = r"E:\Documents\GitHub\Palpatronix\compression soft sensor\Ecoflex 00-30 Compression Test new.is_comp_RawData\Specimen_RawData_1.csv"
hallEffectFileName = r"E:\Documents\GitHub\Palpatronix\compression soft sensor\compression 6 - 30.txt"

compressionData = np.loadtxt(compressionFileName, delimiter=",", skiprows=2)
hallEffectData  = np.loadtxt(hallEffectFileName,delimiter=",")

hallEffectData[:,1] /= 1000

title, compression = plt.subplots(3,1,sharex=True)

title.suptitle("Compression Test with Hall Effect Sensor")

compression[1].scatter(compressionData[:,0],compressionData[:,1])
compression[2].scatter(compressionData[:,0],compressionData[:,2])
compression[0].scatter(hallEffectData[:,1],hallEffectData[:,0])

compression[1].set_title("Displacement")
compression[2].set_title("Load")
compression[0].set_title("Hall Effect")

plt.show()