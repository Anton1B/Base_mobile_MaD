; Auto-generated. Do not edit!


(cl:in-package niryo_one_msgs-msg)


;//! \htmlinclude MatlabMoveResult.msg.html

(cl:defclass <MatlabMoveResult> (roslisp-msg-protocol:ros-message)
  ((status
    :reader status
    :initarg :status
    :type cl:integer
    :initform 0)
   (message
    :reader message
    :initarg :message
    :type cl:string
    :initform ""))
)

(cl:defclass MatlabMoveResult (<MatlabMoveResult>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MatlabMoveResult>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MatlabMoveResult)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name niryo_one_msgs-msg:<MatlabMoveResult> is deprecated: use niryo_one_msgs-msg:MatlabMoveResult instead.")))

(cl:ensure-generic-function 'status-val :lambda-list '(m))
(cl:defmethod status-val ((m <MatlabMoveResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader niryo_one_msgs-msg:status-val is deprecated.  Use niryo_one_msgs-msg:status instead.")
  (status m))

(cl:ensure-generic-function 'message-val :lambda-list '(m))
(cl:defmethod message-val ((m <MatlabMoveResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader niryo_one_msgs-msg:message-val is deprecated.  Use niryo_one_msgs-msg:message instead.")
  (message m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MatlabMoveResult>) ostream)
  "Serializes a message object of type '<MatlabMoveResult>"
  (cl:let* ((signed (cl:slot-value msg 'status)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'message))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'message))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MatlabMoveResult>) istream)
  "Deserializes a message object of type '<MatlabMoveResult>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'status) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'message) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'message) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MatlabMoveResult>)))
  "Returns string type for a message object of type '<MatlabMoveResult>"
  "niryo_one_msgs/MatlabMoveResult")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MatlabMoveResult)))
  "Returns string type for a message object of type 'MatlabMoveResult"
  "niryo_one_msgs/MatlabMoveResult")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MatlabMoveResult>)))
  "Returns md5sum for a message object of type '<MatlabMoveResult>"
  "2c1d00fb8b4e78420f43d93d5292a429")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MatlabMoveResult)))
  "Returns md5sum for a message object of type 'MatlabMoveResult"
  "2c1d00fb8b4e78420f43d93d5292a429")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MatlabMoveResult>)))
  "Returns full string definition for message of type '<MatlabMoveResult>"
  (cl:format cl:nil "int32 status ~%string message ~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MatlabMoveResult)))
  "Returns full string definition for message of type 'MatlabMoveResult"
  (cl:format cl:nil "int32 status ~%string message ~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MatlabMoveResult>))
  (cl:+ 0
     4
     4 (cl:length (cl:slot-value msg 'message))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MatlabMoveResult>))
  "Converts a ROS message object to a list"
  (cl:list 'MatlabMoveResult
    (cl:cons ':status (status msg))
    (cl:cons ':message (message msg))
))
