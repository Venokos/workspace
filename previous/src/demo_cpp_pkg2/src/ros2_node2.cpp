#include "rclcpp/rclcpp.hpp"

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("my_node2");
    RCLCPP_INFO(node->get_logger(), "Hi Ros!");
    rclcpp::spin(node);
    rclcpp::shutdown();
}
