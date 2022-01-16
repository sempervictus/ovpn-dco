/* SPDX-License-Identifier: GPL-2.0-only WITH Linux-syscall-note */
/*
 *  OpenVPN data channel accelerator
 *
 *  Copyright (C) 2019-2021 OpenVPN, Inc.
 *
 *  Author:	James Yonan <james@openvpn.net>
 *		Antonio Quartulli <antonio@openvpn.net>
 */

#ifndef _UAPI_LINUX_OVPN_DCO_H_
#define _UAPI_LINUX_OVPN_DCO_H_

#define OVPN_NL_NAME "ovpn-dco"

#define OVPN_NL_MULTICAST_GROUP_PEERS "peers"

/**
 * enum ovpn_nl_commands - supported netlink commands
 */
enum ovpn_nl_commands {
	/**
	 * @OVPN_CMD_UNSPEC: unspecified command to catch errors
	 */
	OVPN_CMD_UNSPEC = 0,

	/**
	 * @OVPN_CMD_NEW_PEER: Configure peer with its crypto keys
	 */
	OVPN_CMD_NEW_PEER,

	/**
	 * @OVPN_CMD_SET_PEER: Tweak parameters for an existing peer
	 */
	OVPN_CMD_SET_PEER,

	/**
	 * @OVPN_CMD_DEL_PEER: Remove peer from internal table
	 */
	OVPN_CMD_DEL_PEER,

	OVPN_CMD_NEW_KEY,

	OVPN_CMD_SWAP_KEYS,

	OVPN_CMD_DEL_KEY,

	/**
	 * @OVPN_CMD_REGISTER_PACKET: Register for specific packet types to be
	 * forwarded to userspace
	 */
	OVPN_CMD_REGISTER_PACKET,

	/**
	 * @OVPN_CMD_PACKET: Send a packet from userspace to kernelspace. Also
	 * used to send to userspace packets for which a process had registered
	 * with OVPN_CMD_REGISTER_PACKET
	 */
	OVPN_CMD_PACKET,

	/**
	 * @OVPN_CMD_GET_PEER: Retrieve the status of a peer or all peers
	 */
	OVPN_CMD_GET_PEER,
};

enum ovpn_cipher_alg {
	/**
	 * @OVPN_CIPHER_ALG_NONE: Reserved for debugging only
	 */
	OVPN_CIPHER_ALG_NONE = 0,
	OVPN_CIPHER_ALG_AES_GCM,
	OVPN_CIPHER_ALG_CHACHA20_POLY1305,
};

enum ovpn_del_peer_reason {
	__OVPN_DEL_PEER_REASON_FIRST,
	OVPN_DEL_PEER_REASON_TEARDOWN = __OVPN_DEL_PEER_REASON_FIRST,
	OVPN_DEL_PEER_REASON_USERSPACE,
	OVPN_DEL_PEER_REASON_EXPIRED,
	OVPN_DEL_PEER_REASON_TRANSPORT_ERROR,
	__OVPN_DEL_PEER_REASON_AFTER_LAST
};

enum ovpn_key_slot {
	__OVPN_KEY_SLOT_FIRST,
	OVPN_KEY_SLOT_PRIMARY = __OVPN_KEY_SLOT_FIRST,
	OVPN_KEY_SLOT_SECONDARY,
	__OVPN_KEY_SLOT_AFTER_LAST,
};

enum ovpn_netlink_attrs {
	OVPN_ATTR_UNSPEC = 0,
	OVPN_ATTR_IFINDEX,
	OVPN_ATTR_NEW_PEER,
	OVPN_ATTR_SET_PEER,
	OVPN_ATTR_DEL_PEER,
	OVPN_ATTR_NEW_KEY,
	OVPN_ATTR_SWAP_KEYS,
	OVPN_ATTR_DEL_KEY,
	OVPN_ATTR_PACKET,
	OVPN_ATTR_GET_PEER,

	__OVPN_ATTR_AFTER_LAST,
	OVPN_ATTR_MAX = __OVPN_ATTR_AFTER_LAST - 1,
};

enum ovpn_netlink_key_dir_attrs {
	OVPN_KEY_DIR_ATTR_UNSPEC = 0,
	OVPN_KEY_DIR_ATTR_CIPHER_KEY,
	OVPN_KEY_DIR_ATTR_NONCE_TAIL,

	__OVPN_KEY_DIR_ATTR_AFTER_LAST,
	OVPN_KEY_DIR_ATTR_MAX = __OVPN_KEY_DIR_ATTR_AFTER_LAST - 1,
};

enum ovpn_netlink_new_key_attrs {
	OVPN_NEW_KEY_ATTR_UNSPEC = 0,
	OVPN_NEW_KEY_ATTR_PEER_ID,
	OVPN_NEW_KEY_ATTR_KEY_SLOT,
	OVPN_NEW_KEY_ATTR_KEY_ID,
	OVPN_NEW_KEY_ATTR_CIPHER_ALG,
	OVPN_NEW_KEY_ATTR_ENCRYPT_KEY,
	OVPN_NEW_KEY_ATTR_DECRYPT_KEY,

	__OVPN_NEW_KEY_ATTR_AFTER_LAST,
	OVPN_NEW_KEY_ATTR_MAX = __OVPN_NEW_KEY_ATTR_AFTER_LAST - 1,
};

enum ovpn_netlink_del_key_attrs {
	OVPN_DEL_KEY_ATTR_UNSPEC = 0,
	OVPN_DEL_KEY_ATTR_PEER_ID,
	OVPN_DEL_KEY_ATTR_KEY_SLOT,

	__OVPN_DEL_KEY_ATTR_AFTER_LAST,
	OVPN_DEL_KEY_ATTR_MAX = __OVPN_DEL_KEY_ATTR_AFTER_LAST - 1,
};

enum ovpn_netlink_swap_keys_attrs {
	OVPN_SWAP_KEYS_ATTR_UNSPEC = 0,
	OVPN_SWAP_KEYS_ATTR_PEER_ID,

	__OVPN_SWAP_KEYS_ATTR_AFTER_LAST,
	OVPN_SWAP_KEYS_ATTR_MAX = __OVPN_SWAP_KEYS_ATTR_AFTER_LAST - 1,

};

enum ovpn_netlink_new_peer_attrs {
	OVPN_NEW_PEER_ATTR_UNSPEC = 0,
	OVPN_NEW_PEER_ATTR_PEER_ID,
	OVPN_NEW_PEER_ATTR_SOCKADDR_REMOTE,
	OVPN_NEW_PEER_ATTR_SOCKET,
	OVPN_NEW_PEER_ATTR_IPV4,
	OVPN_NEW_PEER_ATTR_IPV6,
	OVPN_NEW_PEER_ATTR_LOCAL_IP,

	__OVPN_NEW_PEER_ATTR_AFTER_LAST,
	OVPN_NEW_PEER_ATTR_MAX = __OVPN_NEW_PEER_ATTR_AFTER_LAST - 1,
};

enum ovpn_netlink_set_peer_attrs {
	OVPN_SET_PEER_ATTR_UNSPEC = 0,
	OVPN_SET_PEER_ATTR_PEER_ID,
	OVPN_SET_PEER_ATTR_KEEPALIVE_INTERVAL,
	OVPN_SET_PEER_ATTR_KEEPALIVE_TIMEOUT,

	__OVPN_SET_PEER_ATTR_AFTER_LAST,
	OVPN_SET_PEER_ATTR_MAX = __OVPN_SET_PEER_ATTR_AFTER_LAST - 1,
};

enum ovpn_netlink_del_peer_attrs {
	OVPN_DEL_PEER_ATTR_UNSPEC = 0,
	OVPN_DEL_PEER_ATTR_REASON,
	OVPN_DEL_PEER_ATTR_PEER_ID,

	__OVPN_DEL_PEER_ATTR_AFTER_LAST,
	OVPN_DEL_PEER_ATTR_MAX = __OVPN_DEL_PEER_ATTR_AFTER_LAST - 1,
};

enum ovpn_netlink_get_peer_attrs {
	OVPN_GET_PEER_ATTR_UNSPEC = 0,
	OVPN_GET_PEER_ATTR_PEER_ID,

	__OVPN_GET_PEER_ATTR_AFTER_LAST,
	OVPN_GET_PEER_ATTR_MAX = __OVPN_GET_PEER_ATTR_AFTER_LAST - 1,
};

enum ovpn_netlink_get_peer_response_attrs {
	OVPN_GET_PEER_RESP_ATTR_UNSPEC = 0,
	OVPN_GET_PEER_RESP_ATTR_PEER_ID,
	OVPN_GET_PEER_RESP_ATTR_SOCKADDR_REMOTE,
	OVPN_GET_PEER_RESP_ATTR_IPV4,
	OVPN_GET_PEER_RESP_ATTR_IPV6,
	OVPN_GET_PEER_RESP_ATTR_LOCAL_IP,
	OVPN_GET_PEER_RESP_ATTR_LOCAL_PORT,
	OVPN_GET_PEER_RESP_ATTR_KEEPALIVE_INTERVAL,
	OVPN_GET_PEER_RESP_ATTR_KEEPALIVE_TIMEOUT,
	OVPN_GET_PEER_RESP_ATTR_RX_BYTES,
	OVPN_GET_PEER_RESP_ATTR_TX_BYTES,
	OVPN_GET_PEER_RESP_ATTR_RX_PACKETS,
	OVPN_GET_PEER_RESP_ATTR_TX_PACKETS,

	__OVPN_GET_PEER_RESP_ATTR_AFTER_LAST,
	OVPN_GET_PEER_RESP_ATTR_MAX = __OVPN_GET_PEER_RESP_ATTR_AFTER_LAST - 1,
};

enum ovpn_netlink_peer_stats_attrs {
	OVPN_PEER_STATS_ATTR_UNSPEC = 0,
	OVPN_PEER_STATS_BYTES,
	OVPN_PEER_STATS_PACKETS,

	__OVPN_PEER_STATS_ATTR_AFTER_LAST,
	OVPN_PEER_STATS_ATTR_MAX = __OVPN_PEER_STATS_ATTR_AFTER_LAST - 1,
};

enum ovpn_netlink_peer_attrs {
	OVPN_PEER_ATTR_UNSPEC = 0,
	OVPN_PEER_ATTR_PEER_ID,
	OVPN_PEER_ATTR_SOCKADDR_REMOTE,
	OVPN_PEER_ATTR_IPV4,
	OVPN_PEER_ATTR_IPV6,
	OVPN_PEER_ATTR_LOCAL_IP,
	OVPN_PEER_ATTR_KEEPALIVE_INTERVAL,
	OVPN_PEER_ATTR_KEEPALIVE_TIMEOUT,
	OVPN_PEER_ATTR_ENCRYPT_KEY,
	OVPN_PEER_ATTR_DECRYPT_KEY,
	OVPN_PEER_ATTR_RX_STATS,
	OVPN_PEER_ATTR_TX_STATS,

	__OVPN_PEER_ATTR_AFTER_LAST,
	OVPN_PEER_ATTR_MAX = __OVPN_PEER_ATTR_AFTER_LAST - 1,
};

enum ovpn_netlink_packet_attrs {
	OVPN_PACKET_ATTR_UNSPEC = 0,
	OVPN_PACKET_ATTR_PACKET,
	OVPN_PACKET_ATTR_PEER_ID,

	__OVPN_PACKET_ATTR_AFTER_LAST,
	OVPN_PACKET_ATTR_MAX = __OVPN_PACKET_ATTR_AFTER_LAST - 1,
};

#endif /* _UAPI_LINUX_OVPN_DCO_H_ */
