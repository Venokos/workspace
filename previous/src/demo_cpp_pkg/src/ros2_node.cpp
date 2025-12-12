#include "rclcpp/rclcpp.hpp" // 引用rclcpp头文件

int main(int argc, char **argv){
    rclcpp::init(argc, argv); // 初始化
    // 创建节点并命名，赋值给变量node
    auto node = std::make_shared<rclcpp::Node>("my_node"); 
    // 输出文字
    RCLCPP_INFO(node->get_logger(), "Hello Ros!");
    // 启动程序,进入事件循环
    rclcpp::spin(node);
    // 关闭程序
    rclcpp::shutdown();
}
