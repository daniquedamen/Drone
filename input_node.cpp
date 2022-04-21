// message publisher

#include <chrono>
#include <memory>
#include <functional>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "message_package/msg/num.hpp" 
#include "message_package/msg/input.hpp" 
#include "std_msgs/msg/string.hpp"
//#include "../include/keyboard_input/keyboard_input_sdl.h"



// still have to make this nice regarding the second input method so with parent class and this as input but could also handle the keyboard input child
// werkt in deze staat

using namespace std::chrono_literals;

class InputPublisher : public rclcpp::Node // public rclcpp::InputClass
{
protected:
  void input_callback()
  {
    auto message = message_package::msg::Input(); 
    message.u={1.0, 2.0, 3.0, 4.0, 5.0,6.0,7.0,8.0,9.0,10.0}; // test numbers
    // doe iets op de input door: ros2 topic pub --once /Inputs message_package/msg/Input "{u:[2.412, 1.234]}"
    publisher_->publish(message);
    RCLCPP_INFO(this->get_logger(),  "You have published input:");// %f"), message[0]); // input publisher 
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<message_package::msg::Input>::SharedPtr publisher_;        
  size_t count_;

public:
  InputPublisher()
  : Node("Input"), count_(0)
  {
    publisher_ = this->create_publisher<message_package::msg::Input>("Inputs_u", 10);   
    timer_ = this->create_wall_timer(
    500ms, std::bind(&InputPublisher::input_callback, this));

  }
};


/*

class commandline_input_class : public InputPublisher
{
  public:

  protected:
}

class keyboard_input_class : public InputPublisher
{
  public:
    keyboard_input_class()
    : Node("keyboard_input")
    {
      timer_ = this->create_wall_timer( 50ms, std::bind(&keyboard_input_class::timer_callback, this));
    }

  protected:
    KeyboardInput_SDL Ki;

    void timer_callback()
    {

      if (Ki.get_quit())
      {
        rclcpp::shutdown();
      }

      auto keys_down = Ki.WhichKeysDown();
      auto message = std_msgs::msg::String();
      message.data = "Keys pressed: ";
      for (unsigned char c : keys_down)
      {
        message.data += c;
      }
      RCLCPP_INFO(this->get_logger(), message.data.c_str());
    }

    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  std::cout<<"=========================================================================="<<std::endl;
  std::cout<<"Attention! This keyboard_input does NOT capture ALL keys! At this moment"<<std::endl;
  std::cout<<"it is configured to only react on the arrow keys and the Q key. If you"<<std::endl;
  std::cout<<"want to change this, adjust the function WhichKeysDown() in"<<std::endl;
  std::cout<<"keyboard_input_sdl.cpp."<<std::endl<<std::endl;
  std::cout<<"Note that (at this moment) the node does not do anything with the acquired"<<std::endl;
  std::cout<<"keyboard information, except for printing to the screen. Thus, you need"<<std::endl;
  std::cout<<"to adjust this node so that it does what you want."<<std::endl;
  std::cout<<"=========================================================================="<<std::endl;
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<keyboard_input_class>());
  rclcpp::shutdown();
  return 0;
}

*/


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<InputPublisher>());
  rclcpp::shutdown();
  return 0;
}



/* input.cpp V1
#include <cstdio>
#include <iostream>
#include "input_node.h"

using namespace std;


int main()
{
  
  string version;
  cout << "Please Enter the version you are working on. \n";
  cout << "a = Drone without cargo or b = Drone with cargo:\n";
    cin >> version >> endl;

  if(version == "a")
    cout << "This is version a\n";
    // blablabla input.node

  else if(version == "b")
    cout << "This is version b\n";

  else
    cout << "You have given a non-correct form of the version. Please enter a or b.\n";
    
  return 0;
}

*/
