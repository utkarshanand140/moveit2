/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2011, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#include <moveit/collision_detection/collision_common.h>
#include <rclcpp/clock.hpp>
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>
#include <moveit/utils/logger.hpp>

constexpr size_t LOG_THROTTLE_PERIOD{ 5 };

namespace collision_detection
{
namespace
{
rclcpp::Logger getLogger()
{
  return moveit::getLogger("collision_detection_common");
}
}  // namespace

void CollisionResult::print() const
{
  rclcpp::Clock clock;
  if (!contacts.empty())
  {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
    RCLCPP_WARN_STREAM_THROTTLE(getLogger(), clock, LOG_THROTTLE_PERIOD,
                                "Objects in collision (printing 1st of "
                                    << contacts.size() << " pairs): " << contacts.begin()->first.first << ", "
                                    << contacts.begin()->first.second);

    // Log all collisions at the debug level
    RCLCPP_DEBUG_STREAM_THROTTLE(getLogger(), clock, LOG_THROTTLE_PERIOD, "Objects in collision:");
    for (const auto& contact : contacts)
    {
      RCLCPP_DEBUG_STREAM_THROTTLE(getLogger(), clock, LOG_THROTTLE_PERIOD,
                                   '\t' << contact.first.first << ", " << contact.first.second);
    }
#pragma GCC diagnostic pop
  }
}

}  // namespace collision_detection
