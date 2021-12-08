/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/
#pragma once

#include <netinet/in.h>
#include <sys/socket.h>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "modules/bridge/proto/udp_bridge_remote_info.pb.h"
#include "modules/canbus/proto/chassis.pb.h"
#include "modules/drivers/gnss/proto/gnss_best_pose.pb.h"
#include "modules/drivers/gnss/proto/imu.pb.h"
#include "modules/drivers/gnss/proto/ins.pb.h"
#include "modules/localization/proto/gps.pb.h"
#include "modules/localization/proto/imu.pb.h"
#include "modules/drivers/proto/conti_radar.pb.h"
#include "modules/drivers/proto/sensor_image.pb.h"
#include "modules/perception/proto/traffic_light_detection.pb.h"
#include "modules/perception/proto/perception_obstacle.pb.h"


#include "cyber/class_loader/class_loader.h"
#include "cyber/component/component.h"
#include "cyber/cyber.h"
#include "cyber/init.h"
#include "cyber/scheduler/scheduler_factory.h"
#include "modules/bridge/common/bridge_gflags.h"
#include "modules/bridge/common/bridge_header.h"
#include "modules/bridge/common/bridge_proto_diserialized_buf.h"
#include "modules/bridge/common/udp_listener.h"
#include "modules/common/monitor_log/monitor_log_buffer.h"

namespace apollo {
namespace bridge {

#define RECEIVER_BRIDGE_COMPONENT_REGISTER(pb_msg) \
  CYBER_REGISTER_COMPONENT(UDPBridgeReceiverComponent<pb_msg>)

template <typename T>
class UDPBridgeReceiverComponent final : public cyber::Component<> {
 public:
  UDPBridgeReceiverComponent();
  ~UDPBridgeReceiverComponent();

  bool Init() override;

  std::string Name() const { return FLAGS_bridge_module_name; }
  bool MsgHandle(int fd);

 private:
  bool InitSession(uint16_t port);
  void MsgDispatcher();
  bool IsProtoExist(const BridgeHeader &header);
  BridgeProtoDiserializedBuf<T> *CreateBridgeProtoBuf(
      const BridgeHeader &header);
  bool IsTimeout(double time_stamp);
  bool RemoveInvalidBuf(uint32_t msg_id);

 private:
  common::monitor::MonitorLogBuffer monitor_logger_buffer_;
  unsigned int bind_port_ = 0;
  std::string proto_name_ = "";
  std::string topic_name_ = "";
  bool enable_timeout_ = true;
  std::shared_ptr<cyber::Writer<T>> writer_;
  std::mutex mutex_;

  
  // float total_frame_limit = MAXFLOAT;
  // float frame_cnt = 0;
  int flag = 1;

  
  BridgeProtoDiserializedBuf<T> *proto_buf;
  bool proto_init_flag = true;

  std::shared_ptr<UDPListener<UDPBridgeReceiverComponent<T>>> listener_ =
      std::make_shared<UDPListener<UDPBridgeReceiverComponent<T>>>();

  std::vector<BridgeProtoDiserializedBuf<T> *> proto_list_;

};

RECEIVER_BRIDGE_COMPONENT_REGISTER(canbus::Chassis)
RECEIVER_BRIDGE_COMPONENT_REGISTER(drivers::gnss::GnssBestPose)
RECEIVER_BRIDGE_COMPONENT_REGISTER(drivers::gnss::Imu)
RECEIVER_BRIDGE_COMPONENT_REGISTER(drivers::gnss::InsStat)
RECEIVER_BRIDGE_COMPONENT_REGISTER(localization::CorrectedImu)
RECEIVER_BRIDGE_COMPONENT_REGISTER(localization::Gps)
RECEIVER_BRIDGE_COMPONENT_REGISTER(drivers::ContiRadar);
RECEIVER_BRIDGE_COMPONENT_REGISTER(drivers::CompressedImage);
RECEIVER_BRIDGE_COMPONENT_REGISTER(perception::TrafficLightDetection);
RECEIVER_BRIDGE_COMPONENT_REGISTER(perception::PerceptionObstacles);

}  // namespace bridge
}  // namespace apollo

