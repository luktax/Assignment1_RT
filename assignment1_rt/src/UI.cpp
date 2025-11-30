#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using std::placeholders::_1;

class UI: public rclcpp::Node{
    public:
    UI(): Node("UI")
    {
        publisher1_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        publisher2_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle2/cmd_vel", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(50), std::bind(&UI::timer_callback, this));
    }
    void input()
    {
        while(rclcpp::ok()){
            int turtle;
            double linear_v, angular_v;
            
            while(turtle != 1 && turtle != 2){
                std::cout << "Press 1 or 2 to select a turtle";
                std::cin >> turtle;
                if (turtle != 1 && turtle != 2){
                    std::cout << "Not a valid turtle! insert 1 or 2.\n"
                }
            }

            while(true){
                std::cout << "Linear velocity: ";
                std::cin >> linear_v;     
                
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout <<"Not a valid input! Insert a number.\n"
                } else break;
            }

            while(true){
                std::cout << "Angular velocity: ";
                std::cin >> angular_v;     
                
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout <<"Not a valid input! Insert a number.\n"
                } else break;
            }

            

        }
    }
    
    private:
    void timer_callback()
    {

    }
}


int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<UI>());
    rclcpp::shutdown();
    return 0;
}