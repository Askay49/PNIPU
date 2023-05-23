import cv2
import time

cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)

prev_frame_time = 0
new_frame_time = 0
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('output.avi',fourcc, 20.0, (640,480))
while(cap.isOpened()):
    ret, frame = cap.read()

    new_frame_time = time.time()
    fps = 1/(new_frame_time-prev_frame_time)
    fps = str(int(fps))
    prev_frame_time = new_frame_time
    
    cv2.putText(frame, fps, (7, 70), cv2.FONT_HERSHEY_SIMPLEX, 3, (0, 0, 255), 3)
    
    out.write(frame) 
    
    cv2.imshow('frame', frame)
    
    if cv2.waitKey(10)==27:
        break

cap.release()
out.release()
cv2.destroyAllWindows()
