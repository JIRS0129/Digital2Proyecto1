import spidev
import time

spi = spidev.SpiDev()
spi.open(0, 1)
spi.bits_per_word = 8
spi.max_speed_hz = 976000

var1 = 0
var2 = 0
var3 = 0
var4 = 0
var5 = 0
var6 = 0
var7 = 0
var8 = 0

try:
    while True:
        print(var1)
        print(var2)
        print(var3)
        print(var4)
        print(var5)
        print(var6)
        print(var7)
        print(var8)
        
        spi.writebytes([0])
        time.sleep(0.001)
        var1 = spi.readbytes(1)
        time.sleep(0.001)
        
        spi.writebytes([1])
        time.sleep(0.001)
        var2 = spi.readbytes(1)
        time.sleep(0.001)
        
        spi.writebytes([2])
        time.sleep(0.001)
        var3 = spi.readbytes(1)
        time.sleep(0.001)
        
        spi.writebytes([3])
        time.sleep(0.001)
        var4 = spi.readbytes(1)
        time.sleep(0.001)
        
        spi.writebytes([4])
        time.sleep(0.001)
        var5 = spi.readbytes(1)
        time.sleep(0.001)
        
        spi.writebytes([5])
        time.sleep(0.001)
        var6 = spi.readbytes(1)
        time.sleep(0.001)
        
        spi.writebytes([6])
        time.sleep(0.001)
        var7 = spi.readbytes(1)
        time.sleep(0.001)
        
        spi.writebytes([7])
        time.sleep(0.001)
        var8 = spi.readbytes(1)
        time.sleep(0.001)
        
except KeyboardInterrup:
    spi.close()