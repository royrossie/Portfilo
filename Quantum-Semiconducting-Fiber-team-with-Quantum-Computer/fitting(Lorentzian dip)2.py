import numpy as np
from scipy.optimize import curve_fit
from scipy import linalg as sp_linalg
from matplotlib import pyplot as plt
import math
import pandas as pd


#import EXCEL_xlsx
T2=pd.read_excel("ring_fitting test.xlsx",engine='openpyxl',usecols='C:D')
C=T2['c']
D=T2['d']
#print(D)
#print(C)
CC=np.array(C)
DD=np.array(D)
CC=CC[400:600]
DD=DD[400:600]
#print(CC)
#print(DD)
pi=math.pi
print(pi)

plt.plot(C,D, 'red',linewidth=2)
plt.plot(CC,DD, 'blue',linewidth=2)
# 공식   a+b*np.exp(-(x/e)**f)*np.sin(pi*(x-c)/w)   w 값을 입력해 주어야 피팅가능

def func(x,y0,xc,w,A):
    return y0+(2*A/pi)*(w/(4*(x-xc)**2 + w**2))

#def Lorentzian(x, amp1, cen1, wid1):
#    return (amp1*wid1**2/((x-cen1)**2+wid1**2)) 

#def _3Lorentzian(x, amp1, cen1, wid1, amp2,cen2,wid2, amp3,cen3,wid3):
#    return (amp1*wid1**2/((x-cen1)**2+wid1**2)) +\
#            (amp2*wid2**2/((x-cen2)**2+wid2**2)) +\
#                (amp3*wid3**2/((x-cen3)**2+wid3**2))
#def _2Lorentzian(x, amp1, cen1, wid1, amp2,cen2,wid2):
#    return (amp1*wid1**2/((x-cen1)**2+wid1**2)) +\
#            (amp2*wid2**2/((x-cen2)**2+wid2**2)) 


popt, pcov = curve_fit(func, CC, DD, maxfev=10000000)
print(popt)


plt.figure(figsize=(16,4))
#plt.plot(CC, func(CC, 3.29,3.72,0.02911,-0.1), 'red',linewidth=2)

plt.plot(CC, func(CC, *popt), 'red',linewidth=2)
plt.scatter(CC,DD, label='T2')
plt.xticks(fontsize =10) #그래프 눈금 숫자 크기 조절
plt.yticks(fontsize =22) #그래프 눈금 숫자 크기 조절
plt.xlabel('time (us)',fontsize=25)
plt.ylabel('PL',fontsize=25)
plt.legend(fontsize=20)
plt.show()

