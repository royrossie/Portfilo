import numpy as np
from scipy.optimize import curve_fit
from scipy import linalg as sp_linalg
from matplotlib import pyplot as plt
import math
import pandas as pd

T2=pd.read_excel("1_7-2.xlsx",engine='openpyxl',usecols='A:B')
C=T2['a']
D=T2['b']

CC=np.array(C)
DD=np.array(D)

CC=CC[360:440]
DD=DD[360:440]

pi=math.pi
print(pi)


