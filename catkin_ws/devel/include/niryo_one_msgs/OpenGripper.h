// Generated by gencpp from file niryo_one_msgs/OpenGripper.msg
// DO NOT EDIT!


#ifndef NIRYO_ONE_MSGS_MESSAGE_OPENGRIPPER_H
#define NIRYO_ONE_MSGS_MESSAGE_OPENGRIPPER_H

#include <ros/service_traits.h>


#include <niryo_one_msgs/OpenGripperRequest.h>
#include <niryo_one_msgs/OpenGripperResponse.h>


namespace niryo_one_msgs
{

struct OpenGripper
{

typedef OpenGripperRequest Request;
typedef OpenGripperResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct OpenGripper
} // namespace niryo_one_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::niryo_one_msgs::OpenGripper > {
  static const char* value()
  {
    return "8fa16a49b77c971df71ae1d221893f06";
  }

  static const char* value(const ::niryo_one_msgs::OpenGripper&) { return value(); }
};

template<>
struct DataType< ::niryo_one_msgs::OpenGripper > {
  static const char* value()
  {
    return "niryo_one_msgs/OpenGripper";
  }

  static const char* value(const ::niryo_one_msgs::OpenGripper&) { return value(); }
};


// service_traits::MD5Sum< ::niryo_one_msgs::OpenGripperRequest> should match 
// service_traits::MD5Sum< ::niryo_one_msgs::OpenGripper > 
template<>
struct MD5Sum< ::niryo_one_msgs::OpenGripperRequest>
{
  static const char* value()
  {
    return MD5Sum< ::niryo_one_msgs::OpenGripper >::value();
  }
  static const char* value(const ::niryo_one_msgs::OpenGripperRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::niryo_one_msgs::OpenGripperRequest> should match 
// service_traits::DataType< ::niryo_one_msgs::OpenGripper > 
template<>
struct DataType< ::niryo_one_msgs::OpenGripperRequest>
{
  static const char* value()
  {
    return DataType< ::niryo_one_msgs::OpenGripper >::value();
  }
  static const char* value(const ::niryo_one_msgs::OpenGripperRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::niryo_one_msgs::OpenGripperResponse> should match 
// service_traits::MD5Sum< ::niryo_one_msgs::OpenGripper > 
template<>
struct MD5Sum< ::niryo_one_msgs::OpenGripperResponse>
{
  static const char* value()
  {
    return MD5Sum< ::niryo_one_msgs::OpenGripper >::value();
  }
  static const char* value(const ::niryo_one_msgs::OpenGripperResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::niryo_one_msgs::OpenGripperResponse> should match 
// service_traits::DataType< ::niryo_one_msgs::OpenGripper > 
template<>
struct DataType< ::niryo_one_msgs::OpenGripperResponse>
{
  static const char* value()
  {
    return DataType< ::niryo_one_msgs::OpenGripper >::value();
  }
  static const char* value(const ::niryo_one_msgs::OpenGripperResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // NIRYO_ONE_MSGS_MESSAGE_OPENGRIPPER_H
