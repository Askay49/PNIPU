#!/usr/bin/env python

import rospy 
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
import time

def publish_message():
 
  prev_frame_time = 0
  new_frame_time = 0


  pub = rospy.Publisher('video_frames', Image, queue_size=10) 
  rospy.init_node('video_pub_py', anonymous=True)
  rate = rospy.Rate(10)
  cap = cv2.VideoCapture(0)
  br = CvBridge()
 
  while not rospy.is_shutdown():
     
      ret, frame = cap.read()
      
      new_frame_time = time.time()
      fps = 1/(new_frame_time-prev_frame_time)
      fps = str(int(fps))
      prev_frame_time = new_frame_time
    
      cv2.putText(frame, fps, (7, 70), cv2.FONT_HERSHEY_SIMPLEX, 3, (0, 0, 255), 3)
      
      if ret == True:
        rospy.loginfo('publishing video frame')  
        pub.publish(br.cv2_to_imgmsg(frame))

      rate.sleep()
         
if __name__ == '__main__':
  try:
    publish_message()
  except rospy.ROSInterruptException:
    pass