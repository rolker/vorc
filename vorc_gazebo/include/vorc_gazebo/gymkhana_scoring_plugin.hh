/*
 * Copyright (C) 2020 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef VORC_GAZEBO_GYMKHANA_SCORING_PLUGIN_HH_
#define VORC_GAZEBO_GYMKHANA_SCORING_PLUGIN_HH_

#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/World.hh>
#include <ros/ros.h>
#include <vrx_gazebo/scoring_plugin.hh>
#include <vrx_gazebo/Task.h>

class GymkhanaScoringPlugin : public ScoringPlugin
{
  /// \brief Constructor.
  public: GymkhanaScoringPlugin();

  /// \brief Destructor.
  public: virtual ~GymkhanaScoringPlugin();

  // Documentation inherited.
  public: virtual void Load(gazebo::physics::WorldPtr _world,
                            sdf::ElementPtr _sdf);

  /// \brief Callback executed at every world update.
  private: void Update();

  protected: void ChannelCallback(const vrx_gazebo::Task::ConstPtr& msg);

  protected: void BlackboxCallback(const vrx_gazebo::Task::ConstPtr& msg);

  /// \brief Pointer to the update event connection.
  private: gazebo::event::ConnectionPtr updateConnection;

  /// \brief ROS node handle.
  private: std::unique_ptr<ros::NodeHandle> rosNode;

  /// \brief ROS subscriber to channel navigation portion scoring plugin
  private: ros::Subscriber channelSub;

  /// \brief ROS subscriber to black box acoustic pinger portion scoring plugin
  private: ros::Subscriber blackboxSub;

  /// \brief Whether buoy channel portion has been completed
  private: bool channelCrossed = false;

  /// \brief Cumulative error from black box station keeping portion
  private: double blackboxScore = 0.0;
};

#endif
