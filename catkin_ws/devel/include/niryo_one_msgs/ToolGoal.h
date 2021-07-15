// Generated by gencpp from file niryo_one_msgs/ToolGoal.msg
// DO NOT EDIT!


#ifndef NIRYO_ONE_MSGS_MESSAGE_TOOLGOAL_H
#define NIRYO_ONE_MSGS_MESSAGE_TOOLGOAL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <niryo_one_msgs/ToolCommand.h>

namespace niryo_one_msgs
{
template <class ContainerAllocator>
struct ToolGoal_
{
  typedef ToolGoal_<ContainerAllocator> Type;

  ToolGoal_()
    : cmd()  {
    }
  ToolGoal_(const ContainerAllocator& _alloc)
    : cmd(_alloc)  {
  (void)_alloc;
    }



   typedef  ::niryo_one_msgs::ToolCommand_<ContainerAllocator>  _cmd_type;
  _cmd_type cmd;





  typedef boost::shared_ptr< ::niryo_one_msgs::ToolGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::niryo_one_msgs::ToolGoal_<ContainerAllocator> const> ConstPtr;

}; // struct ToolGoal_

typedef ::niryo_one_msgs::ToolGoal_<std::allocator<void> > ToolGoal;

typedef boost::shared_ptr< ::niryo_one_msgs::ToolGoal > ToolGoalPtr;
typedef boost::shared_ptr< ::niryo_one_msgs::ToolGoal const> ToolGoalConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::niryo_one_msgs::ToolGoal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::niryo_one_msgs::ToolGoal_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace niryo_one_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'shape_msgs': ['/opt/ros/kinetic/share/shape_msgs/cmake/../msg'], 'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'moveit_msgs': ['/opt/ros/kinetic/share/moveit_msgs/cmake/../msg'], 'trajectory_msgs': ['/opt/ros/kinetic/share/trajectory_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'object_recognition_msgs': ['/opt/ros/kinetic/share/object_recognition_msgs/cmake/../msg'], 'octomap_msgs': ['/opt/ros/kinetic/share/octomap_msgs/cmake/../msg'], 'niryo_one_msgs': ['/home/chaire/catkin_ws/src/niryo_one_ros/niryo_one_msgs/msg', '/home/chaire/catkin_ws/devel/share/niryo_one_msgs/msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::niryo_one_msgs::ToolGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::niryo_one_msgs::ToolGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::niryo_one_msgs::ToolGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::niryo_one_msgs::ToolGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::niryo_one_msgs::ToolGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::niryo_one_msgs::ToolGoal_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::niryo_one_msgs::ToolGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "c773218b26dbc38b2561cc0aa2e21da9";
  }

  static const char* value(const ::niryo_one_msgs::ToolGoal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xc773218b26dbc38bULL;
  static const uint64_t static_value2 = 0x2561cc0aa2e21da9ULL;
};

template<class ContainerAllocator>
struct DataType< ::niryo_one_msgs::ToolGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "niryo_one_msgs/ToolGoal";
  }

  static const char* value(const ::niryo_one_msgs::ToolGoal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::niryo_one_msgs::ToolGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
# goal\n\
niryo_one_msgs/ToolCommand cmd\n\
\n\
================================================================================\n\
MSG: niryo_one_msgs/ToolCommand\n\
\n\
uint8 tool_id\n\
uint8 cmd_type\n\
\n\
# if gripper close\n\
uint16 gripper_close_speed\n\
\n\
# if gripper open\n\
uint16 gripper_open_speed\n\
\n\
# if vacuum pump or electromagnet grove\n\
bool activate\n\
\n\
# if tool is set by digital outputs (electromagnet)\n\
uint8 gpio\n\
\n\
";
  }

  static const char* value(const ::niryo_one_msgs::ToolGoal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::niryo_one_msgs::ToolGoal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.cmd);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ToolGoal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::niryo_one_msgs::ToolGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::niryo_one_msgs::ToolGoal_<ContainerAllocator>& v)
  {
    s << indent << "cmd: ";
    s << std::endl;
    Printer< ::niryo_one_msgs::ToolCommand_<ContainerAllocator> >::stream(s, indent + "  ", v.cmd);
  }
};

} // namespace message_operations
} // namespace ros

#endif // NIRYO_ONE_MSGS_MESSAGE_TOOLGOAL_H
