// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>

#include "minimal_composition/member_publisher.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

MemberPublisher::MemberPublisher(const std::shared_ptr<rclcpp::Node>& parent_node)
: parent_node_(parent_node),
  count_(0)
{
  publisher_ = parent_node_->create_publisher<std_msgs::msg::String>("topic_from_member", 10);
  timer_ = parent_node_->create_wall_timer(
    500ms, std::bind(&MemberPublisher::on_timer, this));
}

void MemberPublisher::on_timer()
{
  auto message = std_msgs::msg::String();
  message.data = "Hello, world! " + std::to_string(count_++);
  RCLCPP_INFO(parent_node_->get_logger(), "Topic from Member Publisher: '%s'", message.data.c_str());
  publisher_->publish(message);
}

// #include "rclcpp_components/register_node_macro.hpp"

// RCLCPP_COMPONENTS_REGISTER_NODE(MemberPublisher)
