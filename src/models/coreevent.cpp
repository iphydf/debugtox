#include "coreevent.h"

#include "src/models/events/conferenceconnected.h"
#include "src/models/events/conferenceinvite.h"
#include "src/models/events/conferencemessage.h"
#include "src/models/events/conferencepeerlistchanged.h"
#include "src/models/events/conferencepeername.h"
#include "src/models/events/conferencetitle.h"
#include "src/models/events/dhtgetnodesresponse.h"
#include "src/models/events/filechunkrequest.h"
#include "src/models/events/filerecv.h"
#include "src/models/events/filerecvchunk.h"
#include "src/models/events/filerecvcontrol.h"
#include "src/models/events/friendconnectionstatus.h"
#include "src/models/events/friendlosslesspacket.h"
#include "src/models/events/friendlossypacket.h"
#include "src/models/events/friendmessage.h"
#include "src/models/events/friendname.h"
#include "src/models/events/friendreadreceipt.h"
#include "src/models/events/friendrequest.h"
#include "src/models/events/friendstatus.h"
#include "src/models/events/friendstatusmessage.h"
#include "src/models/events/friendtyping.h"
#include "src/models/events/groupcustompacket.h"
#include "src/models/events/groupcustomprivatepacket.h"
#include "src/models/events/groupinvite.h"
#include "src/models/events/groupjoinfail.h"
#include "src/models/events/groupmessage.h"
#include "src/models/events/groupmoderation.h"
#include "src/models/events/grouppassword.h"
#include "src/models/events/grouppeerexit.h"
#include "src/models/events/grouppeerjoin.h"
#include "src/models/events/grouppeerlimit.h"
#include "src/models/events/grouppeername.h"
#include "src/models/events/grouppeerstatus.h"
#include "src/models/events/groupprivacystate.h"
#include "src/models/events/groupprivatemessage.h"
#include "src/models/events/groupselfjoin.h"
#include "src/models/events/grouptopic.h"
#include "src/models/events/grouptopiclock.h"
#include "src/models/events/groupvoicestate.h"
#include "src/models/events/selfconnectionstatus.h"

#include <tox/tox_events.h>

CoreEvent::CoreEvent() = default;

CoreEvent::~CoreEvent() = default;

// TOX_EVENT_CONFERENCE_CONNECTED          = 16,
// TOX_EVENT_CONFERENCE_INVITE             = 15,
// TOX_EVENT_CONFERENCE_MESSAGE            = 20,
// TOX_EVENT_CONFERENCE_PEER_LIST_CHANGED  = 17,
// TOX_EVENT_CONFERENCE_PEER_NAME          = 18,
// TOX_EVENT_CONFERENCE_TITLE              = 19,
// TOX_EVENT_DHT_GET_NODES_RESPONSE        = 39,
// TOX_EVENT_FILE_CHUNK_REQUEST            = 11,
// TOX_EVENT_FILE_RECV                     = 12,
// TOX_EVENT_FILE_RECV_CHUNK               = 13,
// TOX_EVENT_FILE_RECV_CONTROL             = 14,
// TOX_EVENT_FRIEND_CONNECTION_STATUS      = 2,
// TOX_EVENT_FRIEND_LOSSLESS_PACKET        = 4,
// TOX_EVENT_FRIEND_LOSSY_PACKET           = 3,
// TOX_EVENT_FRIEND_MESSAGE                = 8,
// TOX_EVENT_FRIEND_NAME                   = 5,
// TOX_EVENT_FRIEND_READ_RECEIPT           = 9,
// TOX_EVENT_FRIEND_REQUEST                = 1,
// TOX_EVENT_FRIEND_STATUS                 = 6,
// TOX_EVENT_FRIEND_STATUS_MESSAGE         = 7,
// TOX_EVENT_FRIEND_TYPING                 = 10,
// TOX_EVENT_GROUP_CUSTOM_PACKET           = 31,
// TOX_EVENT_GROUP_CUSTOM_PRIVATE_PACKET   = 32,
// TOX_EVENT_GROUP_INVITE                  = 33,
// TOX_EVENT_GROUP_JOIN_FAIL               = 37,
// TOX_EVENT_GROUP_MESSAGE                 = 29,
// TOX_EVENT_GROUP_MODERATION              = 38,
// TOX_EVENT_GROUP_PASSWORD                = 28,
// TOX_EVENT_GROUP_PEER_EXIT               = 35,
// TOX_EVENT_GROUP_PEER_JOIN               = 34,
// TOX_EVENT_GROUP_PEER_LIMIT              = 27,
// TOX_EVENT_GROUP_PEER_NAME               = 21,
// TOX_EVENT_GROUP_PEER_STATUS             = 22,
// TOX_EVENT_GROUP_PRIVACY_STATE           = 24,
// TOX_EVENT_GROUP_PRIVATE_MESSAGE         = 30,
// TOX_EVENT_GROUP_SELF_JOIN               = 36,
// TOX_EVENT_GROUP_TOPIC                   = 23,
// TOX_EVENT_GROUP_TOPIC_LOCK              = 26,
// TOX_EVENT_GROUP_VOICE_STATE             = 25,
// TOX_EVENT_SELF_CONNECTION_STATUS        = 0,
std::unique_ptr<CoreEvent> CoreEvent::fromTox(const Tox_Event* event)
{
    switch (tox_event_get_type(event)) {
    case TOX_EVENT_CONFERENCE_CONNECTED:
        return std::make_unique<Events::ConferenceConnected>(tox_event_get_conference_connected(event));
    case TOX_EVENT_CONFERENCE_INVITE:
        return std::make_unique<Events::ConferenceInvite>(tox_event_get_conference_invite(event));
    case TOX_EVENT_CONFERENCE_MESSAGE:
        return std::make_unique<Events::ConferenceMessage>(tox_event_get_conference_message(event));
    case TOX_EVENT_CONFERENCE_PEER_LIST_CHANGED:
        return std::make_unique<Events::ConferencePeerListChanged>(
            tox_event_get_conference_peer_list_changed(event));
    case TOX_EVENT_CONFERENCE_PEER_NAME:
        return std::make_unique<Events::ConferencePeerName>(tox_event_get_conference_peer_name(event));
    case TOX_EVENT_CONFERENCE_TITLE:
        return std::make_unique<Events::ConferenceTitle>(tox_event_get_conference_title(event));
    case TOX_EVENT_DHT_GET_NODES_RESPONSE:
        return std::make_unique<Events::DhtGetNodesResponse>(
            tox_event_get_dht_get_nodes_response(event));
    case TOX_EVENT_FILE_CHUNK_REQUEST:
        return std::make_unique<Events::FileChunkRequest>(tox_event_get_file_chunk_request(event));
    case TOX_EVENT_FILE_RECV:
        return std::make_unique<Events::FileRecv>(tox_event_get_file_recv(event));
    case TOX_EVENT_FILE_RECV_CHUNK:
        return std::make_unique<Events::FileRecvChunk>(tox_event_get_file_recv_chunk(event));
    case TOX_EVENT_FILE_RECV_CONTROL:
        return std::make_unique<Events::FileRecvControl>(tox_event_get_file_recv_control(event));
    case TOX_EVENT_FRIEND_CONNECTION_STATUS:
        return std::make_unique<Events::FriendConnectionStatus>(
            tox_event_get_friend_connection_status(event));
    case TOX_EVENT_FRIEND_LOSSLESS_PACKET:
        return std::make_unique<Events::FriendLosslessPacket>(
            tox_event_get_friend_lossless_packet(event));
    case TOX_EVENT_FRIEND_LOSSY_PACKET:
        return std::make_unique<Events::FriendLossyPacket>(tox_event_get_friend_lossy_packet(event));
    case TOX_EVENT_FRIEND_MESSAGE:
        return std::make_unique<Events::FriendMessage>(tox_event_get_friend_message(event));
    case TOX_EVENT_FRIEND_NAME:
        return std::make_unique<Events::FriendName>(tox_event_get_friend_name(event));
    case TOX_EVENT_FRIEND_READ_RECEIPT:
        return std::make_unique<Events::FriendReadReceipt>(tox_event_get_friend_read_receipt(event));
    case TOX_EVENT_FRIEND_REQUEST:
        return std::make_unique<Events::FriendRequest>(tox_event_get_friend_request(event));
    case TOX_EVENT_FRIEND_STATUS:
        return std::make_unique<Events::FriendStatus>(tox_event_get_friend_status(event));
    case TOX_EVENT_FRIEND_STATUS_MESSAGE:
        return std::make_unique<Events::FriendStatusMessage>(tox_event_get_friend_status_message(event));
    case TOX_EVENT_FRIEND_TYPING:
        return std::make_unique<Events::FriendTyping>(tox_event_get_friend_typing(event));
    case TOX_EVENT_GROUP_CUSTOM_PACKET:
        return std::make_unique<Events::GroupCustomPacket>(tox_event_get_group_custom_packet(event));
    case TOX_EVENT_GROUP_CUSTOM_PRIVATE_PACKET:
        return std::make_unique<Events::GroupCustomPrivatePacket>(
            tox_event_get_group_custom_private_packet(event));
    case TOX_EVENT_GROUP_INVITE:
        return std::make_unique<Events::GroupInvite>(tox_event_get_group_invite(event));
    case TOX_EVENT_GROUP_JOIN_FAIL:
        return std::make_unique<Events::GroupJoinFail>(tox_event_get_group_join_fail(event));
    case TOX_EVENT_GROUP_MESSAGE:
        return std::make_unique<Events::GroupMessage>(tox_event_get_group_message(event));
    case TOX_EVENT_GROUP_MODERATION:
        return std::make_unique<Events::GroupModeration>(tox_event_get_group_moderation(event));
    case TOX_EVENT_GROUP_PASSWORD:
        return std::make_unique<Events::GroupPassword>(tox_event_get_group_password(event));
    case TOX_EVENT_GROUP_PEER_EXIT:
        return std::make_unique<Events::GroupPeerExit>(tox_event_get_group_peer_exit(event));
    case TOX_EVENT_GROUP_PEER_JOIN:
        return std::make_unique<Events::GroupPeerJoin>(tox_event_get_group_peer_join(event));
    case TOX_EVENT_GROUP_PEER_LIMIT:
        return std::make_unique<Events::GroupPeerLimit>(tox_event_get_group_peer_limit(event));
    case TOX_EVENT_GROUP_PEER_NAME:
        return std::make_unique<Events::GroupPeerName>(tox_event_get_group_peer_name(event));
    case TOX_EVENT_GROUP_PEER_STATUS:
        return std::make_unique<Events::GroupPeerStatus>(tox_event_get_group_peer_status(event));
    case TOX_EVENT_GROUP_PRIVACY_STATE:
        return std::make_unique<Events::GroupPrivacyState>(tox_event_get_group_privacy_state(event));
    case TOX_EVENT_GROUP_PRIVATE_MESSAGE:
        return std::make_unique<Events::GroupPrivateMessage>(tox_event_get_group_private_message(event));
    case TOX_EVENT_GROUP_SELF_JOIN:
        return std::make_unique<Events::GroupSelfJoin>(tox_event_get_group_self_join(event));
    case TOX_EVENT_GROUP_TOPIC:
        return std::make_unique<Events::GroupTopic>(tox_event_get_group_topic(event));
    case TOX_EVENT_GROUP_TOPIC_LOCK:
        return std::make_unique<Events::GroupTopicLock>(tox_event_get_group_topic_lock(event));
    case TOX_EVENT_GROUP_VOICE_STATE:
        return std::make_unique<Events::GroupVoiceState>(tox_event_get_group_voice_state(event));
    case TOX_EVENT_SELF_CONNECTION_STATUS:
        return std::make_unique<Events::SelfConnectionStatus>(
            tox_event_get_self_connection_status(event));
    case TOX_EVENT_INVALID:
        return nullptr;
    }
    return nullptr;
}
