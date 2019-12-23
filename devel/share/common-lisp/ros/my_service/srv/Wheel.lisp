; Auto-generated. Do not edit!


(cl:in-package my_service-srv)


;//! \htmlinclude Wheel-request.msg.html

(cl:defclass <Wheel-request> (roslisp-msg-protocol:ros-message)
  ((target_linear_velocity
    :reader target_linear_velocity
    :initarg :target_linear_velocity
    :type cl:float
    :initform 0.0)
   (target_angular_velocity
    :reader target_angular_velocity
    :initarg :target_angular_velocity
    :type cl:float
    :initform 0.0))
)

(cl:defclass Wheel-request (<Wheel-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Wheel-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Wheel-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name my_service-srv:<Wheel-request> is deprecated: use my_service-srv:Wheel-request instead.")))

(cl:ensure-generic-function 'target_linear_velocity-val :lambda-list '(m))
(cl:defmethod target_linear_velocity-val ((m <Wheel-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_service-srv:target_linear_velocity-val is deprecated.  Use my_service-srv:target_linear_velocity instead.")
  (target_linear_velocity m))

(cl:ensure-generic-function 'target_angular_velocity-val :lambda-list '(m))
(cl:defmethod target_angular_velocity-val ((m <Wheel-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_service-srv:target_angular_velocity-val is deprecated.  Use my_service-srv:target_angular_velocity instead.")
  (target_angular_velocity m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Wheel-request>) ostream)
  "Serializes a message object of type '<Wheel-request>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'target_linear_velocity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'target_angular_velocity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Wheel-request>) istream)
  "Deserializes a message object of type '<Wheel-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'target_linear_velocity) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'target_angular_velocity) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Wheel-request>)))
  "Returns string type for a service object of type '<Wheel-request>"
  "my_service/WheelRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Wheel-request)))
  "Returns string type for a service object of type 'Wheel-request"
  "my_service/WheelRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Wheel-request>)))
  "Returns md5sum for a message object of type '<Wheel-request>"
  "ef11d1e759e69b1c0c4a1abd582c4abd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Wheel-request)))
  "Returns md5sum for a message object of type 'Wheel-request"
  "ef11d1e759e69b1c0c4a1abd582c4abd")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Wheel-request>)))
  "Returns full string definition for message of type '<Wheel-request>"
  (cl:format cl:nil "float64 target_linear_velocity~%float64 target_angular_velocity~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Wheel-request)))
  "Returns full string definition for message of type 'Wheel-request"
  (cl:format cl:nil "float64 target_linear_velocity~%float64 target_angular_velocity~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Wheel-request>))
  (cl:+ 0
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Wheel-request>))
  "Converts a ROS message object to a list"
  (cl:list 'Wheel-request
    (cl:cons ':target_linear_velocity (target_linear_velocity msg))
    (cl:cons ':target_angular_velocity (target_angular_velocity msg))
))
;//! \htmlinclude Wheel-response.msg.html

(cl:defclass <Wheel-response> (roslisp-msg-protocol:ros-message)
  ((current_linear_velocity
    :reader current_linear_velocity
    :initarg :current_linear_velocity
    :type cl:float
    :initform 0.0)
   (current_angular_velocity
    :reader current_angular_velocity
    :initarg :current_angular_velocity
    :type cl:float
    :initform 0.0))
)

(cl:defclass Wheel-response (<Wheel-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Wheel-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Wheel-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name my_service-srv:<Wheel-response> is deprecated: use my_service-srv:Wheel-response instead.")))

(cl:ensure-generic-function 'current_linear_velocity-val :lambda-list '(m))
(cl:defmethod current_linear_velocity-val ((m <Wheel-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_service-srv:current_linear_velocity-val is deprecated.  Use my_service-srv:current_linear_velocity instead.")
  (current_linear_velocity m))

(cl:ensure-generic-function 'current_angular_velocity-val :lambda-list '(m))
(cl:defmethod current_angular_velocity-val ((m <Wheel-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader my_service-srv:current_angular_velocity-val is deprecated.  Use my_service-srv:current_angular_velocity instead.")
  (current_angular_velocity m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Wheel-response>) ostream)
  "Serializes a message object of type '<Wheel-response>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'current_linear_velocity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'current_angular_velocity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Wheel-response>) istream)
  "Deserializes a message object of type '<Wheel-response>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'current_linear_velocity) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'current_angular_velocity) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Wheel-response>)))
  "Returns string type for a service object of type '<Wheel-response>"
  "my_service/WheelResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Wheel-response)))
  "Returns string type for a service object of type 'Wheel-response"
  "my_service/WheelResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Wheel-response>)))
  "Returns md5sum for a message object of type '<Wheel-response>"
  "ef11d1e759e69b1c0c4a1abd582c4abd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Wheel-response)))
  "Returns md5sum for a message object of type 'Wheel-response"
  "ef11d1e759e69b1c0c4a1abd582c4abd")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Wheel-response>)))
  "Returns full string definition for message of type '<Wheel-response>"
  (cl:format cl:nil "float64 current_linear_velocity~%float64 current_angular_velocity~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Wheel-response)))
  "Returns full string definition for message of type 'Wheel-response"
  (cl:format cl:nil "float64 current_linear_velocity~%float64 current_angular_velocity~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Wheel-response>))
  (cl:+ 0
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Wheel-response>))
  "Converts a ROS message object to a list"
  (cl:list 'Wheel-response
    (cl:cons ':current_linear_velocity (current_linear_velocity msg))
    (cl:cons ':current_angular_velocity (current_angular_velocity msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'Wheel)))
  'Wheel-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'Wheel)))
  'Wheel-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Wheel)))
  "Returns string type for a service object of type '<Wheel>"
  "my_service/Wheel")