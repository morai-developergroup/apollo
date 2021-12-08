/******************************************************************************
 * Copyright 2019 The Apollo Authors. All Rights Reserved.
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

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdlib>
#include <thread>

#include "modules/drivers/proto/conti_radar.pb.h"

#include "cyber/common/log.h"
#include "cyber/scheduler/scheduler_factory.h"
#include "cyber/time/clock.h"
#include "modules/bridge/common/bridge_proto_serialized_buf.h"

using apollo::cyber::Clock;

bool send(const std::string &remote_ip, uint16_t remote_port, uint32_t count) {
  if (count == 0) {
    count = 10000;
  }
  for (uint32_t i = 0; i < count; i++) {
    double timestamp_ = Clock::NowInSeconds() + 2.0;
    auto pb_msg = std::make_shared<apollo::drivers::ContiRadar>();

    pb_msg->mutable_header()->set_timestamp_sec(timestamp_);
    pb_msg->mutable_header()->set_sequence_num(i);

    for(int j =0  ; j < 60 ; j++){

      apollo::drivers::ContiRadarObs* obs_new = pb_msg->add_contiobs();
      obs_new->set_longitude_accel(0);
      obs_new->set_lateral_accel(0);

      obs_new->set_longitude_dist(0);
      obs_new->set_lateral_dist(0);

    }

    struct sockaddr_in server_addr;
    server_addr.sin_addr.s_addr = inet_addr(remote_ip.c_str());
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(remote_port);

    ADEBUG << "connecting to server... ";

    int sock_fd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);

    int res =
        connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (res < 0) {
      ADEBUG << "connected server failed ";
      continue;
    }

    ADEBUG << "connected to server success. port [" << remote_port << "]";

    // apollo::bridge::BridgeProtoSerializedBuf<apollo::canbus::Chassis> proto_buf;
    apollo::bridge::BridgeProtoSerializedBuf<apollo::drivers::ContiRadar> proto_buf;
    proto_buf.Serialize(pb_msg, "ContiRadar");
    for (size_t j = 0; j < proto_buf.GetSerializedBufCount(); j++) {
      ssize_t nbytes = send(sock_fd, proto_buf.GetSerializedBuf(j),
                            proto_buf.GetSerializedBufSize(j), 0);
      if (nbytes != static_cast<ssize_t>(proto_buf.GetSerializedBufSize(j))) {
        ADEBUG << "sent msg failed ";
        break;
      }
      ADEBUG << "sent " << nbytes << " bytes to server with sequence num " << i;
    }
    close(sock_fd);

    // 1000Hz
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  return true;
}

int main(int argc, char *argv[]) {
  uint32_t count = 0;
  if (argc < 2) {
    count = 1000000;
  } else {
    count = atoi(argv[1]);
    CHECK_LE(count, 20000U);
  }
  send("192.168.1.11", 15007, count);
  return 0;
}
