load("@rules_cc//cc:defs.bzl", "cc_binary")
load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "bridge_receiver_test",
    srcs = ["bridge_receiver_test.cc"],
    deps = [
        "//cyber",
        "//modules/bridge:udp_bridge",
        "//modules/bridge/common:udp_listener",
    ],
)

cc_binary(
    name = "bridge_sender_test",
    srcs = ["bridge_sender_test.cc"],
    deps = [
        "//cyber",
        "//modules/bridge:udp_bridge",
    ],
)
cc_binary(
    name = "bridge_receiver_best_pose",
    srcs = ["bridge_receiver_best_pose.cc"],
    deps = [
        "//cyber",
        "//modules/bridge:udp_bridge",
        "//modules/bridge/common:udp_listener",
    ],
)
cc_binary(
    name = "bridge_receiver_imu",
    srcs = ["bridge_receiver_imu.cc"],
    deps = [
        "//cyber",
        "//modules/bridge:udp_bridge",
        "//modules/bridge/common:udp_listener",
    ],
)
#cc_binary(
#    name = "bridge_sender_radar_test",
#    srcs = ["bridge_sender_radar_test.cc"],
#    deps = [
#        "//cyber",
#        "//modules/bridge:udp_bridge",
#    ],
#)
cc_binary(
    name = "bridge_receiver_radar",
    srcs = ["bridge_receiver_radar.cc"],
    deps = [
        "//cyber",
        "//modules/bridge:udp_bridge",
        "//modules/bridge/common:udp_listener",
    ],
)

cpplint()
