# import numpy as np
import cv2 as cv


# define a video capture object
vid = cv.VideoCapture("Images/project_video.mp4")
cv.namedWindow("video")
while cv.waitKey(10) < 0:
    # Capture the video frame by frame

    ret, frame = vid.read()
    if ret == False:
        break

    # Display the resulting frame
    img = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    edges = cv.Canny(img, 100, 200)

    cv.imshow("frame", edges)

# display the resulting edge


# After the loop release the cap object
vid.release()
# Destroy all the windows
cv.destroyAllWindows()
