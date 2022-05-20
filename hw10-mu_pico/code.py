from ulab import numpy as np

a = range(0, 1024, 1)
s1 = np.sin(a)
s2 = np.sin([1.5*i for i in a])
s3 = np.sin([0.07*i for i in a])

sadd = s1+s2+s3
sfft = np.fft.fft(sadd)
print(len(sfft))


for i in range(len(sfft[0])):
    print((sfft[0][i],sfft[1][i]))




