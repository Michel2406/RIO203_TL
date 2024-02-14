#===========================================#
#                                           #
#                                           #
#----------CROSSWALK RECOGNITION------------#
#-----------WRITTEN BY N.DALAL--------------#
#-----------------2017 (c)------------------#
#                                           #
#                                           #
#===========================================#

#Copyright by N. Dalal, 2017 (c)

#Licensed under the MIT License:

#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:

#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.



import numpy as np
import cv2
import math
import scipy.misc
import PIL.Image
import statistics
import timeit
import glob
from sklearn import linear_model, datasets


# initialize the HOG descriptor
# initialize the HOG descriptor
# initialize the HOG descriptor
hog = cv2.HOGDescriptor()
hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())

#==========================#
#---------functions--------#
#==========================#

#get a line from a point and unit vectors
def lineCalc(vx, vy, x0, y0):
    scale = 10
    x1 = x0+scale*vx
    y1 = y0+scale*vy
    m = (y1-y0)/(x1-x0)
    b = y1-m*x1
    return m,b

#the angle at the vanishing point
def angle(pt1, pt2):
    x1, y1 = pt1
    x2, y2 = pt2
    inner_product = x1*x2 + y1*y2
    len1 = math.hypot(x1, y1)
    len2 = math.hypot(x2, y2)
    print(len1)
    print(len2)
    a=math.acos(inner_product/(len1*len2))
    return a*180/math.pi 

#vanishing point - cramer's rule
def lineIntersect(m1,b1, m2,b2) : 
    #a1*x+b1*y=c1
    #a2*x+b2*y=c2
    #convert to cramer's system
    a_1 = -m1 
    b_1 = 1
    c_1 = b1

    a_2 = -m2
    b_2 = 1
    c_2 = b2

    d = a_1*b_2 - a_2*b_1 #determinant
    dx = c_1*b_2 - c_2*b_1
    dy = a_1*c_2 - a_2*c_1

    intersectionX = dx/d
    intersectionY = dy/d
    return intersectionX,intersectionY

#process a frame
def process(im):
    start = timeit.timeit() #start timer

    #initialize some variables
    x = W
    y = H

    radius = 250 #px
    thresh = 170 
    bw_width = 170 

    bxLeft = []
    byLeft = []
    bxbyLeftArray = []
    bxbyRightArray = []
    bxRight = []
    byRight = []
    boundedLeft = []
    boundedRight = []
    
    #1. filter the white color
    lower = np.array([170,170,170])
    upper = np.array([255,255,255])
    mask = cv2.inRange(im,lower,upper)

    #2. erode the frame
    erodeSize = int(y / 30)
    erodeStructure = cv2.getStructuringElement(cv2.MORPH_RECT, (erodeSize,1))
    erode = cv2.erode(mask, erodeStructure, (-1, -1))

    #3. find contours and  draw the green lines on the white strips
    #_ , contours,hierarchy = cv2.findContours(erode,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE )
    contours, hierarchy = cv2.findContours(erode, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)
    
    for i in contours:
        bx,by,bw,bh = cv2.boundingRect(i)

        if (bw > bw_width):
            
            cv2.line(im,(bx,by),(bx+bw,by),(0,255,0),2) # draw the a contour line
            bxRight.append(bx+bw) #right line
            byRight.append(by) #right line
            bxLeft.append(bx) #left line
            byLeft.append(by) #left line
            bxbyLeftArray.append([bx,by]) #x,y for the left line
            bxbyRightArray.append([bx+bw,by]) # x,y for the left line
            cv2.circle(im,(int(bx),int(by)),5,(0,250,250),2) #circles -> left line
            cv2.circle(im,(int(bx+bw),int(by)),5,(250,250,0),2) #circles -> right line
    
    p1 = bxbyLeftArray[0]
    p2 = bxbyLeftArray[-1]
    p3 = bxbyRightArray[0]
    p4 = bxbyRightArray[len(bxbyLeftArray) - 2]

    #Draw rectangle on the image
    cv2.rectangle(img, tuple(p1), tuple(p4), (0, 255, 0), 2)
    global rectangle
    rectangle = (p1, p4)

    #calculate median average for each line
    medianR = np.median(bxbyRightArray, axis=0)
    medianL = np.median(bxbyLeftArray, axis=0)

    bxbyLeftArray = np.asarray(bxbyLeftArray)
    bxbyRightArray = np.asarray(bxbyRightArray)
     
    #4. are the points bounded within the median circle?
    for i in bxbyLeftArray:
        if (((medianL[0] - i[0])**2 + (medianL[1] - i[1])**2) < radius**2) == True:
            boundedLeft.append(i)

    boundedLeft = np.asarray(boundedLeft)

    for i in bxbyRightArray:
        if (((medianR[0] - i[0])**2 + (medianR[1] - i[1])**2) < radius**2) == True:
            boundedRight.append(i)

    boundedRight = np.asarray(boundedRight)

    #5. RANSAC Algorithm

    #select the points enclosed within the circle (from the last part)
    bxLeft = np.asarray(boundedLeft[:,0])
    byLeft =  np.asarray(boundedLeft[:,1]) 
    bxRight = np.asarray(boundedRight[:,0]) 
    byRight = np.asarray(boundedRight[:,1])

    #transpose x of the right and the left line
    bxLeftT = np.array([bxLeft]).transpose()
    bxRightT = np.array([bxRight]).transpose()

    #run ransac for LEFT
    model_ransac = linear_model.RANSACRegressor(linear_model.LinearRegression())
    ransacX = model_ransac.fit(bxLeftT, byLeft)
    inlier_maskL = model_ransac.inlier_mask_ #right mask

    #run ransac for RIGHT
    ransacY = model_ransac.fit(bxRightT, byRight)
    inlier_maskR = model_ransac.inlier_mask_ #left mask

    #draw RANSAC selected circles
    for i, element in enumerate(boundedRight[inlier_maskR]):
       # print(i,element[0])
        cv2.circle(im,(element[0],element[1]),10,(250,250,250),2) #circles -> right line

    for i, element in enumerate(boundedLeft[inlier_maskL]):
       # print(i,element[0])
        cv2.circle(im,(element[0],element[1]),10,(100,100,250),2) #circles -> right line


    #6. Calcuate the intersection point of the bounding lines
    #unit vector + a point on each line
    vx, vy, x0, y0 = cv2.fitLine(boundedLeft[inlier_maskL],cv2.DIST_L2,0,0.01,0.01) 
    vx_R, vy_R, x0_R, y0_R = cv2.fitLine(boundedRight[inlier_maskR],cv2.DIST_L2,0,0.01,0.01)

    #get m*x+b
    m_L,b_L=lineCalc(vx, vy, x0, y0)
    m_R,b_R=lineCalc(vx_R, vy_R, x0_R, y0_R)

    #calculate intersention 
    intersectionX,intersectionY = lineIntersect(m_R,b_R,m_L,b_L)

    #7. draw the bounding lines and the intersection point
    m = radius*10 
    if (intersectionY < H/2 ):
        #cv2.circle(im,(int(intersectionX),int(intersectionY)),10,(0,0,255),15)
        #cv2.line(im,(x0-m*vx, y0-m*vy), (x0+m*vx, y0+m*vy),(255,0,0),3)
        #cv2.line(im,(x0_R-m*vx_R, y0_R-m*vy_R), (x0_R+m*vx_R, y0_R+m*vy_R),(255,0,0),3)
        i = 0

   
    #8. calculating the direction vector  
    POVx = W/2 #camera POV - center of the screen
    POVy = H/2 # camera POV - center of the screen

    Dx = -int(intersectionX-POVx) #regular x,y axis coordinates
    Dy = -int(intersectionY-POVy) #regular x,y axis coordinates

    #focal length in pixels = (image width in pixels) * (focal length in mm) / (CCD width in mm)
    focalpx = int(W * 4.26 / 6.604) #all in mm


    end = timeit.timeit() #STOP TIMER
    time_ = end - start

    print('DELTA (x,y from POV):' + str(Dx) + ',' + str(Dy))
    return im,Dx,Dy

def draw_rectangle(img, p1, p2, color=(0, 255, 0), thickness=2):
    """
    Draw a rectangle on the image.

    Parameters:
    - img: The image on which to draw the rectangle.
    - p1: Tuple representing one corner of the rectangle.
    - p2: Tuple representing the opposite corner of the rectangle.
    - color: Color of the rectangle (BGR format).
    - thickness: Thickness of the rectangle border.
    """
    cv2.rectangle(img, p1, p2, color, thickness)

def is_point_inside_rectangle(point, corner1, corner2):
    """
    Check if a point is inside a rectangle.

    Parameters:
    - point: Tuple representing the (x, y) coordinates of the point.
    - corner1: Tuple representing one corner of the rectangle.
    - corner2: Tuple representing the opposite corner of the rectangle.

    Returns:
    - True if the point is inside the rectangle, False otherwise.
    """
    x, y = point
    x1, y1 = corner1
    x2, y2 = corner2

    return x1 <= x <= x2 or y1 <= y <= y2



#=============================#
#---------MAIN PROGRAM--------#
#=============================#
#initialization
cap = cv2.VideoCapture('../walker.mov') #load a video

W = cap.get(3) #get width
H = cap.get(4) #get height

#Define a new resolution 
#ratio = H/W
#W = 800
#H = int(W * ratio)

#setup the parameters for saving the processed file
fourcc = cv2.VideoWriter_fourcc(*'mp4v')
out = cv2.VideoWriter('processed.mp4',fourcc, 15.0, (int(W),int(H)))

Dx = []
Dy = []
after =0
DxAve =0
Dxold =0
DyAve =0
Dyold =0
i = 0
state = ""
procNumber = 0
rectangle = 0
outSide = 0

while(cap.isOpened()):
    #ret, frame = cap.read()
    #img = scipy.misc.imresize(frame, (H,W)) 
    
    #draw camera's POV
    #cv2.circle(img,(int(W/2),int(H/2)),5,(0,0,255),8)

    #ret, frame = cap.read()
    #img = scipy.misc.imresize(frame, (H,W)) 
    #img = resize(frame, (H, W))
    #img = frame.copy()
    #draw camera's POV
    #cv2.circle(img,(int(W/2),int(H/2)),5,(0,0,255),8)

    ret, frame = cap.read()
    
    
    # Check if the frame is not None
    if frame is None:
        break

    img = frame.copy()
    
    try:
        processedFrame = img
        if(procNumber == 0):
            processedFrame,dx,dy = process(img)
        else:
            if(rectangle != 0):
                draw_rectangle(img, rectangle[0], rectangle[1])


        procNumber = procNumber + 1
        
        # detect humans in input image
        (humans, _) = hog.detectMultiScale(img, winStride=(10, 10),
        padding=(32, 32), scale=1.1)

        # getting no. of human detected
        #print('Human Detected : ', len(humans))
        cx = 0
        cy = 0
        # loop over all detected humans
        for (x, y, w, h) in humans:
            pad_w, pad_h = int(0.15 * w), int(0.01 * h)
            # Calculate center coordinates at the bottom side
            cx = x + w // 2
            cy = y + h - pad_h  # Adjusted to be at the bottom side
            # Draw a circle at the center
            cv2.circle(img, (cx, cy), 5, (200, 0, 200), -1)  # -1 fills the circle
        #print(cx, cy)
        if(not is_point_inside_rectangle((cx, cy), rectangle[0], rectangle[1])):
            outSide = outSide + 1
            #print(outSide)
        else:
            outSide = 0
            
        if(outSide == 50):
            print("State : warning ....")
            outSide = 0
    except:
        print('Failed to process frame')

    #show & save
    img = cv2.imshow('Processed',processedFrame) 
    out.write(processedFrame)
    
    if cv2.waitKey(1) & 0xFF == ord('q') or cv2.waitKey(1) & 0xFF == ord('Q'):
        break

out.release()
cap.release()
cv2.destroyAllWindows()