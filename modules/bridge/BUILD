load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load("//tools/install:install.bzl", "install")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

BRIDGE_COPTS = ['-DMODULE_NAME=\\"bridge\\"']

filegroup(
    name = "runtime_data",
    srcs = glob([
        "conf/*.txt",
        "dag/*.dag",
        "launch/*.launch",
    ]),
)

install(
    name = "install",
    data = [
      ":runtime_data",
    ],
    targets = [
      ":libudp_bridge_sender_component.so",
      ":libudp_bridge_receiver_component.so",
      ":libudp_bridge_receiver_component_corimu.so",
      ":libudp_bridge_multi_receiver_component.so",
    ],
    deps = [
        "//cyber:install",
    ],
)

cc_library(
    name = "udp_bridge",
    copts = BRIDGE_COPTS,
    deps = [
        "//cyber",
        "//modules/bridge/common:bridge_gflags",
        "//modules/bridge/common:bridge_header",
        "//modules/bridge/common:bridge_proto_diser_buf_factory",
        "//modules/bridge/common:bridge_proto_diserialized_buf",
        "//modules/bridge/common:bridge_proto_serialized_buf",
        "//modules/bridge/common:macro",
        "//modules/bridge/common:util",
        "//modules/bridge/proto:udp_bridge_remote_info_cc_proto",
        "//modules/common/adapters:adapter_gflags",
        "//modules/common/monitor_log",
        "//modules/common/util",
        "//modules/planning/proto:planning_cc_proto",
        "//modules/drivers/gnss/proto:gnss_best_pose_cc_proto",
        "//modules/drivers/gnss/proto:imu_cc_proto",
        "//modules/drivers/gnss/proto:ins_cc_proto",
        "//modules/localization/proto:gps_cc_proto",
        "//modules/localization/proto:imu_cc_proto",
        "//modules/control/proto:control_cmd_cc_proto",
        "//modules/drivers/proto:conti_radar_cc_proto",
        "//modules/drivers/proto:sensor_image_cc_proto",
        "//modules/perception/proto:traffic_light_detection_cc_proto",
        "//modules/perception/proto:perception_obstacle_cc_proto",
        "@com_github_gflags_gflags//:gflags",
    ],
)

cc_library(
    name = "udp_bridge_sender",
    srcs = ["udp_bridge_sender_component.cc"],
    hdrs = ["udp_bridge_sender_component.h"],
    copts = BRIDGE_COPTS,
    deps = [
        ":udp_bridge",
    ],
)

cc_library(
    name = "udp_bridge_receiver",
    srcs = ["udp_bridge_receiver_component.cc"],
    hdrs = ["udp_bridge_receiver_component.h"],
    copts = BRIDGE_COPTS,
    deps = [
        ":udp_bridge",
        "//modules/bridge/common:udp_listener",
    ],
)
cc_library(
    name = "udp_bridge_receiver_corimu",
    srcs = ["udp_bridge_receiver_component_corimu.cc"],
    hdrs = ["udp_bridge_receiver_component_corimu.h"],
    copts = BRIDGE_COPTS,
    deps = [
        ":udp_bridge",
        "//modules/bridge/common:udp_listener",
    ],
)
cc_library(
    name = "udp_bridge_receiver_camera",
    srcs = ["udp_bridge_receiver_component_camera.cc"],
    hdrs = ["udp_bridge_receiver_component_camera.h"],
    copts = BRIDGE_COPTS,
    deps = [
        ":udp_bridge",
        "//modules/bridge/common:udp_listener",
    ],
)
cc_library(
    name = "udp_bridge_multi_receiver",
    srcs = ["udp_bridge_multi_receiver_component.cc"],
    hdrs = ["udp_bridge_multi_receiver_component.h"],
    copts = BRIDGE_COPTS,
    deps = [
        ":udp_bridge",
        "//modules/bridge/common:udp_listener",
    ],
)

cc_binary(
    name = "libudp_bridge_sender_component.so",
    linkshared = True,
    linkstatic = False,
    deps = [":udp_bridge_sender"],
)

cc_binary(
    name = "libudp_bridge_receiver_component.so",
    linkshared = True,
    linkstatic = False,
    deps = [":udp_bridge_receiver"],
)
cc_binary(
    name = "libudp_bridge_receiver_component_corimu.so",
    linkshared = True,
    linkstatic = False,
    deps = [":udp_bridge_receiver_corimu"],
)
cc_binary(
    name = "libudp_bridge_receiver_component_camera.so",
    linkshared = True,
    linkstatic = False,
    deps = [":udp_bridge_receiver_camera"],
)

cc_binary(
    name = "libudp_bridge_multi_receiver_component.so",
    linkshared = True,
    linkstatic = False,
    deps = [":udp_bridge_multi_receiver"],
)

cc_test(
    name = "udp_bridge_component_test",
    size = "small",
    srcs = ["udp_bridge_component_test.cc"],
    deps = [
        ":udp_bridge_sender",
        "@com_google_googletest//:gtest_main",
    ],
)

cpplint()
