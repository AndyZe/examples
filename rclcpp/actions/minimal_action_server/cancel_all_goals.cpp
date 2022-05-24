#include "example_interfaces/action/fibonacci.hpp"

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

namespace {
  using Fibonacci = example_interfaces::action::Fibonacci;
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::NodeOptions node_options;
  auto node = rclcpp::Node::make_shared("action_server_cancellation", "", node_options);

rclcpp_action::Client<Fibonacci>::SharedPtr client_ptr = rclcpp_action::create_client<Fibonacci>(node, "fibonacci");
  if (!client_ptr->wait_for_action_server(std::chrono::seconds(5))) {
    RCLCPP_ERROR(node->get_logger(), "Action server not available after waiting");
    rclcpp::shutdown();
  }
  client_ptr->async_cancel_all_goals();
  RCLCPP_ERROR(node->get_logger(), "Cancellation was requested.");

  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}