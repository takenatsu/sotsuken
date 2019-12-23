// Auto-generated. Do not edit!

// (in-package my_service.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class WheelRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.target_linear_velocity = null;
      this.target_angular_velocity = null;
    }
    else {
      if (initObj.hasOwnProperty('target_linear_velocity')) {
        this.target_linear_velocity = initObj.target_linear_velocity
      }
      else {
        this.target_linear_velocity = 0.0;
      }
      if (initObj.hasOwnProperty('target_angular_velocity')) {
        this.target_angular_velocity = initObj.target_angular_velocity
      }
      else {
        this.target_angular_velocity = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type WheelRequest
    // Serialize message field [target_linear_velocity]
    bufferOffset = _serializer.float64(obj.target_linear_velocity, buffer, bufferOffset);
    // Serialize message field [target_angular_velocity]
    bufferOffset = _serializer.float64(obj.target_angular_velocity, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type WheelRequest
    let len;
    let data = new WheelRequest(null);
    // Deserialize message field [target_linear_velocity]
    data.target_linear_velocity = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [target_angular_velocity]
    data.target_angular_velocity = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a service object
    return 'my_service/WheelRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f0250a22f26b2d4fb70fdb58e85f8b9a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 target_linear_velocity
    float64 target_angular_velocity
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new WheelRequest(null);
    if (msg.target_linear_velocity !== undefined) {
      resolved.target_linear_velocity = msg.target_linear_velocity;
    }
    else {
      resolved.target_linear_velocity = 0.0
    }

    if (msg.target_angular_velocity !== undefined) {
      resolved.target_angular_velocity = msg.target_angular_velocity;
    }
    else {
      resolved.target_angular_velocity = 0.0
    }

    return resolved;
    }
};

class WheelResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.current_linear_velocity = null;
      this.current_angular_velocity = null;
    }
    else {
      if (initObj.hasOwnProperty('current_linear_velocity')) {
        this.current_linear_velocity = initObj.current_linear_velocity
      }
      else {
        this.current_linear_velocity = 0.0;
      }
      if (initObj.hasOwnProperty('current_angular_velocity')) {
        this.current_angular_velocity = initObj.current_angular_velocity
      }
      else {
        this.current_angular_velocity = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type WheelResponse
    // Serialize message field [current_linear_velocity]
    bufferOffset = _serializer.float64(obj.current_linear_velocity, buffer, bufferOffset);
    // Serialize message field [current_angular_velocity]
    bufferOffset = _serializer.float64(obj.current_angular_velocity, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type WheelResponse
    let len;
    let data = new WheelResponse(null);
    // Deserialize message field [current_linear_velocity]
    data.current_linear_velocity = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [current_angular_velocity]
    data.current_angular_velocity = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a service object
    return 'my_service/WheelResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '056d03b83b9853a858cfe23bcf52551d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 current_linear_velocity
    float64 current_angular_velocity
    
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new WheelResponse(null);
    if (msg.current_linear_velocity !== undefined) {
      resolved.current_linear_velocity = msg.current_linear_velocity;
    }
    else {
      resolved.current_linear_velocity = 0.0
    }

    if (msg.current_angular_velocity !== undefined) {
      resolved.current_angular_velocity = msg.current_angular_velocity;
    }
    else {
      resolved.current_angular_velocity = 0.0
    }

    return resolved;
    }
};

module.exports = {
  Request: WheelRequest,
  Response: WheelResponse,
  md5sum() { return 'ef11d1e759e69b1c0c4a1abd582c4abd'; },
  datatype() { return 'my_service/Wheel'; }
};
