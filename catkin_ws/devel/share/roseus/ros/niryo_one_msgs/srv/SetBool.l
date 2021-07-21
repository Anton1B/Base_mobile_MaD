;; Auto-generated. Do not edit!


(when (boundp 'niryo_one_msgs::SetBool)
  (if (not (find-package "NIRYO_ONE_MSGS"))
    (make-package "NIRYO_ONE_MSGS"))
  (shadow 'SetBool (find-package "NIRYO_ONE_MSGS")))
(unless (find-package "NIRYO_ONE_MSGS::SETBOOL")
  (make-package "NIRYO_ONE_MSGS::SETBOOL"))
(unless (find-package "NIRYO_ONE_MSGS::SETBOOLREQUEST")
  (make-package "NIRYO_ONE_MSGS::SETBOOLREQUEST"))
(unless (find-package "NIRYO_ONE_MSGS::SETBOOLRESPONSE")
  (make-package "NIRYO_ONE_MSGS::SETBOOLRESPONSE"))

(in-package "ROS")





(defclass niryo_one_msgs::SetBoolRequest
  :super ros::object
  :slots (_value ))

(defmethod niryo_one_msgs::SetBoolRequest
  (:init
   (&key
    ((:value __value) nil)
    )
   (send-super :init)
   (setq _value __value)
   self)
  (:value
   (&optional __value)
   (if __value (setq _value __value)) _value)
  (:serialization-length
   ()
   (+
    ;; bool _value
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _value
       (if _value (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _value
     (setq _value (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass niryo_one_msgs::SetBoolResponse
  :super ros::object
  :slots (_status _message ))

(defmethod niryo_one_msgs::SetBoolResponse
  (:init
   (&key
    ((:status __status) 0)
    ((:message __message) "")
    )
   (send-super :init)
   (setq _status (round __status))
   (setq _message (string __message))
   self)
  (:status
   (&optional __status)
   (if __status (setq _status __status)) _status)
  (:message
   (&optional __message)
   (if __message (setq _message __message)) _message)
  (:serialization-length
   ()
   (+
    ;; int32 _status
    4
    ;; string _message
    4 (length _message)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _status
       (write-long _status s)
     ;; string _message
       (write-long (length _message) s) (princ _message s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _status
     (setq _status (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; string _message
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _message (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass niryo_one_msgs::SetBool
  :super ros::object
  :slots ())

(setf (get niryo_one_msgs::SetBool :md5sum-) "26e3a36c26c26a03b8fdc8f132744ba9")
(setf (get niryo_one_msgs::SetBool :datatype-) "niryo_one_msgs/SetBool")
(setf (get niryo_one_msgs::SetBool :request) niryo_one_msgs::SetBoolRequest)
(setf (get niryo_one_msgs::SetBool :response) niryo_one_msgs::SetBoolResponse)

(defmethod niryo_one_msgs::SetBoolRequest
  (:response () (instance niryo_one_msgs::SetBoolResponse :init)))

(setf (get niryo_one_msgs::SetBoolRequest :md5sum-) "26e3a36c26c26a03b8fdc8f132744ba9")
(setf (get niryo_one_msgs::SetBoolRequest :datatype-) "niryo_one_msgs/SetBoolRequest")
(setf (get niryo_one_msgs::SetBoolRequest :definition-)
      "bool value
---
int32 status
string message

")

(setf (get niryo_one_msgs::SetBoolResponse :md5sum-) "26e3a36c26c26a03b8fdc8f132744ba9")
(setf (get niryo_one_msgs::SetBoolResponse :datatype-) "niryo_one_msgs/SetBoolResponse")
(setf (get niryo_one_msgs::SetBoolResponse :definition-)
      "bool value
---
int32 status
string message

")



(provide :niryo_one_msgs/SetBool "26e3a36c26c26a03b8fdc8f132744ba9")


