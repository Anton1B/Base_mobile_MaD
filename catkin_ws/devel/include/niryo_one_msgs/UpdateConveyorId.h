// Generated by gencpp from file niryo_one_msgs/UpdateConveyorId.msg
// DO NOT EDIT!


#ifndef NIRYO_ONE_MSGS_MESSAGE_UPDATECONVEYORID_H
#define NIRYO_ONE_MSGS_MESSAGE_UPDATECONVEYORID_H

#include <ros/service_traits.h>


#include <niryo_one_msgs/UpdateConveyorIdRequest.h>
#include <niryo_one_msgs/UpdateConveyorIdResponse.h>


namespace niryo_one_msgs
{

struct UpdateConveyorId
{

typedef UpdateConveyorIdRequest Request;
typedef UpdateConveyorIdResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct UpdateConveyorId
} // namespace niryo_one_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::niryo_one_msgs::UpdateConveyorId > {
  static const char* value()
  {
    return "9e9cf49bb2af3c06095ed6c4f8b6cef4";
  }

  static const char* value(const ::niryo_one_msgs::UpdateConveyorId&) { return value(); }
};

template<>
struct DataType< ::niryo_one_msgs::UpdateConveyorId > {
  static const char* value()
  {
    return "niryo_one_msgs/UpdateConveyorId";
  }

  static const char* value(const ::niryo_one_msgs::UpdateConveyorId&) { return value(); }
};


// service_traits::MD5Sum< ::niryo_one_msgs::UpdateConveyorIdRequest> should match 
// service_traits::MD5Sum< ::niryo_one_msgs::UpdateConveyorId > 
template<>
struct MD5Sum< ::niryo_one_msgs::UpdateConveyorIdRequest>
{
  static const char* value()
  {
    return MD5Sum< ::niryo_one_msgs::UpdateConveyorId >::value();
  }
  static const char* value(const ::niryo_one_msgs::UpdateConveyorIdRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::niryo_one_msgs::UpdateConveyorIdRequest> should match 
// service_traits::DataType< ::niryo_one_msgs::UpdateConveyorId > 
template<>
struct DataType< ::niryo_one_msgs::UpdateConveyorIdRequest>
{
  static const char* value()
  {
    return DataType< ::niryo_one_msgs::UpdateConveyorId >::value();
  }
  static const char* value(const ::niryo_one_msgs::UpdateConveyorIdRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::niryo_one_msgs::UpdateConveyorIdResponse> should match 
// service_traits::MD5Sum< ::niryo_one_msgs::UpdateConveyorId > 
template<>
struct MD5Sum< ::niryo_one_msgs::UpdateConveyorIdResponse>
{
  static const char* value()
  {
    return MD5Sum< ::niryo_one_msgs::UpdateConveyorId >::value();
  }
  static const char* value(const ::niryo_one_msgs::UpdateConveyorIdResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::niryo_one_msgs::UpdateConveyorIdResponse> should match 
// service_traits::DataType< ::niryo_one_msgs::UpdateConveyorId > 
template<>
struct DataType< ::niryo_one_msgs::UpdateConveyorIdResponse>
{
  static const char* value()
  {
    return DataType< ::niryo_one_msgs::UpdateConveyorId >::value();
  }
  static const char* value(const ::niryo_one_msgs::UpdateConveyorIdResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // NIRYO_ONE_MSGS_MESSAGE_UPDATECONVEYORID_H
