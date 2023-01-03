# //	 Trần Minh Nhựt 	19144062
# //	 Nguyễn Tiến Phúc	19146137
# //	 Ninh Khải Hoàn		19146087
import pyautogui
import time
import serial
import io

# uart
ser = serial.Serial()
ser.baudrate = 9600
ser.port = 'COM6'
ser.timeout = 0.1
ser.open()
print('serial COM 4 open', ser.is_open)
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))
ser.flush() # wait until all data is written

pyautogui.FAILSAFE = False # set failsafe for manual exit

while(True):
    if ser.in_waiting:
        line = ser.readline().decode('utf')[:-1]
        # line = sio.readline()
        data = line.split()     
        # print(line)
        print (data)
        motion = int(data[11])
        print(motion)
        if motion == 0:
            print('blance') 
            pyautogui.press('c')
        elif motion == 1:
            pyautogui.keyDown('down')  
            pyautogui.keyUp('down')
        elif motion == 2:
            pyautogui.keyDown('up')    
            
            pyautogui.keyUp('up')
        elif motion == 3: 
            pyautogui.keyDown('shift')    
            pyautogui.keyDown('left')
            pyautogui.keyUp('left')
            pyautogui.keyUp('shift')
            pyautogui.press('c')
        elif motion == 4: 
            pyautogui.keyDown('shift')    
            pyautogui.keyDown('right')
            pyautogui.keyUp('right')
            pyautogui.keyUp('shift')
            pyautogui.press('c')

        
        if  int(data[0]) == 0:
             pyautogui.keyDown('left')  
             pyautogui.keyDown('up')    
            
             pyautogui.keyUp('up')
             pyautogui.keyUp('left')        

        #button 2
        if int(data[1]) == 0:
            pyautogui.keyDown('right')  
            pyautogui.keyUp('right') 
            pyautogui.keyDown('up')    
            
            pyautogui.keyUp('up')
            

        # #button 3
        if int(data[1]) == 0:
            pyautogui.keyDown('space')  
            pyautogui.keyUp('space')              
 
        #button 4
        if int(data[3]) == 0: 
            pyautogui.keyDown('shift')
            pyautogui.keyDown('f')
            pyautogui.keyUp('shift')
            pyautogui.keyUp('f')

        #button 5
        if int(data[4]) == 0:
            pyautogui.keyDown('left')  
            pyautogui.keyUp('left')  
          

        #button 6
        if int(data[5]) == 0:
            pyautogui.keyDown('right')  
            pyautogui.keyUp('right')
      
        #button 7
        if int(data[6]) == 0:
            pyautogui.keyDown('g')  
            pyautogui.keyUp('g')
        

        #button8
        if int(data[7]) == 0:
            pyautogui.press('c')

        #button9
        if int(data[8]) == 0:
            pyautogui.keyDown('f')
            pyautogui.keyUp('f')

        #pageup
        if int(data[9]) == 1:
            pyautogui.keyDown('pageup')  
            pyautogui.keyUp('pageup')
        # pagedown
        if int(data[10]) == 1:
            pyautogui.keyDown('pagedown')  
            pyautogui.keyUp('pagedown')

