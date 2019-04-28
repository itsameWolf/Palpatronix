import numpy as np
from matplotlib import pyplot as plt

compressionFileName = r"E:\Documents\GitHub\Palpatronix\compression soft sensor\Ecoflex 00-30 Compression Test new.is_comp_RawData\Specimen_RawData_1.csv"

compressionData = np.loadtxt(compressionFileName, delimiter=",", skiprows=2)

plt.scatter(compressionData[:,1],compressionData[:,2])

plt.show()