#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/address_book.hpp"

using namespace std::chrono_literals;

class AddressBookPublisher : public rclcpp::Node
{
public:
	// Create an address book publisher
	AddressBookPublisher() // Constructor
	: Node("address_book_publisher")
	{
		address_book_publisher_ =
			this->create_publisher<more_interfaces::msg::AddressBook>("address_book", 10);
		
		auto publish_msg = [this]() -> void {
			auto message = more_interfaces::msg::AddressBook();

			message.first_name = "John";
			message.last_name = "Doe";
			message.phone_number = "1234567890";
			message.phone_type = message.PHONE_TYPE_MOBILE;

			RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Publishing Contact\n");

			this->address_book_publisher_->publish(message);
		};
		timer_ = this->create_wall_timer(1s, publish_msg);
	}
private:
	rclcpp::Publisher<more_interfaces::msg::AddressBook>::SharedPtr address_book_publisher_;
	rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	// Advertise an instance of "AddressBookPublisher", passing by shared pointer
	rclcpp::spin(std::make_shared<AddressBookPublisher>());
	rclcpp::shutdown();

	return 0;
}
