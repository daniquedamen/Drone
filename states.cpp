#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "message_package/msg/num.hpp"
#include "message_package/msg/num2.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

// We make a class / node of this because this node would become the "drone" node
// message now: Published: Num // topic: states_x, msgx
// subscribed: Num2 // topic: update_states, msg

// Do not call this drone because now you could easily give information of another thing and it would still work

class Update_states : public rclcpp::Node
{
public:
  Update_states()
  : Node("States")
  {
    subscription_ = this->create_subscription<message_package::msg::Num2>(         
      "Update_states", 10, std::bind(&Update_states::update_state_callback, this, _1));

    publisher_ = this->create_publisher<message_package::msg::Num>(
      "States_x", 10, std::bind(&Update_states::publish_state_callback, this, _1));   // this must be changed so the callbacks trigger eachother
  }


  void update_state_callback(const message_package::msg::Num2::SharedPtr msg) const     
  {
    // In here, the states must be updated
    RCLCPP_INFO(this->get_logger(), "Updated State subscribed: '%d'", msg->num2);   
    // over here, or in another way, the publisher must be triggered.           
  }

  void publish_state_callback(const message_package::msg::Num::SharedPtr msgx)
  {
    auto message = message_package::msg::Num();                              
    message.num = this->count_++;                                        
    RCLCPP_INFO(this->get_logger(), "Publish states: '%d'", message.num);    
    publisher_->publish(message);
  }


private:
  
  rclcpp::Subscription<message_package::msg::Num2>::SharedPtr subscription_;  
  rclcpp::Publisher<message_package::msg::Num>::SharedPtr publisher_; 

  rclcpp::TimerBase::SharedPtr timer_;       
  size_t count_;   
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Update_states>());

  rclcpp::shutdown();
  return 0;
}
