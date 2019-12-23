
(cl:in-package :asdf)

(defsystem "my_service-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Wheel" :depends-on ("_package_Wheel"))
    (:file "_package_Wheel" :depends-on ("_package"))
  ))