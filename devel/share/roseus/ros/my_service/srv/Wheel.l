;; Auto-generated. Do not edit!


(when (boundp 'my_service::Wheel)
  (if (not (find-package "MY_SERVICE"))
    (make-package "MY_SERVICE"))
  (shadow 'Wheel (find-package "MY_SERVICE")))
(unless (find-package "MY_SERVICE::WHEEL")
  (make-package "MY_SERVICE::WHEEL"))
(unless (find-package "MY_SERVICE::WHEELREQUEST")
  (make-package "MY_SERVICE::WHEELREQUEST"))
(unless (find-package "MY_SERVICE::WHEELRESPONSE")
  (make-package "MY_SERVICE::WHEELRESPONSE"))

(in-package "ROS")





(defclass my_service::WheelRequest
  :super ros::object
  :slots (_target_linear_velocity _target_angular_velocity ))

(defmethod my_service::WheelRequest
  (:init
   (&key
    ((:target_linear_velocity __target_linear_velocity) 0.0)
    ((:target_angular_velocity __target_angular_velocity) 0.0)
    )
   (send-super :init)
   (setq _target_linear_velocity (float __target_linear_velocity))
   (setq _target_angular_velocity (float __target_angular_velocity))
   self)
  (:target_linear_velocity
   (&optional __target_linear_velocity)
   (if __target_linear_velocity (setq _target_linear_velocity __target_linear_velocity)) _target_linear_velocity)
  (:target_angular_velocity
   (&optional __target_angular_velocity)
   (if __target_angular_velocity (setq _target_angular_velocity __target_angular_velocity)) _target_angular_velocity)
  (:serialization-length
   ()
   (+
    ;; float64 _target_linear_velocity
    8
    ;; float64 _target_angular_velocity
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _target_linear_velocity
       (sys::poke _target_linear_velocity (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _target_angular_velocity
       (sys::poke _target_angular_velocity (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _target_linear_velocity
     (setq _target_linear_velocity (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _target_angular_velocity
     (setq _target_angular_velocity (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass my_service::WheelResponse
  :super ros::object
  :slots (_current_linear_velocity _current_angular_velocity ))

(defmethod my_service::WheelResponse
  (:init
   (&key
    ((:current_linear_velocity __current_linear_velocity) 0.0)
    ((:current_angular_velocity __current_angular_velocity) 0.0)
    )
   (send-super :init)
   (setq _current_linear_velocity (float __current_linear_velocity))
   (setq _current_angular_velocity (float __current_angular_velocity))
   self)
  (:current_linear_velocity
   (&optional __current_linear_velocity)
   (if __current_linear_velocity (setq _current_linear_velocity __current_linear_velocity)) _current_linear_velocity)
  (:current_angular_velocity
   (&optional __current_angular_velocity)
   (if __current_angular_velocity (setq _current_angular_velocity __current_angular_velocity)) _current_angular_velocity)
  (:serialization-length
   ()
   (+
    ;; float64 _current_linear_velocity
    8
    ;; float64 _current_angular_velocity
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _current_linear_velocity
       (sys::poke _current_linear_velocity (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _current_angular_velocity
       (sys::poke _current_angular_velocity (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _current_linear_velocity
     (setq _current_linear_velocity (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _current_angular_velocity
     (setq _current_angular_velocity (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass my_service::Wheel
  :super ros::object
  :slots ())

(setf (get my_service::Wheel :md5sum-) "ef11d1e759e69b1c0c4a1abd582c4abd")
(setf (get my_service::Wheel :datatype-) "my_service/Wheel")
(setf (get my_service::Wheel :request) my_service::WheelRequest)
(setf (get my_service::Wheel :response) my_service::WheelResponse)

(defmethod my_service::WheelRequest
  (:response () (instance my_service::WheelResponse :init)))

(setf (get my_service::WheelRequest :md5sum-) "ef11d1e759e69b1c0c4a1abd582c4abd")
(setf (get my_service::WheelRequest :datatype-) "my_service/WheelRequest")
(setf (get my_service::WheelRequest :definition-)
      "float64 target_linear_velocity
float64 target_angular_velocity
---
float64 current_linear_velocity
float64 current_angular_velocity


")

(setf (get my_service::WheelResponse :md5sum-) "ef11d1e759e69b1c0c4a1abd582c4abd")
(setf (get my_service::WheelResponse :datatype-) "my_service/WheelResponse")
(setf (get my_service::WheelResponse :definition-)
      "float64 target_linear_velocity
float64 target_angular_velocity
---
float64 current_linear_velocity
float64 current_angular_velocity


")



(provide :my_service/Wheel "ef11d1e759e69b1c0c4a1abd582c4abd")


