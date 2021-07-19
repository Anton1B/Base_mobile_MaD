// Generated by gencpp from file niryo_one_msgs/SetBool.msg
// DO NOT EDIT!


#ifndef NIRYO_ONE_MSGS_MESSAGE_SETBOOL_H
#define NIRYO_ONE_MSGS_MESSAGE_SETBOOL_H

#include <ros/service_traits.h>


#include <niryo_one_msgs/SetBoolRequest.h>
#include <niryo_one_msgs/SetBoolResponse.h>


namespace niryo_one_msgs
{

struct SetBool
{

typedef SetBoolRequest Request;
typedef SetBoolResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct SetBool
} // namespace niryo_one_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::niryo_one_msgs::SetBool > {
  static const char* value()
  {
    return "26e3a36c26c26a03b8fdc8f132744ba9";
  }

  static const char* value(const ::niryo_one_msgs::SetBool&) { return value(); }
};

template<>
struct DataType< ::niryo_one_msgs::SetBool > {
  static const char* value()
  {
    return "niryo_one_msgs/SetBool";
  }

  static const char* value(const ::niryo_one_msgs::SetBool&) { return value(); }
};


// service_traits::MD5Sum< ::niryo_one_msgs::SetBoolRequest> should match 
// service_traits::MD5Sum< ::niryo_one_msgs::SetBool > 
template<>
struct MD5Sum< ::niryo_one_msgs::SetBoolRequest>
{
  static const char* value()
  {
    return MD5Sum< ::niryo_one_msgs::SetBool >::value();
  }
  static const char* value(const ::niryo_one_msgs::SetBoolRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::niryo_one_msgs::SetBoolRequest> should match 
// service_traits::DataType< ::niryo_one_msgs::SetBool > 
template<>
struct DataType< ::niryo_one_msgs::SetBoolRequest>
{
  static const char* value()
  {
    return DataType< ::niryo_one_msgs::SetBool >::value();
  }
  static const char* value(const ::niryo_one_msgs::SetBoolRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::niryo_one_msgs::SetBoolResponse> should match 
// service_traits::MD5Sum< ::niryo_one_msgs::SetBool > 
template<>
struct MD5Sum< ::niryo_one_msgs::SetBoolResponse>
{
  static const char* value()
  {
    return MD5Sum< ::niryo_one_msgs::SetBool >::value();
  }
  static const char* value(const ::niryo_one_msgs::SetBoolResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::niryo_one_msgs::SetBoolResponse> should match 
// service_traits::DataType< ::niryo_one_msgs::SetBool > 
template<>
struct DataType< ::niryo_one_msgs::SetBoolResponse>
{
  static const char* value()
  {
    return DataType< ::niryo_one_msgs::SetBool >::value();
  }
  static const char* value(const ::niryo_one_msgs::SetBoolResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // NIRYO_ONE_MSGS_MESSAGE_SETBOOL_H